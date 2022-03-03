//---------------------------------------------------------------------------
// File: WindowSystem_Egldevice.cpp
//
// Distributed as part of NVIDIA Tegra Graphics Debugger serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------

#include "WindowSystem.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <dlfcn.h>
#include <fcntl.h>

#include <xf86drm.h>
#include <xf86drmMode.h>

#include <map>
#include <vector>

namespace // unnamed
{

using PFNDRMOPEN = int (*)(const char*, const char*);
using PFNDRMMODEGETRESOURCES = drmModeResPtr (*)(int);
using PFNDRMMODEFREERESOURCES = void (*)(drmModeResPtr);
using PFNDRMMODEGETPLANERESOURCES = drmModePlaneResPtr (*)(int);
using PFNDRMMODEFREEPLANERESOURCES = void (*)(drmModePlaneResPtr);
using PFNDRMMODEGETCONNECTOR = drmModeConnectorPtr (*)(int, uint32_t);
using PFNDRMMODEFREECONNECTOR = void (*)(drmModeConnectorPtr);
using PFNDRMMODEGETENCODER = drmModeEncoderPtr (*)(int, uint32_t);
using PFNDRMMODEFREEENCODER = void (*)(drmModeEncoderPtr);
using PFNDRMMODEGETPLANE = drmModePlanePtr (*)(int, uint32_t);
using PFNDRMMODEFREEPLANE = void (*)(drmModePlanePtr);
using PFNDRMMODESETCRTC = int (*)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t*, int, drmModeModeInfoPtr);
using PFNDRMMODEGETCRTC = drmModeCrtcPtr (*)(int, uint32_t);
using PFNDRMMODESETPLANE = int (*)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
using PFNDRMMODEFREECRTC = void (*)(drmModeCrtcPtr);

PFNDRMOPEN FP_drmOpen = nullptr;
PFNDRMMODEGETRESOURCES FP_drmModeGetResources = nullptr;
PFNDRMMODEFREERESOURCES FP_drmModeFreeResources = nullptr;
PFNDRMMODEGETPLANERESOURCES FP_drmModeGetPlaneResources = nullptr;
PFNDRMMODEFREEPLANERESOURCES FP_drmModeFreePlaneResources = nullptr;
PFNDRMMODEGETCONNECTOR FP_drmModeGetConnector = nullptr;
PFNDRMMODEFREECONNECTOR FP_drmModeFreeConnector = nullptr;
PFNDRMMODEGETENCODER FP_drmModeGetEncoder = nullptr;
PFNDRMMODEFREEENCODER FP_drmModeFreeEncoder = nullptr;
PFNDRMMODEGETPLANE FP_drmModeGetPlane = nullptr;
PFNDRMMODEFREEPLANE FP_drmModeFreePlane = nullptr;
PFNDRMMODESETCRTC FP_drmModeSetCrtc = nullptr;
PFNDRMMODEGETCRTC FP_drmModeGetCrtc = nullptr;
PFNDRMMODESETPLANE FP_drmModeSetPlane = nullptr;
PFNDRMMODEFREECRTC FP_drmModeFreeCrtc = nullptr;

typedef EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLOutputLayerEXT layer);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *num_devices);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, const EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *num_layers);
typedef const char *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *value);

PFNEGLSTREAMCONSUMEROUTPUTEXTPROC FP_eglStreamConsumerOutputEXT = nullptr;
PFNEGLQUERYDEVICESEXTPROC FP_eglQueryDevicesEXT = nullptr;
PFNEGLGETOUTPUTLAYERSEXTPROC FP_eglGetOutputLayersEXT = nullptr;
PFNEGLQUERYDEVICESTRINGEXTPROC FP_eglQueryDeviceStringEXT = nullptr;
PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC FP_eglQueryOutputLayerAttribEXT = nullptr;

} // unnamed

class EglDeviceSystem : public WindowSystem
{

public:
    virtual void CreateDisplay() override
    {
        DoInitEglDevice();
        DoInitDrmDevice();
    }

    virtual void DestroyDisplay() override
    {
        if (m_pDrmRes)
        {
            FP_drmModeFreeResources(m_pDrmRes);
        }

        if (m_pDrmPlaneRes)
        {
            FP_drmModeFreePlaneResources(m_pDrmPlaneRes);
        }

        if (m_libDrmHandle)
        {
            dlclose(m_libDrmHandle);
        }
    }

    virtual void CreateNativeWindow(void* data, int width, int height) override
    {
        DoCreateEglDevice();
        DoCreateDrmDevice();
        DoSetDrmOutputMode();
    }

    virtual void DestroyAllWindows() override
    {
        // Nothing to do.
    }

    virtual void DestroyWindow(void* winAddr) override
    {
        // Nothing to do.
    }

    virtual void* GetDisplayAddr() override
    {
        if ((m_currDevIndex != -1) && (m_currDevIndex < m_vecDevices.size()))
        {
            return reinterpret_cast<void*>(&m_vecDevices[m_currDevIndex]);
        }

        return reinterpret_cast<void*>(&m_null_display);
    }

    virtual void* GetWindowAddr() override
    {
        return reinterpret_cast<void*>(&m_null_window);
    }

#if defined(WINAPI_EGL)
#ifdef EGL_KHR_stream
    virtual void ConnectConsumerToStream(EGLStreamKHR stream) override
    {
        if (m_currLayerIndex == -1)
        {
            return;
        }

        // Connect the output layer to the stream
        EGLBoolean result = FP_eglStreamConsumerOutputEXT(m_display, stream, m_vecLayers[m_currLayerIndex]);
        NV_THROW_IF(!result, "Failed to connect the output layer to the stream.");
    }
#endif

    virtual void* GetEGLDisplayAddr() override
    {
        return reinterpret_cast<void*>(&m_display);
    }
#endif

    EglDeviceSystem()
        : m_display(0)
        , m_vecDevices()
        , m_vecLayers()
        , m_null_display(0)
        , m_null_window(0)
        , m_libDrmHandle(nullptr)
        , m_drmDescriptor(0)
        , m_pDrmName(nullptr)
        , m_pDrmRes(nullptr)
        , m_pDrmPlaneRes(nullptr)
        , m_mapConnToCrtc()
        , m_mapCrtcToLayer()
        , m_currDevIndex(-1)
        , m_currLayerIndex(-1)
        , m_currConnIndex(-1)
        , m_currCrtcIndex(-1)
    {
    }

private:
    void DoInitEglDevice()
    {
        // Macro to load egl ext function pointers
#define NV_LOAD_EGLEXT_PTR(name, type)                                   \
    FP_##name = reinterpret_cast<type>(eglGetProcAddress(#name)); \
    NV_THROW_IF(!FP_##name, "Failed to load symbol from libEGL.so.1.");

        // Get EGL ext functions
        NV_LOAD_EGLEXT_PTR(eglStreamConsumerOutputEXT, PFNEGLSTREAMCONSUMEROUTPUTEXTPROC);
        NV_LOAD_EGLEXT_PTR(eglQueryDevicesEXT, PFNEGLQUERYDEVICESEXTPROC);
        NV_LOAD_EGLEXT_PTR(eglGetOutputLayersEXT, PFNEGLGETOUTPUTLAYERSEXTPROC);
        NV_LOAD_EGLEXT_PTR(eglQueryDeviceStringEXT, PFNEGLQUERYDEVICESTRINGEXTPROC);
        NV_LOAD_EGLEXT_PTR(eglQueryOutputLayerAttribEXT, PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC);       

#undef NV_LOAD_EGLEXT_PTR

        // Get the extension string.
        const char* pExtensions = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        NV_THROW_IF(!pExtensions, "Failed to query EGL extensions.");

        // Check extensions for EGL device.
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_device_base"), "EGL device platform extension is not there.");
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_platform_base"), "EGL device platform extension is not there.");
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_platform_device"), "EGL device platform extension is not there.");

        // Query the number of all supported devices in the system.
        EGLint num = 0;
        EGLBoolean result = FP_eglQueryDevicesEXT(0, nullptr, &num);
        NV_THROW_IF(!result || (num == 0), "Failed to query EGL devices.");

        // Load devices.
        m_vecDevices.resize(num);
        EGLint deviceCount = 0;
        result = FP_eglQueryDevicesEXT(num, m_vecDevices.data(), &deviceCount);
        NV_THROW_IF(!result || (deviceCount == 0), "Failed to load EGL device.");

        // Use device 0 as default
        m_currDevIndex = 0;
        printf("Try using device %d\n", m_currDevIndex);

        m_display = eglGetPlatformDisplay(EGL_PLATFORM_DEVICE_EXT, static_cast<NativeDisplayType>(m_vecDevices[m_currDevIndex]), nullptr);
    }

    void DoCreateEglDevice()
    {
        // Get extension string
        const char* pExtensions = eglQueryString(m_display, EGL_EXTENSIONS);
        NV_THROW_IF(!pExtensions, "Failed to query EGL extensions.");

        // Check extensions for EGL stream
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_output_base"), "EGL stream extension is not there..");
        NV_THROW_IF(!strstr(pExtensions, "EGL_KHR_stream"), "EGL stream extension is not there..");
        NV_THROW_IF(!strstr(pExtensions, "EGL_KHR_stream_producer_eglsurface"), "EGL stream extension is not there..");
        NV_THROW_IF(!strstr(pExtensions, "EGL_EXT_stream_consumer_egloutput"), "EGL stream extension is not there..");

        // Query the number of all supported layers in the system.
        EGLint num = 0;
        EGLBoolean result = FP_eglGetOutputLayersEXT(m_display, nullptr, nullptr, 0, &num);
        NV_THROW_IF(!result || (num == 0), "Failed to query EGL layers.");

        // Obtain layers.
        m_vecLayers.resize(num);
        EGLint layerCount = 0;
        result = FP_eglGetOutputLayersEXT(m_display, nullptr, m_vecLayers.data(), num, &layerCount);
        NV_THROW_IF(!result || (layerCount == 0), "Failed to obtain EGL layer.");
    }

    void DoInitDrmDevice()
    {
        // Open DRM library
        void* m_libDrmHandle = dlopen("libdrm.so.2", RTLD_LAZY);
        NV_THROW_IF(!m_libDrmHandle, "Failed to open libdrm.so.2");

// Macro to load function pointers
#define NV_LOAD_DRM_PTR(name, type)                                   \
    FP_##name = reinterpret_cast<type>(dlsym(m_libDrmHandle, #name)); \
    NV_THROW_IF(!FP_##name, "Failed to load symbol from libdrm.so.2.");

        // Get DRM functions
        NV_LOAD_DRM_PTR(drmOpen, PFNDRMOPEN);
        NV_LOAD_DRM_PTR(drmModeGetResources, PFNDRMMODEGETRESOURCES);
        NV_LOAD_DRM_PTR(drmModeFreeResources, PFNDRMMODEFREERESOURCES);
        NV_LOAD_DRM_PTR(drmModeGetPlaneResources, PFNDRMMODEGETPLANERESOURCES);
        NV_LOAD_DRM_PTR(drmModeFreePlaneResources, PFNDRMMODEFREEPLANERESOURCES);
        NV_LOAD_DRM_PTR(drmModeGetConnector, PFNDRMMODEGETCONNECTOR);
        NV_LOAD_DRM_PTR(drmModeFreeConnector, PFNDRMMODEFREECONNECTOR);
        NV_LOAD_DRM_PTR(drmModeGetEncoder, PFNDRMMODEGETENCODER);
        NV_LOAD_DRM_PTR(drmModeFreeEncoder, PFNDRMMODEFREEENCODER);
        NV_LOAD_DRM_PTR(drmModeGetPlane, PFNDRMMODEGETPLANE);
        NV_LOAD_DRM_PTR(drmModeFreePlane, PFNDRMMODEFREEPLANE);
        NV_LOAD_DRM_PTR(drmModeSetCrtc, PFNDRMMODESETCRTC);
        NV_LOAD_DRM_PTR(drmModeGetCrtc, PFNDRMMODEGETCRTC);
        NV_LOAD_DRM_PTR(drmModeSetPlane, PFNDRMMODESETPLANE);
        NV_LOAD_DRM_PTR(drmModeFreeCrtc, PFNDRMMODEFREECRTC);

#undef NV_LOAD_DRM_PTR
    }

    // Create DRM desktop
    void DoCreateDrmDevice()
    {
        // Open DRM file and query resources
        m_pDrmName = FP_eglQueryDeviceStringEXT(m_vecDevices[m_currDevIndex], EGL_DRM_DEVICE_FILE_EXT);
        NV_THROW_IF(!m_pDrmName, "Failed to query EGL_DRM_DEVICE_FILE_EXT.");

        if (strcmp(m_pDrmName, "drm-nvdc") == 0) {
            m_drmDescriptor = FP_drmOpen(m_pDrmName, nullptr);
        } else {
            m_drmDescriptor = open(m_pDrmName, O_RDWR);
        }

        NV_THROW_IF(m_drmDescriptor == -1, "Failed to open DRM.");

        m_pDrmRes = FP_drmModeGetResources(m_drmDescriptor);
        NV_THROW_IF(!m_pDrmRes, "Failed to get DRM resources.");

        m_pDrmPlaneRes = FP_drmModeGetPlaneResources(m_drmDescriptor);
        NV_THROW_IF(!m_pDrmPlaneRes, "Failed to get DRM plane resources.");

        // Find all available connectors and their associated CRTCs.
        for (int connIndex = 0; connIndex < m_pDrmRes->count_connectors; ++connIndex)
        {
            drmModeConnector* pConnector = FP_drmModeGetConnector(m_drmDescriptor, m_pDrmRes->connectors[connIndex]);
            if (!pConnector || (pConnector->connection != DRM_MODE_CONNECTED) || (pConnector->count_modes <= 0))
            {
                // Try the next connector.
                continue;
            }

            //                 // Record the connector we try to use.
            //                 m_currConnIndex = connIndex;
            //                 std::cout << "Try using display output " << m_currConnIndex << std::endl;

            // Find a usable CRTC associated with the selected connector
            drmModeEncoder* pEncoder = FP_drmModeGetEncoder(m_drmDescriptor, pConnector->encoder_id);
            if (pEncoder)
            {
                for (int crtcIndex = 0; crtcIndex < m_pDrmRes->count_crtcs; ++crtcIndex)
                {
                    if (m_pDrmRes->crtcs[crtcIndex] == pEncoder->crtc_id)
                    {
                        m_mapConnToCrtc[connIndex] = crtcIndex;
                        printf("Associate connector %d with %d\n", connIndex, crtcIndex);
                        //                             m_currCrtcIndex = crtcIndex;
                        //                             std::cout << "Try using CRTC " << m_currCrtcIndex << std::endl;
                    }
                }

                // Free the encoder info
                FP_drmModeFreeEncoder(pEncoder);
            }

            // Free the connector info
            FP_drmModeFreeConnector(pConnector);
        }
        NV_THROW_IF(m_mapConnToCrtc.empty(), "Failed to find available connector.");

        // Map CRTCs to layers
        for (unsigned int layerIndex = 0; layerIndex < m_vecLayers.size(); ++layerIndex)
        {
            EGLAttrib attribID = 0;
            if (FP_eglQueryOutputLayerAttribEXT(m_display, m_vecLayers[layerIndex], EGL_DRM_CRTC_EXT, &attribID))
            {
                for (int crtcIndex = 0; crtcIndex < m_pDrmRes->count_crtcs; ++crtcIndex)
                {
                    if (m_pDrmRes->crtcs[crtcIndex] == attribID)
                    {
                        m_mapCrtcToLayer[crtcIndex] = layerIndex;
                    }
                }
            }
        }
        NV_THROW_IF(m_mapCrtcToLayer.empty(), "Failed to find available CRTC.");

        for (const auto& pairConnToCrtc : m_mapConnToCrtc)
        {
            if (m_mapCrtcToLayer.find(pairConnToCrtc.second) != m_mapCrtcToLayer.end())
            {
                // Keep the three indices in the consistent state, all in uninitialized or
                // all in initialized.
                m_currConnIndex = pairConnToCrtc.first;
                m_currCrtcIndex = pairConnToCrtc.second;
                m_currLayerIndex = m_mapCrtcToLayer[m_currCrtcIndex];
                printf("Try using connector %d, CRTC %d, output layer %d\n", m_currConnIndex, m_currCrtcIndex, m_currLayerIndex);
            }
        }
        NV_THROW_IF(m_currLayerIndex == -1, "Failed to find available connector/CRTC/output layer.");
    }

    // Set DRM output mode
    void DoSetDrmOutputMode()
    {
        if ((m_currConnIndex == -1) || (m_currCrtcIndex == -1))
        {
            return;
        }

        // Get the current state of the connector
        drmModeConnector* pConnector = FP_drmModeGetConnector(m_drmDescriptor, m_pDrmRes->connectors[m_currConnIndex]);
        NV_THROW_IF(!pConnector, "Failed to get DRM connector.");

        // Set the output mode
        {
            int selectedModeIndex = 0;
            unsigned int modeSize = 0;

            // Choose the largest supported mode (because if you got it, flaunt it)
            for (int connIndex = 0; connIndex < pConnector->count_modes; ++connIndex)
            {
                drmModeModeInfoPtr pMode = pConnector->modes + connIndex;
                unsigned int size = static_cast<unsigned int>(pMode->hdisplay) * static_cast<unsigned int>(pMode->vdisplay);
                if (size > modeSize)
                {
                    selectedModeIndex = connIndex;
                }
            }

            drmModeCrtcPtr pCrtc = reinterpret_cast<drmModeCrtcPtr>(FP_drmModeGetCrtc(m_drmDescriptor, m_pDrmRes->crtcs[m_currCrtcIndex]));
            if (!pCrtc)
            {
                FP_drmModeFreeCrtc(pCrtc);

                // Set the mode
                FP_drmModeSetCrtc(m_drmDescriptor,
                    m_pDrmRes->crtcs[m_currCrtcIndex],
                    -1,
                    0,
                    0,
                    &m_pDrmRes->connectors[m_currConnIndex],
                    1,
                    pConnector->modes + selectedModeIndex);
            }
        }
    }

    // EGL variables
    EGLDisplay m_display;
    std::vector<EGLDeviceEXT> m_vecDevices;
    std::vector<EGLOutputLayerEXT> m_vecLayers;
    NativeDisplayType m_null_display;
    NativeWindowType m_null_window;

    // DRM variables
    void* m_libDrmHandle;
    int m_drmDescriptor;
    const char* m_pDrmName;
    drmModeRes* m_pDrmRes;
    drmModePlaneRes* m_pDrmPlaneRes;

    // Record of usable connectors and its associated CRTC
    std::map<int, int> m_mapConnToCrtc;

    // Record of usable CRTC and its associated layer
    std::map<int, int> m_mapCrtcToLayer;

    // Indices records
    int m_currDevIndex;
    int m_currLayerIndex;
    int m_currConnIndex;
    int m_currCrtcIndex;
};

WindowSystem& WindowSystemInstance()
{
    static EglDeviceSystem instance;
    return instance;
}
