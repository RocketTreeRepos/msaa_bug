#include "DXGIReplay.h"

#include <dxgi1_2.h>

#include "Application.h"
#include "Arguments.h"
#include "function_overrides.h"

#include <chrono>
#include <ctime>
#include <iomanip>

static const uint32_t s_invalidAdapterIndex = 0xFFFFFFFF;
static uint32_t s_adapterIndex = s_invalidAdapterIndex;

//------------------------------------------------------------------------------
// DXGI-specific Options functions
//------------------------------------------------------------------------------
static FnParseResults DXGIArguments(args::ArgumentParser& parser)
{
    static args::Group optDXGIgroup(parser, "DXGI-specific options:");

    // By default we use the adapter index requested by the application at runtime.  This
    // option allows us to override that value when replaying the C++ Capture.
    static args::Flag optAdapterIndex(optDXGIgroup, "DXGI-adapter", "Adapter index used when enumerating adapters [default=0]", { "DXGI-adapter", "adapter" });

    return [=]() {
        if (optAdapterIndex) {
            s_adapterIndex = optAdapterIndex.Get();
        }

        if (Application::MinimizeCPUOverheadRequested()) {
            // This is where we set any options that we know are safe to enable and minimize the CPU overhead
        }
    };
}

REGISTER_ARGUMENTS(DXGIArguments);

//------------------------------------------------------------------------------
// DXGIReplay_SetFullscreenState
//------------------------------------------------------------------------------
HRESULT DXGIReplay_SetFullscreenState(IDXGISwapChain* pSwapChain, BOOL Fullscreen, IDXGIOutput* pTarget)
{
    const BOOL fullscreenOverride = Application::HasForceBorderlessWindow() ? FALSE : Fullscreen;
    IDXGIOutput* pTargetOverride = Application::HasForceBorderlessWindow() ? nullptr : pTarget;
    const HRESULT result = My_IDXGISwapChain_SetFullscreenState(pSwapChain, fullscreenOverride, pTargetOverride);
    return result;
}

//------------------------------------------------------------------------------
// DXGIReplay_CreateSwapChain
//------------------------------------------------------------------------------
HRESULT DXGIReplay_CreateSwapChain(
    IDXGIFactory* pFactory,
    IUnknown* pDevice,
    DXGI_SWAP_CHAIN_DESC* pDesc,
    IDXGISwapChain** ppSwapChain)
{
    DXGI_SWAP_CHAIN_DESC swapChainDescOverride;
    DXGI_SWAP_CHAIN_DESC* pSwapChainDescOverride = pDesc;
    if (pDesc && Application::HasForceBorderlessWindow()) {
        pSwapChainDescOverride = &swapChainDescOverride;
        swapChainDescOverride = *pDesc;
        swapChainDescOverride.Windowed = TRUE;
    }
    const HRESULT result = My_IDXGIFactory_CreateSwapChain(pFactory, pDevice, pSwapChainDescOverride, ppSwapChain);
    return result;
}

//------------------------------------------------------------------------------
// DXGIReplay_CreateSwapChainForHwnd
//------------------------------------------------------------------------------
HRESULT DXGIReplay_CreateSwapChainForHwnd(IDXGIFactory2* pFactory,
    IUnknown* pDevice,
    HWND hWnd,
    const DXGI_SWAP_CHAIN_DESC1* pDesc,
    const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc,
    IDXGIOutput* pRestrictToOutput,
    IDXGISwapChain1** ppSwapChain)
{
    DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDescOverride;
    const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDescOverride = pFullscreenDesc;
    if (pFullscreenDesc && Application::HasForceBorderlessWindow()) {
        pFullscreenDescOverride = &fullscreenDescOverride;
        fullscreenDescOverride = *pFullscreenDesc;
        fullscreenDescOverride.Windowed = TRUE;
    }
    const HRESULT result = My_IDXGIFactory2_CreateSwapChainForHwnd(pFactory, pDevice, hWnd, pDesc, pFullscreenDescOverride, pRestrictToOutput, ppSwapChain);
    return result;
}

//------------------------------------------------------------------------------
// DXGIReplay_EnumAdapters
//------------------------------------------------------------------------------
HRESULT DXGIReplay_EnumAdapters(uint32_t adapterIndex, IDXGIFactory* pFactory, IDXGIAdapter** pAdapterInterface)
{
    const auto adapterIndextoUse = (s_adapterIndex != s_invalidAdapterIndex) ? s_adapterIndex : adapterIndex;
    return My_IDXGIFactory_EnumAdapters(pFactory, adapterIndextoUse, pAdapterInterface);
}

//------------------------------------------------------------------------------
// DXGIReplay_EnumAdapters
//------------------------------------------------------------------------------
HRESULT DXGIReplay_EnumAdapters1(uint32_t adapterIndex, IDXGIFactory1* pFactory1, IDXGIAdapter1** pAdapterInterface)
{
    const auto adapterIndextoUse = (s_adapterIndex != s_invalidAdapterIndex ? s_adapterIndex : adapterIndex);
    return My_IDXGIFactory1_EnumAdapters1(pFactory1, adapterIndextoUse, pAdapterInterface);
}

//------------------------------------------------------------------------------
// DXGIReplay_CheckPresentResult
//------------------------------------------------------------------------------
void DXGIReplay_CheckPresentResult(HRESULT result, IDXGISwapChain* pSwapChain, const char* file, int line)
{
    if (FAILED(result)) {
        DXGI_SWAP_CHAIN_DESC tempDesc;
        pSwapChain->GetDesc(&tempDesc);
        std::stringstream stream;
        stream << "Present Failed with error 0x" << std::hex << result << std::endl << std::endl;
        stream << "Try the -wb option to force windowed borderless." << std::endl;
        if (tempDesc.SwapEffect != DXGI_SWAP_EFFECT_DISCARD && tempDesc.SwapEffect != DXGI_SWAP_EFFECT_SEQUENTIAL) {
            stream << "Otherwise, try changing the swap chain swap effect to DXGI_SWAP_EFFECT_DISCARD or DXGI_SWAP_EFFECT_SEQUENTIAL to see if it solves the problem." << std::endl << std::endl;
        }
        ThrowErrorWithMessage(stream.str().c_str(), file, line);
    }
}

//------------------------------------------------------------------------------
// DXGIReplay_CaptureScreenShot
//------------------------------------------------------------------------------
void DXGIReplay_CaptureScreenShot(HWND hwnd, std::string filename)
{
    struct CaptureWindowsScreenshot
    {
        CaptureWindowsScreenshot(HWND hwnd, std::string filename)
            : hWnd(hwnd)
            , filename(filename)

        {
        }

        void DoCapture()
        {
            if (!hWnd) {
                hWnd = GetActiveWindow();
            }

            SetForegroundWindow(hWnd);

            // Retrieve the handle to a display device context for the client 
            // area of the window. 
            hdcScreen = GetDC(NULL);
            hdcWindow = GetDC(hWnd);

            // Create a compatible DC which is used in a BitBlt from the window DC
            hdcMemDC = CreateCompatibleDC(hdcWindow);
            NV_ASSERT(hdcMemDC);

            // Get the client area for size calculation
            WINDOWINFO wi = {};
            GetWindowInfo(hWnd, &wi);
            RECT& rcClient = wi.rcClient;
            auto width = rcClient.right - rcClient.left;
            auto height = rcClient.bottom - rcClient.top;

            // Create a compatible bitmap from the Window DC
            hbmScreen = CreateCompatibleBitmap(hdcWindow, width, height);
            NV_ASSERT(hbmScreen);

            //The source DC is the entire screen and the destination DC is the current window (HWND)
            BOOL bltOk = BitBlt(hdcWindow,
                0,
                0,
                width,
                height,
                hdcScreen,
                rcClient.left,
                rcClient.top,
                SRCCOPY);
            NV_ASSERT(bltOk);

            // Select the compatible bitmap into the compatible memory DC.
            SelectObject(hdcMemDC, hbmScreen);

            // Bit block transfer into our compatible memory DC.
            bltOk = BitBlt(hdcMemDC,
                0, 0,
                width, 
                height,
                hdcWindow,
                0, 0,
                SRCCOPY);
            NV_ASSERT(bltOk);

            // Get the BITMAP from the HBITMAP
            GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

            BITMAPFILEHEADER   bmfHeader;
            BITMAPINFOHEADER   bi;

            bi.biSize = sizeof(BITMAPINFOHEADER);
            bi.biWidth = bmpScreen.bmWidth;
            bi.biHeight = bmpScreen.bmHeight;
            bi.biPlanes = 1;
            bi.biBitCount = 32;
            bi.biCompression = BI_RGB;
            bi.biSizeImage = 0;
            bi.biXPelsPerMeter = 0;
            bi.biYPelsPerMeter = 0;
            bi.biClrUsed = 0;
            bi.biClrImportant = 0;

            DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

            // Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
            // call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
            // have greater overhead than HeapAlloc.
            hDIB = GlobalAlloc(GHND, dwBmpSize);
            NV_ASSERT(hDIB);

            char* lpbitmap = (char*)GlobalLock(hDIB);

            // Gets the "bits" from the bitmap and copies them into a buffer 
            // which is pointed to by lpbitmap.
            GetDIBits(hdcWindow, hbmScreen, 0,
                (UINT)bmpScreen.bmHeight,
                lpbitmap,
                (BITMAPINFO*)&bi, DIB_RGB_COLORS);

            // A file is created, this is where we will save the screen capture.
            hFile = CreateFileA(filename.c_str(),
                GENERIC_WRITE,
                0,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL, NULL);
            NV_ASSERT(hFile);

            // Add the size of the headers to the size of the bitmap to get the total file size
            DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

            //Offset to where the actual bitmap bits start.
            bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

            //Size of the file
            bmfHeader.bfSize = dwSizeofDIB;

            //bfType must always be BM for Bitmaps
            bmfHeader.bfType = 0x4D42; //BM   

            DWORD dwBytesWritten = 0;
            auto CheckWriteFile = [&](BOOL ok) {
                NV_ASSERT(ok && dwBytesWritten);
            };

            CheckWriteFile(WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL));
            CheckWriteFile(WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL));
            CheckWriteFile(WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL));
        }

        ~CaptureWindowsScreenshot()
        {
            if (hDIB) {
                GlobalUnlock(hDIB);
                GlobalFree(hDIB);
            }

            CloseHandle(hFile);
            DeleteObject(hbmScreen);
            DeleteObject(hdcMemDC);
            ReleaseDC(nullptr, hdcScreen);
            ReleaseDC(hWnd, hdcWindow);
        }

    private:
        HWND hWnd = nullptr;
        std::string filename;
        HANDLE hDIB = nullptr;
        HANDLE hFile = nullptr;
        HDC hdcScreen = nullptr;
        HDC hdcWindow = nullptr;
        HDC hdcMemDC = NULL;
        HBITMAP hbmScreen = NULL;
        BITMAP bmpScreen = {};
    };

    if (filename.empty()) {
        // Assign a filename based on exe name/date/time
        std::string exeName(size_t(MAX_PATH), '\0');
        auto hMod = GetModuleHandleA(nullptr);
        auto exeNameSize = GetModuleFileNameA(hMod, &exeName[0], MAX_PATH);
        exeName.resize(exeNameSize);

        auto slashIndex = exeName.find_last_of("/\\");
        if (slashIndex != std::string::npos) {
            exeName = exeName.substr(slashIndex + 1);
        }

        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto localClock = std::localtime(&time);
        std::stringstream sstr;
        sstr << exeName << '_' << localClock->tm_year + 1900  << '_' << localClock->tm_mon + 1 << '_' << localClock->tm_mday << "__" << localClock->tm_hour << '_' << localClock->tm_min << '_' << localClock->tm_sec << ".BMP";
        filename = sstr.str();
    }

    CaptureWindowsScreenshot screenshot(hwnd, filename);
    screenshot.DoCapture();
}
