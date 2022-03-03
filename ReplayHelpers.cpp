#include "ReplayHelpers.h"

#include <sstream>

#include "ReadOnlyDatabase.h"
#include "Helpers.h"

bool hasFrameReset = true;
bool forceDebug = false;
bool automated = false;
bool useDebugBytecode = false;
char errorBuf[512];


#if defined(WIN32)
// Tell the driver to use the high performance GPU
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
};

HINSTANCE currentInstance = NULL;

HRESULT result;

//-----------------------------------------------------------------------------
// CheckResult
//-----------------------------------------------------------------------------
void CheckResult(HRESULT r, const char* file, int line)
{
    if (FAILED(r))
    {
        std::stringstream stream;
        stream << "Error 0x" << std::hex << result;
        ThrowErrorWithMessage(stream.str().c_str(), file, line);
    }
}

//-----------------------------------------------------------------------------
// NvNameHelperSetObjectName
//-----------------------------------------------------------------------------
void NvNameHelperSetObjectName(void* pObj, const char* pName)
{
    // NvSetObjectName does not support this type
}

#endif

union HexFloat
{
    float f;
    uint32_t h;
};

union HexDouble
{
    double d;
    uint64_t h;
};

float HexToFloat(uint32_t h)
{
    HexFloat v;
    v.h = h;
    return v.f;
}

double HexToDouble(uint64_t h)
{
    HexDouble v;
    v.h = h;
    return v.d;
}

float NAN_F()
{
    return HexToFloat(0xffc00000);
}

float INF_F()
{
    return HexToFloat(0x7f800000);
}

double NAN_D()
{
    return HexToDouble(0xfff8000000000000);
}

double INF_D()
{
    return HexToDouble(0x7ff0000000000000);
}

//-----------------------------------------------------------------------------
// Threading Resources
//-----------------------------------------------------------------------------
bool releaseReplayerThreads = false;
bool exitReplayerThreads = false;

#if defined(WIN32)
HANDLE threadSequenceEvents[NUM_REPLAYER_THREADS] = { NULL };
HANDLE threadDoneEvents[NUM_REPLAYER_THREADS] = { NULL };
#else
EventsArray threadSequenceEvents;
EventsArray threadDoneEvents;
#endif

//-----------------------------------------------------------------------------
// ReportErrorWithMessage
//-----------------------------------------------------------------------------
void ReportErrorWithMessage(const char* message, const char* file, int line)
{
    std::stringstream stream;
    stream << message << " at " << file << "(" << line << ")";
    NV_MESSAGE(stream.str().c_str());
}

//-----------------------------------------------------------------------------
// ThrowErrorWithMessage
//-----------------------------------------------------------------------------
void ThrowErrorWithMessage(const char* message, const char* file, int line)
{
    std::stringstream stream;
    stream << message << " at " << file << "(" << line << ")";
    throw std::runtime_error(stream.str());
}

//-----------------------------------------------------------------------------
// WriteMessage
//-----------------------------------------------------------------------------
void WriteMessage(const char* message)
{
#ifdef NV_WIN32_SUBSYSTEM
    if (!automated)
    {
        ::OutputDebugStringA(message);
        ::OutputDebugStringA("\n");
        return;
    }
#endif

    fprintf(stderr, "%s", message);
    fprintf(stderr, "\n");
}

//-----------------------------------------------------------------------------
// Database
//-----------------------------------------------------------------------------
static Serialization::ReadOnlyDatabase* s_pDatabase = nullptr;

//-----------------------------------------------------------------------------
// InitializeDatabase
//-----------------------------------------------------------------------------
void InitializeDatabase()
{
    // Set max page size: 64MB
    const static uint64_t MAX_PAGE_SIZE = 1 << 26;

    // Set max resident page count
#if defined(__arm__) || defined(__aarch64__) || defined(__ARM64__)
    const static size_t MAX_RESIDENT_PAGES = 4;
#else
    const static size_t MAX_RESIDENT_PAGES = 16;
#endif

    s_pDatabase = new Serialization::ReadOnlyDatabase(DATABASE_BIN_FILE, MAX_PAGE_SIZE, MAX_RESIDENT_PAGES);

    const auto lastInitResult = s_pDatabase->GetLastInitResult();
    if (lastInitResult != Serialization::ReadOnlyDatabase::InitResult::Ok)
    {
        std::stringstream stream;
        stream << "Failed to initialize database: " << Serialization::ReadOnlyDatabase::InitResultToString(lastInitResult);
        throw std::runtime_error(stream.str());
    }
}

//-----------------------------------------------------------------------------
// GetDatabase
//-----------------------------------------------------------------------------
Serialization::ReadOnlyDatabase& GetDatabase()
{
    return *s_pDatabase;
}

//-----------------------------------------------------------------------------
// FreeCachedMemory
//-----------------------------------------------------------------------------
void FreeCachedMemory()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    GetDatabase().FreeCachedMemory();
}