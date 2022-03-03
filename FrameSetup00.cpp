//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2021.3.1.0
// 
// File: FrameSetup00.cpp
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
// SetInitialFrameState00
//-----------------------------------------------------------------------------
void SetInitialFrameState00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    FreeCachedMemory();
}

NV_REPLAY_END_FRAME_SETUP()
