//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2021.3.1.0
// 
// File: Helpers.h
// 
//-----------------------------------------------------------------------------

#pragma once

#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <set>
#include <stdio.h>
#include <sstream>

#include "ReadOnlyDatabase.h"
#include "ThreadPool.h"
#include "CommonReplay.h"

//-----------------------------------------------------------------------------
// Common Resources
//-----------------------------------------------------------------------------
NV_REPLAY_EXPORT extern const char* ProcessName;
NV_REPLAY_EXPORT extern double array_of_0s[256];

const unsigned int NUM_REPLAYER_THREADS = 1;
