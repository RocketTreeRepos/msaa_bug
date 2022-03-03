//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2021.3.1.0
// 
// File: FrameReset00.cpp
// 
//-----------------------------------------------------------------------------

#include <vector>
#include <sstream>

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
#include "Application.h"

NV_REPLAY_BEGIN_FRAME_SETUP()

//-----------------------------------------------------------------------------
// ResetInitialFrameState00
//-----------------------------------------------------------------------------
void ResetInitialFrameState00(bool firstTime)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    My_D3DPERF_BeginEvent(0xFFC86464u, L"ResetInitialFrameState");

    // Initialize shader resources to zero
    {
        BEGIN_DATA_SCOPE();

        static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_15[128] = { NULL };
        My_ID3D11DeviceContext_CSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_15);

        static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_16[128] = { NULL };
        My_ID3D11DeviceContext_VSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_16);

        static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_17[128] = { NULL };
        My_ID3D11DeviceContext_HSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_17);

        static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_18[128] = { NULL };
        My_ID3D11DeviceContext_DSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_18);

        static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_19[128] = { NULL };
        My_ID3D11DeviceContext_GSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_19);

        static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_20[128] = { NULL };
        My_ID3D11DeviceContext_PSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_20);
    }

    static ID3D11Buffer* pID3D11Buffer_temp_13[14] = { NULL };
    My_ID3D11DeviceContext_CSSetConstantBuffers(pID3D11DeviceContext_uid_13, 0, 14ull, pID3D11Buffer_temp_13);

    static ID3D11SamplerState* pID3D11SamplerState_temp_9[16] = { NULL };
    My_ID3D11DeviceContext_CSSetSamplers(pID3D11DeviceContext_uid_13, 0, 16ull, pID3D11SamplerState_temp_9);

    My_ID3D11DeviceContext_CSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);

    static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_21[128] = { NULL };
    My_ID3D11DeviceContext_CSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_21);

    static ID3D11UnorderedAccessView* pID3D11UnorderedAccessView_temp_2[8] = { NULL };
    static UINT UINT_temp_8[8] = { 4294967295u, 4294967295u, 4294967295u, 4294967295u, 4294967295u, 4294967295u, 4294967295u, 4294967295u };
    My_ID3D11DeviceContext_CSSetUnorderedAccessViews(pID3D11DeviceContext_uid_13, 0, 8ull, pID3D11UnorderedAccessView_temp_2, UINT_temp_8);

    My_ID3D11DeviceContext_IASetIndexBuffer(pID3D11DeviceContext_uid_13, pID3D11Buffer_uid_66, DXGI_FORMAT_R16_UINT, 0u);
    My_ID3D11DeviceContext_IASetInputLayout(pID3D11DeviceContext_uid_13, pID3D11InputLayout_uid_37);
    My_ID3D11DeviceContext_IASetPrimitiveTopology(pID3D11DeviceContext_uid_13, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    static ID3D11Buffer* pID3D11Buffer_temp_14[32] = { pID3D11Buffer_uid_65 };
    static UINT UINT_temp_9[32] = { 68u };
    static UINT UINT_temp_10[32] = { 0u };
    My_ID3D11DeviceContext_IASetVertexBuffers(pID3D11DeviceContext_uid_13, 0, 32ull, pID3D11Buffer_temp_14, UINT_temp_9, UINT_temp_10);

    static ID3D11Buffer* pID3D11Buffer_temp_15[14] = { pID3D11Buffer_uid_28, pID3D11Buffer_uid_29 };
    My_ID3D11DeviceContext_VSSetConstantBuffers(pID3D11DeviceContext_uid_13, 0, 14ull, pID3D11Buffer_temp_15);

    static ID3D11SamplerState* pID3D11SamplerState_temp_10[16] = { NULL };
    My_ID3D11DeviceContext_VSSetSamplers(pID3D11DeviceContext_uid_13, 0, 16ull, pID3D11SamplerState_temp_10);

    My_ID3D11DeviceContext_VSSetShader(pID3D11DeviceContext_uid_13, pID3D11VertexShader_uid_35, nullptr, 0u);

    static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_22[128] = { NULL };
    My_ID3D11DeviceContext_VSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_22);

    static ID3D11Buffer* pID3D11Buffer_temp_16[14] = { NULL };
    My_ID3D11DeviceContext_HSSetConstantBuffers(pID3D11DeviceContext_uid_13, 0, 14ull, pID3D11Buffer_temp_16);

    static ID3D11SamplerState* pID3D11SamplerState_temp_11[16] = { NULL };
    My_ID3D11DeviceContext_HSSetSamplers(pID3D11DeviceContext_uid_13, 0, 16ull, pID3D11SamplerState_temp_11);

    My_ID3D11DeviceContext_HSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);

    static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_23[128] = { NULL };
    My_ID3D11DeviceContext_HSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_23);

    static ID3D11Buffer* pID3D11Buffer_temp_17[14] = { NULL };
    My_ID3D11DeviceContext_DSSetConstantBuffers(pID3D11DeviceContext_uid_13, 0, 14ull, pID3D11Buffer_temp_17);

    static ID3D11SamplerState* pID3D11SamplerState_temp_12[16] = { NULL };
    My_ID3D11DeviceContext_DSSetSamplers(pID3D11DeviceContext_uid_13, 0, 16ull, pID3D11SamplerState_temp_12);

    My_ID3D11DeviceContext_DSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);

    static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_24[128] = { NULL };
    My_ID3D11DeviceContext_DSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_24);

    static ID3D11Buffer* pID3D11Buffer_temp_18[14] = { NULL };
    My_ID3D11DeviceContext_GSSetConstantBuffers(pID3D11DeviceContext_uid_13, 0, 14ull, pID3D11Buffer_temp_18);

    static ID3D11SamplerState* pID3D11SamplerState_temp_13[16] = { NULL };
    My_ID3D11DeviceContext_GSSetSamplers(pID3D11DeviceContext_uid_13, 0, 16ull, pID3D11SamplerState_temp_13);

    My_ID3D11DeviceContext_GSSetShader(pID3D11DeviceContext_uid_13, NULL, nullptr, 0u);

    static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_25[128] = { NULL };
    My_ID3D11DeviceContext_GSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_25);

    static ID3D11Buffer* pID3D11Buffer_temp_19[4] = { NULL };
    static uint32_t uint32_t_temp_2[4] = { 4294967295u, 4294967295u, 4294967295u, 4294967295u };
    My_ID3D11DeviceContext_SOSetTargets(pID3D11DeviceContext_uid_13, 4ull, pID3D11Buffer_temp_19, uint32_t_temp_2);

    static D3D11_RECT D3D11_RECT_temp_2;
    My_ID3D11DeviceContext_RSSetScissorRects(pID3D11DeviceContext_uid_13, 0u, nullptr);

    My_ID3D11DeviceContext_RSSetState(pID3D11DeviceContext_uid_13, pID3D11RasterizerState_uid_39);

    static D3D11_VIEWPORT D3D11_VIEWPORT_temp_5[1] = { {0.0f, 0.0f, HexToFloat(0x44160000/*600.0f*/), HexToFloat(0x43960000/*300.0f*/), 0.0f, HexToFloat(0x3F800000/*1.0f*/)} };
    My_ID3D11DeviceContext_RSSetViewports(pID3D11DeviceContext_uid_13, 1u, D3D11_VIEWPORT_temp_5);

    static ID3D11Buffer* pID3D11Buffer_temp_20[14] = { NULL };
    My_ID3D11DeviceContext_PSSetConstantBuffers(pID3D11DeviceContext_uid_13, 0, 14ull, pID3D11Buffer_temp_20);

    static ID3D11SamplerState* pID3D11SamplerState_temp_14[16] = { pID3D11SamplerState_uid_30 };
    My_ID3D11DeviceContext_PSSetSamplers(pID3D11DeviceContext_uid_13, 0, 16ull, pID3D11SamplerState_temp_14);

    My_ID3D11DeviceContext_PSSetShader(pID3D11DeviceContext_uid_13, pID3D11PixelShader_uid_36, nullptr, 0u);

    static ID3D11ShaderResourceView* pID3D11ShaderResourceView_temp_26[128] = { pID3D11ShaderResourceView_uid_54 };
    My_ID3D11DeviceContext_PSSetShaderResources(pID3D11DeviceContext_uid_13, 0, 128ull, pID3D11ShaderResourceView_temp_26);

    static float float_temp_2[4] = { HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x3F800000/*1.0f*/) };
    My_ID3D11DeviceContext_OMSetBlendState(pID3D11DeviceContext_uid_13, pID3D11BlendState_uid_38, float_temp_2, 0xFFFFFFFFu);

    My_ID3D11DeviceContext_OMSetDepthStencilState(pID3D11DeviceContext_uid_13, pID3D11DepthStencilState_uid_46, 0u);
    My_ID3D11DeviceContext_OMSetRenderTargets(pID3D11DeviceContext_uid_13, 1u, &pID3D11RenderTargetView_uid_68, pID3D11DepthStencilView_uid_70);
    My_ID3D11DeviceContext_SetPredication(pID3D11DeviceContext_uid_13, NULL, FALSE);
    My_D3DPERF_EndEvent();
}

//-----------------------------------------------------------------------------
// ResetState00
//-----------------------------------------------------------------------------
void ResetState00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    My_D3DPERF_BeginEvent(0xFFC86464u, L"ResetState");
    My_D3DPERF_EndEvent();
}

NV_REPLAY_END_FRAME_SETUP()
