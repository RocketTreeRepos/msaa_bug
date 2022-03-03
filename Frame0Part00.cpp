//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2021.3.1.0
// 
// File: Frame0Part00.cpp
// 
//-----------------------------------------------------------------------------

#include <d3d9.h>
#include <d3d11.h>
#include <dxgi.h>

#ifndef FUNCTION_OVERRIDES_H_DEF
#include "function_overrides.h"
#define FUNCTION_OVERRIDES_H_DEF
#endif
#include "DXGIReplay.h"
#include "D3D11Replay.h"
#include "Resources.h"
#include "Helpers.h"
#include "ReplayHelpers.h"
#include "Threading.h"

NV_REPLAY_BEGIN_FRAME()

//-----------------------------------------------------------------------------
// RunFrame0Part00
//-----------------------------------------------------------------------------
void RunFrame0Part00(uint64_t frameIndex)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    static D3D11_VIEWPORT D3D11_VIEWPORT_temp_1[1] = { {0.0f, 0.0f, HexToFloat(0x44160000/*600.0f*/), HexToFloat(0x43960000/*300.0f*/), 0.0f, HexToFloat(0x3F800000/*1.0f*/)} };
    My_ID3D11DeviceContext_RSSetViewports(pID3D11DeviceContext_uid_13, 1u, D3D11_VIEWPORT_temp_1);

    My_ID3D11DeviceContext_OMSetRenderTargets(pID3D11DeviceContext_uid_13, 1u, &pID3D11RenderTargetView_uid_68, pID3D11DepthStencilView_uid_70);

    // Clear #0 [0...1]
    static FLOAT FLOAT_temp_1[4] = { HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/) };
    My_ID3D11DeviceContext_ClearRenderTargetView(pID3D11DeviceContext_uid_13, pID3D11RenderTargetView_uid_68, FLOAT_temp_1);

    // Clear #1 [0...1]
    My_ID3D11DeviceContext_ClearDepthStencilView(pID3D11DeviceContext_uid_13, pID3D11DepthStencilView_uid_70, 1u, HexToFloat(0x3F800000/*1.0f*/), 0);

    static D3D11_VIEWPORT D3D11_VIEWPORT_temp_2[1] = { {0.0f, 0.0f, HexToFloat(0x44160000/*600.0f*/), HexToFloat(0x43960000/*300.0f*/), 0.0f, HexToFloat(0x3F800000/*1.0f*/)} };
    My_ID3D11DeviceContext_RSSetViewports(pID3D11DeviceContext_uid_13, 1u, D3D11_VIEWPORT_temp_2);

    static FLOAT FLOAT_temp_2;
    My_ID3D11DeviceContext_OMSetBlendState(pID3D11DeviceContext_uid_13, pID3D11BlendState_uid_38, nullptr, 0xFFFFFFFFu);

    static UINT UINT_temp_1[1] = { 68u };
    static UINT UINT_temp_2[1] = { 0u };
    My_ID3D11DeviceContext_IASetVertexBuffers(pID3D11DeviceContext_uid_13, 0u, 1u, &pID3D11Buffer_uid_63, UINT_temp_1, UINT_temp_2);

    My_ID3D11DeviceContext_IASetIndexBuffer(pID3D11DeviceContext_uid_13, pID3D11Buffer_uid_64, DXGI_FORMAT_R16_UINT, 0u);
    My_ID3D11DeviceContext_UpdateSubresource(pID3D11DeviceContext_uid_13, ((ID3D11Resource*)pID3D11Buffer_uid_28), 0u, nullptr, NV_GET_RESOURCE(void*, 0), 128u, 128u);
    My_ID3D11DeviceContext_UpdateSubresource(pID3D11DeviceContext_uid_13, ((ID3D11Resource*)pID3D11Buffer_uid_29), 0u, nullptr, NV_GET_RESOURCE(void*, 1), 80u, 80u);

    static ID3D11Buffer* pID3D11Buffer_temp_2[2] = { pID3D11Buffer_uid_28, pID3D11Buffer_uid_29 };
    My_ID3D11DeviceContext_VSSetConstantBuffers(pID3D11DeviceContext_uid_13, 0u, 2u, pID3D11Buffer_temp_2);

    My_ID3D11DeviceContext_VSSetShader(pID3D11DeviceContext_uid_13, pID3D11VertexShader_uid_35, nullptr, 0u);
    My_ID3D11DeviceContext_PSSetSamplers(pID3D11DeviceContext_uid_13, 0u, 1u, &pID3D11SamplerState_uid_30);
    My_ID3D11DeviceContext_PSSetShaderResources(pID3D11DeviceContext_uid_13, 0u, 1u, &pID3D11ShaderResourceView_uid_54);
    My_ID3D11DeviceContext_PSSetShader(pID3D11DeviceContext_uid_13, pID3D11PixelShader_uid_36, nullptr, 0u);
    My_ID3D11DeviceContext_GSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);
    My_ID3D11DeviceContext_HSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);
    My_ID3D11DeviceContext_DSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);

    // Draw #0 [0...1]
    My_ID3D11DeviceContext_DrawIndexed(pID3D11DeviceContext_uid_13, 6u, 0u, 0);

    static D3D11_VIEWPORT D3D11_VIEWPORT_temp_3[1] = { {0.0f, 0.0f, HexToFloat(0x44160000/*600.0f*/), HexToFloat(0x43960000/*300.0f*/), 0.0f, HexToFloat(0x3F800000/*1.0f*/)} };
    My_ID3D11DeviceContext_RSSetViewports(pID3D11DeviceContext_uid_13, 1u, D3D11_VIEWPORT_temp_3);

    static FLOAT FLOAT_temp_3;
    My_ID3D11DeviceContext_OMSetBlendState(pID3D11DeviceContext_uid_13, pID3D11BlendState_uid_38, nullptr, 0xFFFFFFFFu);

    static UINT UINT_temp_3[1] = { 68u };
    static UINT UINT_temp_4[1] = { 0u };
    My_ID3D11DeviceContext_IASetVertexBuffers(pID3D11DeviceContext_uid_13, 0u, 1u, &pID3D11Buffer_uid_65, UINT_temp_3, UINT_temp_4);

    My_ID3D11DeviceContext_IASetIndexBuffer(pID3D11DeviceContext_uid_13, pID3D11Buffer_uid_66, DXGI_FORMAT_R16_UINT, 0u);
    My_ID3D11DeviceContext_UpdateSubresource(pID3D11DeviceContext_uid_13, ((ID3D11Resource*)pID3D11Buffer_uid_28), 0u, nullptr, NV_GET_RESOURCE(void*, 2), 128u, 128u);
    My_ID3D11DeviceContext_UpdateSubresource(pID3D11DeviceContext_uid_13, ((ID3D11Resource*)pID3D11Buffer_uid_29), 0u, nullptr, NV_GET_RESOURCE(void*, 3), 80u, 80u);

    static ID3D11Buffer* pID3D11Buffer_temp_4[2] = { pID3D11Buffer_uid_28, pID3D11Buffer_uid_29 };
    My_ID3D11DeviceContext_VSSetConstantBuffers(pID3D11DeviceContext_uid_13, 0u, 2u, pID3D11Buffer_temp_4);

    My_ID3D11DeviceContext_VSSetShader(pID3D11DeviceContext_uid_13, pID3D11VertexShader_uid_35, nullptr, 0u);
    My_ID3D11DeviceContext_PSSetSamplers(pID3D11DeviceContext_uid_13, 0u, 1u, &pID3D11SamplerState_uid_30);
    My_ID3D11DeviceContext_PSSetShaderResources(pID3D11DeviceContext_uid_13, 0u, 1u, &pID3D11ShaderResourceView_uid_54);
    My_ID3D11DeviceContext_PSSetShader(pID3D11DeviceContext_uid_13, pID3D11PixelShader_uid_36, nullptr, 0u);
    My_ID3D11DeviceContext_GSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);
    My_ID3D11DeviceContext_HSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);
    My_ID3D11DeviceContext_DSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);

    // Draw #1 [0...1]
    My_ID3D11DeviceContext_DrawIndexed(pID3D11DeviceContext_uid_13, 6u, 0u, 0);

    result = My_IDXGISwapChain_Present(pIDXGISwapChain_uid_19, 1u, 0u);
    NV_CHECK_PRESENT_RESULT(result, pIDXGISwapChain_uid_19);
}

NV_REPLAY_END_FRAME()
