#pragma once

#include "CommonReplay.h"

#include <cstdint>
#include <string>
#include <functional>

//-----------------------------------------------------------------------------
// Application
//-----------------------------------------------------------------------------
class Application
{
protected:
    NV_REPLAY_EXPORT Application();
    NV_REPLAY_EXPORT Application(const Application&);
    NV_REPLAY_EXPORT Application& operator=(const Application&);

public:
    NV_REPLAY_EXPORT static Application& PlatformInstance();

    NV_REPLAY_EXPORT int Execute();
    NV_REPLAY_EXPORT int Execute(int argc, char** argv);
    NV_REPLAY_EXPORT static bool VerboseOutput();
    NV_REPLAY_EXPORT static bool HasForceBorderlessWindow();

#if defined(NV_REPLAY_ON_ORIGINAL_THREAD_IDS)
    NV_REPLAY_EXPORT static bool HasMultiThreadedReplay();
    NV_REPLAY_EXPORT static void EnableMultiThreadedReplay(bool enable);
#endif

    NV_REPLAY_EXPORT static bool MinimizeCPUOverheadRequested();
    NV_REPLAY_EXPORT static bool ShouldCatchAndReportSystemExceptions();

    NV_REPLAY_EXPORT static void SetFrameExecutor(std::function<bool(uint64_t)> fnExecutor);
    NV_REPLAY_EXPORT static bool ExecuteFrame(uint64_t frameIndex);

protected:
    NV_REPLAY_EXPORT bool ParseCommandLine(int argc, char** argv);
    NV_REPLAY_EXPORT void OnError(const char* pMessage);

    NV_REPLAY_EXPORT virtual int ExecuteInternal(int argc, char** argv);
    NV_REPLAY_EXPORT virtual void PlatformInit();
    NV_REPLAY_EXPORT virtual void PlatformDone();
    NV_REPLAY_EXPORT virtual void OutputMessage(const std::string& message) const;
    NV_REPLAY_EXPORT virtual bool ProcessMessages() = 0;

private:
    uint64_t m_repeatCount = 0;
    uint64_t m_frameIndex = 0;
    bool m_perfStats = false;
    bool m_forceBorderlessWindow = false;
#if defined(NV_REPLAY_ON_ORIGINAL_THREAD_IDS)
    bool m_multiThreadedReplay = true;
#endif
    bool m_dumpFrameTimes = false;
    bool m_verbose = false;
    bool m_minimizeCPUOverhead = false;
    bool m_catchAndReportSystemExceptions = true;
    std::function<bool(uint64_t)> m_fnFrameExecutor;
};
