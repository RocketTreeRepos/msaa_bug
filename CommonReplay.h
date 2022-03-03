//---------------------------------------------------------------------------
// File: CommonReplay.h
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//---------------------------------------------------------------------------

#pragma once

#include <stddef.h>
#include "ReplayConfig.h"

extern size_t g_threadPoolThreadCount;

#if defined(NV_REPLAY_LIB_SHARED)
 #if defined(_WIN32)
  #if defined(ReplayExecutor_EXPORTS)
   #define NV_REPLAY_EXPORT __declspec(dllexport)
  #else
   #define NV_REPLAY_EXPORT __declspec(dllimport)
  #endif
 #else
  #define NV_REPLAY_EXPORT __attribute__((visibility("default")))
 #endif
#else
 #define NV_REPLAY_EXPORT
#endif

#if defined(_MSC_VER)
#define NV_REPLAY_NOINLINE __declspec(noinline)
#define NV_REPLAY_FORCEINLINE __forceinline
#elif defined(__GNUC__) || defined(__INTEGRITY)
#define NV_REPLAY_NOINLINE __attribute__((noinline))
#define NV_REPLAY_FORCEINLINE inline __attribute__((always_inline))
#else
#define NV_REPLAY_NOINLINE
#define NV_REPLAY_FORCEINLINE inline
#endif

enum class NVCheckedMemcpyState {
    PASS_0,
    PASS_1,
    DETECTED_DIFFS,
    DETECTED_NO_DIFFS
};

#define NV_MEMCPY_IN_FRAME(dst, src, size) \
    do { \
        static NVCheckedMemcpyState state = NVCheckedMemcpyState::PASS_0; \
        NVCheckedMemcpy(dst, src, size, state); \
    } while (false)

void NVCheckedMemcpy(void* dst, const void* src, size_t size, NVCheckedMemcpyState& state);