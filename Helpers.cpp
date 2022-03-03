//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2021.3.1.0
// 
// File: Helpers.cpp
// 
//-----------------------------------------------------------------------------

#include "Helpers.h"
#include "ReplayHelpers.h"
#include "Resources.h"
#include "ReadOnlyDatabase.h"

#if defined(ANDROID) || defined(__linux__) || defined(__QNX__)

#include <dlfcn.h>

#endif

#if !defined(_WIN64) && !defined(__x86_64__) && !defined(__ppc64__) && !defined(__LP64__)
#if !defined(NV_AUTOMATED_BUILD)
#error Application originally targeted 64-bit; compiling now as 32-bit
#else
#if defined(_MSC_VER)
#pragma message("Warning: Application originally targeted 64-bit; compiling now as 32-bit")
#else
#warning Application originally targeted 64-bit; compiling now as 32-bit
#endif
#endif
#endif

#if defined(_MSC_VER)
#pragma message("Warning: Project was generated from an incompatible capture, the frame may not run correctly")
#else
#warning Project was generated from an incompatible capture, the frame may not run correctly
#endif
#if defined(_MSC_VER)
#pragma message("Warning: [Incompatibility] ID2D1Factory7::GetDesktopDpi")
#else
#warning [Incompatibility] ID2D1Factory7::GetDesktopDpi
#endif
#if defined(_MSC_VER)
#pragma message("Warning: [Incompatibility] ID2D1Factory7::Release")
#else
#warning [Incompatibility] ID2D1Factory7::Release
#endif
#if !defined(NV_AUTOMATED_BUILD)
#error You may proceed by compiling out this line, but proceed at your own risk
#else
#if defined(_MSC_VER)
#pragma message("Warning: You may proceed by compiling out this line, but proceed at your own risk")
#else
#warning You may proceed by compiling out this line, but proceed at your own risk
#endif
#endif


//-----------------------------------------------------------------------------
// Common Resources
//-----------------------------------------------------------------------------
const char* ProcessName = "umajin";
double array_of_0s[256] = { 0 };
