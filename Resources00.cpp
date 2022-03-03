//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2021.3.1.0
// 
// File: Resources00.cpp
// 
//-----------------------------------------------------------------------------

#include <vector>
#include <d3d9.h>
#include <d3d11.h>
#include <dxgi.h>

#ifndef FUNCTION_OVERRIDES_H_DEF
#include "function_overrides.h"
#define FUNCTION_OVERRIDES_H_DEF
#endif
#include "DXGIReplay.h"
#include "D3D11Replay.h"
#include "Helpers.h"
#include "ReplayHelpers.h"
#include "Resources.h"
#include "WindowSystem.h"

NV_REPLAY_BEGIN_RESOURCE_INIT()

//-----------------------------------------------------------------------------
// CreateResources00
//-----------------------------------------------------------------------------
void CreateResources00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    static D3D_FEATURE_LEVEL D3D_FEATURE_LEVEL_temp_1[3] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_9_1 };
    static DXGI_SWAP_CHAIN_DESC DXGI_SWAP_CHAIN_DESC_temp_1 = {{600u, 300u, {60u, 1u}, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED, DXGI_MODE_SCALING_UNSPECIFIED}, {8u, 4294967295u}, DXGI_CPU_ACCESS_NONE | DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER, 2u, hwnd_00000000000409D0, TRUE, DXGI_SWAP_EFFECT_DISCARD, (DXGI_SWAP_CHAIN_FLAG)0};
    static D3D_FEATURE_LEVEL D3D_FEATURE_LEVEL_temp_2 = D3D_FEATURE_LEVEL_11_0;
    result = D3D11Replay_D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, nullptr, 1u, D3D_FEATURE_LEVEL_temp_1, 3u, 7u, &DXGI_SWAP_CHAIN_DESC_temp_1, &pIDXGISwapChain_uid_19, &pID3D11Device_uid_12, &D3D_FEATURE_LEVEL_temp_2, &pID3D11DeviceContext_uid_13);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11Device_uid_12, "Device 2");

    result = My_IDXGISwapChain_ResizeBuffers(pIDXGISwapChain_uid_19, 2u, 600u, 300u, DXGI_FORMAT_R8G8B8A8_UNORM, 0u);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pIDXGISwapChain_uid_19, "0x0000026DC3163C50");

    result = My_IDXGISwapChain_ResizeBuffers(pIDXGISwapChain_uid_19, 2u, 600u, 300u, DXGI_FORMAT_R8G8B8A8_UNORM, 0u);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pIDXGISwapChain_uid_19, "0x0000026DC3163C50");

    result = My_ID3D11Device_CreateClassLinkage(pID3D11Device_uid_12, &pID3D11ClassLinkage_uid_27);
    NV_CHECK_RESULT(result);

    // Manage lifetime of scoped variables
    {
        BEGIN_DATA_SCOPE();

        std::vector<uint8_t> std_vector_of_uint8_t_temp_1;
        Serialization::BlobProxy<uint8_t*> Serialization_BlobProxy_of_uint8_t__temp_1;
        static D3D11_BUFFER_DESC D3D11_BUFFER_DESC_temp_1 = {128u, D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, (D3D11_CPU_ACCESS_FLAG)0, (D3D11_RESOURCE_MISC_FLAG)0, 0u};
        result = My_ID3D11Device_CreateBuffer(pID3D11Device_uid_12, &D3D11_BUFFER_DESC_temp_1, InitializeSubresourceDataD3D11(4, std_vector_of_uint8_t_temp_1, Serialization_BlobProxy_of_uint8_t__temp_1), &pID3D11Buffer_uid_28);
        NV_CHECK_RESULT(result);
    }
    NV_SET_OBJECT_NAME(pID3D11Buffer_uid_28, "Buffer 1");

    // Manage lifetime of scoped variables
    {
        BEGIN_DATA_SCOPE();

        std::vector<uint8_t> std_vector_of_uint8_t_temp_2;
        Serialization::BlobProxy<uint8_t*> Serialization_BlobProxy_of_uint8_t__temp_2;
        static D3D11_BUFFER_DESC D3D11_BUFFER_DESC_temp_2 = {80u, D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, (D3D11_CPU_ACCESS_FLAG)0, (D3D11_RESOURCE_MISC_FLAG)0, 0u};
        result = My_ID3D11Device_CreateBuffer(pID3D11Device_uid_12, &D3D11_BUFFER_DESC_temp_2, InitializeSubresourceDataD3D11(5, std_vector_of_uint8_t_temp_2, Serialization_BlobProxy_of_uint8_t__temp_2), &pID3D11Buffer_uid_29);
        NV_CHECK_RESULT(result);
    }
    NV_SET_OBJECT_NAME(pID3D11Buffer_uid_29, "Buffer 2");

    static D3D11_SAMPLER_DESC D3D11_SAMPLER_DESC_temp_1 = {D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, 0.0f, 0u, D3D11_COMPARISON_NEVER, {0.0f,0.0f,0.0f,0.0f}, HexToFloat(0xFF7FFFFF/*-3.40282e+38f*/), HexToFloat(0x447A0000/*1000.0f*/)};
    result = My_ID3D11Device_CreateSamplerState(pID3D11Device_uid_12, &D3D11_SAMPLER_DESC_temp_1, &pID3D11SamplerState_uid_30);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11SamplerState_uid_30, "SamplerState 3");

    result = My_ID3D11Device_CreateVertexShader(pID3D11Device_uid_12, NV_GET_RESOURCE(const void*, 6), 1820ull, pID3D11ClassLinkage_uid_27, &pID3D11VertexShader_uid_35);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11VertexShader_uid_35, "VertexShader 3");

    result = My_ID3D11Device_CreatePixelShader(pID3D11Device_uid_12, NV_GET_RESOURCE(const void*, 7), 780ull, pID3D11ClassLinkage_uid_27, &pID3D11PixelShader_uid_36);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11PixelShader_uid_36, "PixelShader 3");

    static D3D11_INPUT_ELEMENT_DESC D3D11_INPUT_ELEMENT_DESC_temp_1[8] = { {"POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u}, {"COLOR", 0u, DXGI_FORMAT_R8G8B8A8_UINT, 0u, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0u}, {"TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 16u, D3D11_INPUT_PER_VERTEX_DATA, 0u}, {"NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 24u, D3D11_INPUT_PER_VERTEX_DATA, 0u}, {"TANGENT", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 36u, D3D11_INPUT_PER_VERTEX_DATA, 0u}, {"BINORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 48u, D3D11_INPUT_PER_VERTEX_DATA, 0u}, {"BONEWEIGHTS", 0u, DXGI_FORMAT_R8G8B8A8_UINT, 0u, 60u, D3D11_INPUT_PER_VERTEX_DATA, 0u}, {"BONEINDICES", 0u, DXGI_FORMAT_R8G8B8A8_UINT, 0u, 64u, D3D11_INPUT_PER_VERTEX_DATA, 0u} };
    result = My_ID3D11Device_CreateInputLayout(pID3D11Device_uid_12, D3D11_INPUT_ELEMENT_DESC_temp_1, 8u, NV_GET_RESOURCE(const void*, 8), 1820ull, &pID3D11InputLayout_uid_37);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11InputLayout_uid_37, "InputLayout 1");

    static D3D11_BLEND_DESC D3D11_BLEND_DESC_temp_1 = {0, 0, {{1, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD, 15},{1, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD, 15},{1, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD, 15},{1, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD, 15},{1, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD, 15},{1, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD, 15},{1, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD, 15},{1, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_OP_ADD, 15}}};
    result = My_ID3D11Device_CreateBlendState(pID3D11Device_uid_12, &D3D11_BLEND_DESC_temp_1, &pID3D11BlendState_uid_38);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11BlendState_uid_38, "BlendState 3");

    static D3D11_RASTERIZER_DESC D3D11_RASTERIZER_DESC_temp_1 = {D3D11_FILL_SOLID, D3D11_CULL_NONE, 1, 0, 0.0f, 0.0f, TRUE, FALSE, TRUE, TRUE};
    result = My_ID3D11Device_CreateRasterizerState(pID3D11Device_uid_12, &D3D11_RASTERIZER_DESC_temp_1, &pID3D11RasterizerState_uid_39);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11RasterizerState_uid_39, "RasterizerState 3");

    static D3D11_DEPTH_STENCIL_DESC D3D11_DEPTH_STENCIL_DESC_temp_1 = {1, D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_ALWAYS, 0, 255, 255, {D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS}, {D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS}};
    result = My_ID3D11Device_CreateDepthStencilState(pID3D11Device_uid_12, &D3D11_DEPTH_STENCIL_DESC_temp_1, &pID3D11DepthStencilState_uid_46);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11DepthStencilState_uid_46, "DepthStencilState 8");

    // Manage lifetime of scoped variables
    {
        BEGIN_DATA_SCOPE();

        std::vector<uint8_t> std_vector_of_uint8_t_temp_3;
        Serialization::BlobProxy<uint8_t*> Serialization_BlobProxy_of_uint8_t__temp_3;
        static D3D11_TEXTURE2D_DESC D3D11_TEXTURE2D_DESC_temp_1 = {1u, 1u, 1u, 1u, DXGI_FORMAT_R8G8B8A8_UNORM, {1u, 0u}, D3D11_USAGE_IMMUTABLE, D3D11_BIND_SHADER_RESOURCE, (D3D11_CPU_ACCESS_FLAG)0, (D3D11_RESOURCE_MISC_FLAG)0};
        result = My_ID3D11Device_CreateTexture2D(pID3D11Device_uid_12, &D3D11_TEXTURE2D_DESC_temp_1, InitializeSubresourceDataD3D11(9, std_vector_of_uint8_t_temp_3, Serialization_BlobProxy_of_uint8_t__temp_3), &pID3D11Texture2D_uid_53);
        NV_CHECK_RESULT(result);
    }
    NV_SET_OBJECT_NAME(pID3D11Texture2D_uid_53, "Texture2D 4");

    static D3D11_TEX2D_SRV D3D11_TEX2D_SRV_temp_1 = {0u, 1u};
    static D3D11_SHADER_RESOURCE_VIEW_DESC D3D11_SHADER_RESOURCE_VIEW_DESC_temp_1;
        D3D11_SHADER_RESOURCE_VIEW_DESC_temp_1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        D3D11_SHADER_RESOURCE_VIEW_DESC_temp_1.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
        D3D11_SHADER_RESOURCE_VIEW_DESC_temp_1.Texture2D = D3D11_TEX2D_SRV_temp_1;
    result = My_ID3D11Device_CreateShaderResourceView(pID3D11Device_uid_12, ((ID3D11Resource*)pID3D11Texture2D_uid_53), &D3D11_SHADER_RESOURCE_VIEW_DESC_temp_1, &pID3D11ShaderResourceView_uid_54);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11ShaderResourceView_uid_54, "SRV 1");

    // Manage lifetime of scoped variables
    {
        BEGIN_DATA_SCOPE();

        std::vector<uint8_t> std_vector_of_uint8_t_temp_4;
        Serialization::BlobProxy<uint8_t*> Serialization_BlobProxy_of_uint8_t__temp_4;
        static D3D11_BUFFER_DESC D3D11_BUFFER_DESC_temp_3 = {408u, D3D11_USAGE_DYNAMIC, D3D11_BIND_VERTEX_BUFFER, D3D11_CPU_ACCESS_WRITE, (D3D11_RESOURCE_MISC_FLAG)0, 0u};
        result = My_ID3D11Device_CreateBuffer(pID3D11Device_uid_12, &D3D11_BUFFER_DESC_temp_3, InitializeSubresourceDataD3D11(10, std_vector_of_uint8_t_temp_4, Serialization_BlobProxy_of_uint8_t__temp_4), &pID3D11Buffer_uid_63);
        NV_CHECK_RESULT(result);
    }
    NV_SET_OBJECT_NAME(pID3D11Buffer_uid_63, "Buffer 3");

    // Manage lifetime of scoped variables
    {
        BEGIN_DATA_SCOPE();

        std::vector<uint8_t> std_vector_of_uint8_t_temp_5;
        Serialization::BlobProxy<uint8_t*> Serialization_BlobProxy_of_uint8_t__temp_5;
        static D3D11_BUFFER_DESC D3D11_BUFFER_DESC_temp_4 = {12u, D3D11_USAGE_DYNAMIC, D3D11_BIND_INDEX_BUFFER, D3D11_CPU_ACCESS_WRITE, (D3D11_RESOURCE_MISC_FLAG)0, 0u};
        result = My_ID3D11Device_CreateBuffer(pID3D11Device_uid_12, &D3D11_BUFFER_DESC_temp_4, InitializeSubresourceDataD3D11(11, std_vector_of_uint8_t_temp_5, Serialization_BlobProxy_of_uint8_t__temp_5), &pID3D11Buffer_uid_64);
        NV_CHECK_RESULT(result);
    }
    NV_SET_OBJECT_NAME(pID3D11Buffer_uid_64, "Buffer 4");

    // Manage lifetime of scoped variables
    {
        BEGIN_DATA_SCOPE();

        std::vector<uint8_t> std_vector_of_uint8_t_temp_6;
        Serialization::BlobProxy<uint8_t*> Serialization_BlobProxy_of_uint8_t__temp_6;
        static D3D11_BUFFER_DESC D3D11_BUFFER_DESC_temp_5 = {408u, D3D11_USAGE_DYNAMIC, D3D11_BIND_VERTEX_BUFFER, D3D11_CPU_ACCESS_WRITE, (D3D11_RESOURCE_MISC_FLAG)0, 0u};
        result = My_ID3D11Device_CreateBuffer(pID3D11Device_uid_12, &D3D11_BUFFER_DESC_temp_5, InitializeSubresourceDataD3D11(12, std_vector_of_uint8_t_temp_6, Serialization_BlobProxy_of_uint8_t__temp_6), &pID3D11Buffer_uid_65);
        NV_CHECK_RESULT(result);
    }
    NV_SET_OBJECT_NAME(pID3D11Buffer_uid_65, "Buffer 5");

    // Manage lifetime of scoped variables
    {
        BEGIN_DATA_SCOPE();

        std::vector<uint8_t> std_vector_of_uint8_t_temp_7;
        Serialization::BlobProxy<uint8_t*> Serialization_BlobProxy_of_uint8_t__temp_7;
        static D3D11_BUFFER_DESC D3D11_BUFFER_DESC_temp_6 = {12u, D3D11_USAGE_DYNAMIC, D3D11_BIND_INDEX_BUFFER, D3D11_CPU_ACCESS_WRITE, (D3D11_RESOURCE_MISC_FLAG)0, 0u};
        result = My_ID3D11Device_CreateBuffer(pID3D11Device_uid_12, &D3D11_BUFFER_DESC_temp_6, InitializeSubresourceDataD3D11(13, std_vector_of_uint8_t_temp_7, Serialization_BlobProxy_of_uint8_t__temp_7), &pID3D11Buffer_uid_66);
        NV_CHECK_RESULT(result);
    }
    NV_SET_OBJECT_NAME(pID3D11Buffer_uid_66, "Buffer 6");

    result = My_IDXGISwapChain_GetBuffer(pIDXGISwapChain_uid_19, 0u, __uuidof(ID3D11Texture2D), ((void**)&pIUnknown_uid_67));
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pIUnknown_uid_67, "Texture2D 9");

    static D3D11_TEX2DMS_RTV D3D11_TEX2DMS_RTV_temp_1 = {0u};
    static D3D11_RENDER_TARGET_VIEW_DESC D3D11_RENDER_TARGET_VIEW_DESC_temp_1;
        D3D11_RENDER_TARGET_VIEW_DESC_temp_1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        D3D11_RENDER_TARGET_VIEW_DESC_temp_1.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
        D3D11_RENDER_TARGET_VIEW_DESC_temp_1.Texture2DMS = D3D11_TEX2DMS_RTV_temp_1;
    result = My_ID3D11Device_CreateRenderTargetView(pID3D11Device_uid_12, ((ID3D11Resource*)pIUnknown_uid_67), &D3D11_RENDER_TARGET_VIEW_DESC_temp_1, &pID3D11RenderTargetView_uid_68);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11RenderTargetView_uid_68, "RTV 3");

    // Manage lifetime of scoped variables
    {
        BEGIN_DATA_SCOPE();

        static D3D11_TEXTURE2D_DESC D3D11_TEXTURE2D_DESC_temp_2 = {600u, 300u, 1u, 1u, DXGI_FORMAT_D32_FLOAT_S8X24_UINT, {8u, 4294967295u}, D3D11_USAGE_DEFAULT, D3D11_BIND_DEPTH_STENCIL, (D3D11_CPU_ACCESS_FLAG)0, (D3D11_RESOURCE_MISC_FLAG)0};
        result = My_ID3D11Device_CreateTexture2D(pID3D11Device_uid_12, &D3D11_TEXTURE2D_DESC_temp_2, NULL, ((ID3D11Texture2D**)&pID3D11Resource_uid_69));
        NV_CHECK_RESULT(result);
    }
    NV_SET_OBJECT_NAME(pID3D11Resource_uid_69, "Texture2D 10");

    static D3D11_TEX2DMS_DSV D3D11_TEX2DMS_DSV_temp_1 = {0u};
    static D3D11_DEPTH_STENCIL_VIEW_DESC D3D11_DEPTH_STENCIL_VIEW_DESC_temp_1;
        D3D11_DEPTH_STENCIL_VIEW_DESC_temp_1.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
        D3D11_DEPTH_STENCIL_VIEW_DESC_temp_1.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
        D3D11_DEPTH_STENCIL_VIEW_DESC_temp_1.Flags = 0u;
        D3D11_DEPTH_STENCIL_VIEW_DESC_temp_1.Texture2DMS = D3D11_TEX2DMS_DSV_temp_1;
    result = My_ID3D11Device_CreateDepthStencilView(pID3D11Device_uid_12, pID3D11Resource_uid_69, &D3D11_DEPTH_STENCIL_VIEW_DESC_temp_1, &pID3D11DepthStencilView_uid_70);
    NV_CHECK_RESULT(result);
    NV_SET_OBJECT_NAME(pID3D11DepthStencilView_uid_70, "DSV 3");
}

//-----------------------------------------------------------------------------
// OnBeforeWinResourcesInit00
//-----------------------------------------------------------------------------
void OnBeforeWinResourcesInit00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

}

//-----------------------------------------------------------------------------
// CreateWinResources00
//-----------------------------------------------------------------------------
void CreateWinResources00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    // Create hwnd_00000000000409D0
    {
        BEGIN_DATA_SCOPE();

        NV_THROW_IF(!RegisterReplayerWindowClass(currentInstance, CS_HREDRAW | CS_OWNDC | CS_VREDRAW), "Failed to register window class");
        const uint32_t x = 0u;
        const uint32_t y = 0u;
        const uint32_t Width = 600u;
        const uint32_t Height = 300u;
        const DWORD Style = WS_BORDER | WS_DLGFRAME | WS_OVERLAPPED | WS_SYSMENU | WS_TILED | WS_VISIBLE;
        const DWORD ExtendedStyle = 0;
        PROCESS_DPI_AWARENESS DpiAwareness = PROCESS_PER_MONITOR_DPI_AWARE;
        hwnd_00000000000409D0 = CreateReplayerWindow(currentInstance, nullptr, x, y, Width, Height, Style, ExtendedStyle, DpiAwareness);
        NV_THROW_IF(!hwnd_00000000000409D0, "Failed to create replayer window");
    }
}

//-----------------------------------------------------------------------------
// OnAfterWinResourcesInit00
//-----------------------------------------------------------------------------
void OnAfterWinResourcesInit00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

}

//-----------------------------------------------------------------------------
// ReleaseResources00
//-----------------------------------------------------------------------------
void ReleaseResources00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    if (pID3D11DepthStencilView_uid_70)
    {
        My_ID3D11DepthStencilView_Release(pID3D11DepthStencilView_uid_70);
    }

    if (pID3D11Resource_uid_69)
    {
        My_ID3D11Resource_Release(pID3D11Resource_uid_69);
    }

    if (pID3D11RenderTargetView_uid_68)
    {
        My_ID3D11RenderTargetView_Release(pID3D11RenderTargetView_uid_68);
    }

    if (pIUnknown_uid_67)
    {
        My_IUnknown_Release(pIUnknown_uid_67);
    }

    if (pID3D11Buffer_uid_66)
    {
        My_ID3D11Buffer_Release(pID3D11Buffer_uid_66);
    }

    if (pID3D11Buffer_uid_65)
    {
        My_ID3D11Buffer_Release(pID3D11Buffer_uid_65);
    }

    if (pID3D11Buffer_uid_64)
    {
        My_ID3D11Buffer_Release(pID3D11Buffer_uid_64);
    }

    if (pID3D11Buffer_uid_63)
    {
        My_ID3D11Buffer_Release(pID3D11Buffer_uid_63);
    }

    if (pID3D11ShaderResourceView_uid_54)
    {
        My_ID3D11ShaderResourceView_Release(pID3D11ShaderResourceView_uid_54);
    }

    if (pID3D11Texture2D_uid_53)
    {
        My_ID3D11Texture2D_Release(pID3D11Texture2D_uid_53);
    }

    if (pID3D11DepthStencilState_uid_46)
    {
        My_ID3D11DepthStencilState_Release(pID3D11DepthStencilState_uid_46);
    }

    if (pID3D11RasterizerState_uid_39)
    {
        My_ID3D11RasterizerState_Release(pID3D11RasterizerState_uid_39);
    }

    if (pID3D11BlendState_uid_38)
    {
        My_ID3D11BlendState_Release(pID3D11BlendState_uid_38);
    }

    if (pID3D11InputLayout_uid_37)
    {
        My_ID3D11InputLayout_Release(pID3D11InputLayout_uid_37);
    }

    if (pID3D11PixelShader_uid_36)
    {
        My_ID3D11PixelShader_Release(pID3D11PixelShader_uid_36);
    }

    if (pID3D11VertexShader_uid_35)
    {
        My_ID3D11VertexShader_Release(pID3D11VertexShader_uid_35);
    }

    if (pID3D11SamplerState_uid_30)
    {
        My_ID3D11SamplerState_Release(pID3D11SamplerState_uid_30);
    }

    if (pID3D11Buffer_uid_29)
    {
        My_ID3D11Buffer_Release(pID3D11Buffer_uid_29);
    }

    if (pID3D11Buffer_uid_28)
    {
        My_ID3D11Buffer_Release(pID3D11Buffer_uid_28);
    }

    if (pID3D11ClassLinkage_uid_27)
    {
        My_ID3D11ClassLinkage_Release(pID3D11ClassLinkage_uid_27);
    }

    if (pIDXGISwapChain_uid_19)
    {
        pIDXGISwapChain_uid_19->SetFullscreenState(0, nullptr);
        My_IDXGISwapChain_Release(pIDXGISwapChain_uid_19);
    }

    if (pID3D11DeviceContext_uid_13)
    {
        My_ID3D11DeviceContext_Release(pID3D11DeviceContext_uid_13);
    }

    if (pID3D11Device_uid_12)
    {
        My_ID3D11Device_Release(pID3D11Device_uid_12);
    }
}

//-----------------------------------------------------------------------------
// ReleaseWinResources00
//-----------------------------------------------------------------------------
void ReleaseWinResources00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    // Release hwnd_00000000000409D0
    DestroyWindow(hwnd_00000000000409D0);
}

//-----------------------------------------------------------------------------
// OnAfterWinResourcesReleased00
//-----------------------------------------------------------------------------
void OnAfterWinResourcesReleased00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

}

//-----------------------------------------------------------------------------
// Captured Resources
//-----------------------------------------------------------------------------
ID3D11Device* pID3D11Device_uid_12 = NULL;
ID3D11DeviceContext* pID3D11DeviceContext_uid_13 = NULL;
IDXGISwapChain* pIDXGISwapChain_uid_19 = NULL;
ID3D11ClassLinkage* pID3D11ClassLinkage_uid_27 = NULL;
ID3D11Buffer* pID3D11Buffer_uid_28 = NULL;
ID3D11Buffer* pID3D11Buffer_uid_29 = NULL;
ID3D11SamplerState* pID3D11SamplerState_uid_30 = NULL;
ID3D11VertexShader* pID3D11VertexShader_uid_35 = NULL;
ID3D11PixelShader* pID3D11PixelShader_uid_36 = NULL;
ID3D11InputLayout* pID3D11InputLayout_uid_37 = NULL;
ID3D11BlendState* pID3D11BlendState_uid_38 = NULL;
ID3D11RasterizerState* pID3D11RasterizerState_uid_39 = NULL;
ID3D11DepthStencilState* pID3D11DepthStencilState_uid_46 = NULL;
ID3D11Texture2D* pID3D11Texture2D_uid_53 = NULL;
ID3D11ShaderResourceView* pID3D11ShaderResourceView_uid_54 = NULL;
ID3D11Buffer* pID3D11Buffer_uid_63 = NULL;
ID3D11Buffer* pID3D11Buffer_uid_64 = NULL;
ID3D11Buffer* pID3D11Buffer_uid_65 = NULL;
ID3D11Buffer* pID3D11Buffer_uid_66 = NULL;
IUnknown* pIUnknown_uid_67 = NULL;
ID3D11RenderTargetView* pID3D11RenderTargetView_uid_68 = NULL;
ID3D11Resource* pID3D11Resource_uid_69 = NULL;
ID3D11DepthStencilView* pID3D11DepthStencilView_uid_70 = NULL;
HWND hwnd_00000000000409D0;
NV_REPLAY_END_RESOURCE_INIT()
