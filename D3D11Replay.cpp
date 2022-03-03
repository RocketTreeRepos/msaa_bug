#include "D3D11Replay.h"

#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgi.h>

#include "Application.h"
#include "Arguments.h"
#include "function_overrides.h"

//------------------------------------------------------------------------------
// D3D11Replay_D3D11CreateDeviceAndSwapChainCommon
//------------------------------------------------------------------------------
HRESULT D3D11Replay_D3D11CreateDeviceAndSwapChain(
    IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    IDXGISwapChain** ppSwapChain,
    ID3D11Device** ppDevice,
    D3D_FEATURE_LEVEL* pFeatureLevel,
    ID3D11DeviceContext** ppImmediateContext)
{
    DXGI_SWAP_CHAIN_DESC swapChainDescOverride;
    const DXGI_SWAP_CHAIN_DESC* pSwapChainDescOverride = pSwapChainDesc;
    if (pSwapChainDesc && Application::HasForceBorderlessWindow()) {
        pSwapChainDescOverride = &swapChainDescOverride;
        swapChainDescOverride = *pSwapChainDesc;
        swapChainDescOverride.Windowed = TRUE;
    }
    const HRESULT result = My_D3D11CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDescOverride, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
    return result;
}

static const GUID s_WKPDID_D3DDebugObjectName = { 0x429b8c22, 0x9188, 0x4b0c, { 0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00 } };

//-----------------------------------------------------------------------------
// NvNameHelperSetObjectName
//-----------------------------------------------------------------------------
void NvNameHelperSetObjectName(ID3D11Device* pObj, const char* pName)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    if (pObj && pName)
    {
        BEGIN_DATA_SCOPE();

        NV_CHECK_RESULT(pObj->SetPrivateData(s_WKPDID_D3DDebugObjectName, (UINT)strlen(pName) + 1, pName));
    }
}

//-----------------------------------------------------------------------------
// NvNameHelperSetObjectName
//-----------------------------------------------------------------------------
void NvNameHelperSetObjectName(ID3D11DeviceChild* pObj, const char* pName)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    if (pObj && pName)
    {
        BEGIN_DATA_SCOPE();

        NV_CHECK_RESULT(pObj->SetPrivateData(s_WKPDID_D3DDebugObjectName, (UINT)strlen(pName) + 1, pName));
    }
}

//-----------------------------------------------------------------------------
// NvNameHelperSetObjectName
//-----------------------------------------------------------------------------
void NvNameHelperSetObjectName(ID3D11VideoDevice* pObj, const char* pName)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    if (pObj && pName)
    {
        BEGIN_DATA_SCOPE();

        NV_CHECK_RESULT(pObj->SetPrivateData(s_WKPDID_D3DDebugObjectName, (UINT)strlen(pName) + 1, pName));
    }
}

//-----------------------------------------------------------------------------
// NvNameHelperSetObjectName
//-----------------------------------------------------------------------------
void NvNameHelperSetObjectName(IDXGIObject* pObj, const char* pName)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    if (pObj && pName)
    {
        BEGIN_DATA_SCOPE();

        NV_CHECK_RESULT(pObj->SetPrivateData(s_WKPDID_D3DDebugObjectName, (UINT)strlen(pName) + 1, pName));
    }
}

//-----------------------------------------------------------------------------
// NvNameHelperSetObjectName
//-----------------------------------------------------------------------------
void NvNameHelperSetObjectName(IUnknown* pObj, const char* pName)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    if (pObj && pName)
    {
        BEGIN_DATA_SCOPE();

        ID3D11Texture2D* pID3D11Texture2D_temp_1 = nullptr;
        if (SUCCEEDED(pObj->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&pID3D11Texture2D_temp_1)))
        {
            BEGIN_DATA_SCOPE();

            NvNameHelperSetObjectName(pID3D11Texture2D_temp_1, pName);
            NV_SAFE_RELEASE(pID3D11Texture2D_temp_1);
        }
    }
}

//-----------------------------------------------------------------------------
// InitializeSubresourceDataD3D11
//-----------------------------------------------------------------------------
D3D11_SUBRESOURCE_DATA* InitializeSubresourceDataD3D11(int resourceId, std::vector<uint8_t>& retvalData, Serialization::BlobProxy<uint8_t*>& dataProxy)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    struct PORTABLE_SUBRESOURCE_DATA
    {
            uint64_t pSysMem;
            UINT SysMemPitch;
            UINT SysMemSlicePitch;
    };

    Serialization::DATABASE_HANDLE handle(resourceId);
    uint64_t totalBlobSize = GetDatabase().GetSize(handle);
    if (0 == totalBlobSize)
    {
        BEGIN_DATA_SCOPE();

        return NULL;
    }

    dataProxy = GetDatabase().Read<uint8_t*>(handle);

    // Extract the subresource count
    UINT* pBlobCount = (UINT*)dataProxy.Get();
    UINT subResourceCount = *pBlobCount;

    // Extract the descs
    PORTABLE_SUBRESOURCE_DATA* pPortableBlobDescs = (PORTABLE_SUBRESOURCE_DATA*)(pBlobCount + 1);

    // Declare output data
    retvalData.resize(size_t(subResourceCount * sizeof(D3D11_SUBRESOURCE_DATA)));
    D3D11_SUBRESOURCE_DATA* pBlobDescs = (D3D11_SUBRESOURCE_DATA*)(&retvalData[0]);

    // Convert portable data to the 32 or 64 bit pointers, converting all the offsets to pointers
    for (UINT subResource = 0; subResource < subResourceCount; ++subResource)
    {
        BEGIN_DATA_SCOPE();

        if (NULL == pPortableBlobDescs[subResource].pSysMem)
        {
            BEGIN_DATA_SCOPE();

            pBlobDescs[subResource].pSysMem = NULL;
        }
        else
        {
            BEGIN_DATA_SCOPE();

            pBlobDescs[subResource].pSysMem = dataProxy.Get() + (UINT)pPortableBlobDescs[subResource].pSysMem;
        }

        pBlobDescs[subResource].SysMemPitch = pPortableBlobDescs[subResource].SysMemPitch;
        pBlobDescs[subResource].SysMemSlicePitch = pPortableBlobDescs[subResource].SysMemSlicePitch;
    }

    // Return pointer to descs to caller
    return pBlobDescs;
}