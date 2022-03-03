cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0054 NEW)

#Support for visual studio build
set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

#Build shared libraries opposed to single exe
set(NV_SHARED_REPLAY_LIB 0)

#Choose an available Windows SDK in order to meet the Direct3D feature level
set(REQUIRED_WIN_SDK_VERSION )
if(WIN32 AND REQUIRED_WIN_SDK_VERSION AND NOT CMAKE_SYSTEM_VERSION)
#Detect all the Windows SDKs that exist on the machine.
    set(WIN_SDK_VERSIONS "")

#We have to check "Windows.h" to verify if the SDK is really installed because there's no reliable registry value since v10.
    macro(AddWinSDKIfInstalled SDK_INCLUDE_PATH SDK_VERSION)
        if(EXISTS "${SDK_INCLUDE_PATH}/um/Windows.h")
            list(APPEND WIN_SDK_VERSIONS "${SDK_VERSION}")
        endif()
    endmacro()

#Helper to identify all sub - sdks within a windows SDK directory
    macro(AddWin10SDKIfInstalled SDK_DIR)
        if(IS_DIRECTORY ${SDK_DIR})
            file(GLOB SUB_FOLDERS RELATIVE ${SDK_DIR}/Include ${SDK_DIR}/Include/*)
            foreach(SUB_FOLDER ${SUB_FOLDERS})
                AddWinSDKIfInstalled(${SDK_DIR}/Include/${SUB_FOLDER} ${SUB_FOLDER})
            endforeach()
        endif()
    endmacro()

    # Start at v8.1 because the minimum Visual Studio supported version is 2015.
    get_filename_component(WIN_SDK_V81_ROOT "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot81]" ABSOLUTE CACHE)
    if(NOT WIN_SDK_V81_ROOT)
        set(WIN_SDK_V81_ROOT "%ProgramFiles%/Windows Kits/8.1")
    endif()
    if(IS_DIRECTORY ${WIN_SDK_V81_ROOT})
        AddWinSDKIfInstalled(${WIN_SDK_V81_ROOT}/Include 8.1)
    endif()

    # Add system-identified windows 10 SDKs
    get_filename_component(WIN_SDK_V10_ROOT "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot10]" ABSOLUTE CACHE)
    if(NOT WIN_SDK_V10_ROOT)
        set(WIN_SDK_V10_ROOT "%ProgramFiles%/Windows Kits/10")
    endif()
    AddWin10SDKIfInstalled(${WIN_SDK_V10_ROOT})

    # Add a user-specified WINDOWS_SDK_DIR if one is defined
    if(DEFINED ENV{WINDOWS_SDK_DIR})
        AddWin10SDKIfInstalled($ENV{WINDOWS_SDK_DIR})
    endif()

    message(STATUS "Finding Windows SDK to satisfy required SDK of: ${REQUIRED_WIN_SDK_VERSION}")
    if (WIN_SDK_VERSIONS)
        message(STATUS "Windows SDK candidates: ${WIN_SDK_VERSIONS}")
    else()
        message(STATUS "Windows SDK candidates: none found")
    endif()

    # Select a version that satisfies the requirement
    list(REVERSE WIN_SDK_VERSIONS)
    foreach(WIN_SDK_VERSION ${WIN_SDK_VERSIONS})
        if (WIN_SDK_VERSION VERSION_GREATER_EQUAL REQUIRED_WIN_SDK_VERSION)
            message(STATUS "Windows SDK selected: ${WIN_SDK_VERSION}")
            set(CMAKE_SYSTEM_VERSION ${WIN_SDK_VERSION})
            break()
        endif()
    endforeach()

    if(NOT CMAKE_SYSTEM_VERSION)
        message(FATAL_ERROR "Failed to find a Windows SDK that available to use. The minimum version required is ${REQUIRED_WIN_SDK_VERSION}")
    endif()
endif()

# Set project name
set(CPP_PROJECT_NAME "umajin__2022_03_04__10_01_01")
set(CPP_PROJECT_NAME_NOTIMESTAMP "umajin")

# Set output name
option(NV_USE_TIMESTAMP_IN_APPLICATION_NAME "Rename output file to be timestamped" OFF)
if (NV_USE_TIMESTAMP_IN_APPLICATION_NAME)
    set(CPP_OUTPUT_NAME ${CPP_PROJECT_NAME})
else()
    set(CPP_OUTPUT_NAME ${CPP_PROJECT_NAME_NOTIMESTAMP})
endif()

# The target name is trim so that cmake path lengths are short; the actual
# executable will be renamed via a property below
set(EXECUTABLE_TARGET cppcap)

# Information of original capture
set(NV_ORIGINAL_OS WIN32)
set(NV_ORIGINAL_WINSYS win32)
set(NV_ORIGINAL_ARCH 64)

# Detect current platform the CMake is running under
if(WIN32)
    set(NV_HOST_PLATFORM "WIN32")
elseif(UNIX AND (NOT APPLE))
    set(NV_HOST_PLATFORM "LINUX_DESKTOP")
else()
    message(FATAL_ERROR "The CMake must be running under Windows/Linux Desktop")
endif()
message(STATUS "NV_HOST_PLATFORM: ${NV_HOST_PLATFORM}")

# Determine default target platform if not specified by "-DNV_TARGET_PLATFORM"
if(NOT NV_TARGET_PLATFORM)
    if(NV_HOST_PLATFORM STREQUAL "WIN32")
        set(NV_TARGET_PLATFORM "WIN32")
    elseif(NV_HOST_PLATFORM STREQUAL "LINUX_DESKTOP")
        if(NV_ORIGINAL_OS STREQUAL "WIN32")
            set(NV_TARGET_PLATFORM "LINUX_DESKTOP")
        else()
            set(NV_TARGET_PLATFORM "${NV_ORIGINAL_OS}")
        endif()
    endif()
endif()
message(STATUS "NV_TARGET_PLATFORM: ${NV_TARGET_PLATFORM}")

# Make NV_TARGET_PLATFORM to be an option selectable in cmake-GUI
# The supported target platforms are determined based on the host platform
set(NV_TARGET_PLATFORM "${NV_TARGET_PLATFORM}" CACHE STRING "Select target platform to build for")
if(NV_HOST_PLATFORM STREQUAL "WIN32")
    set_property(CACHE NV_TARGET_PLATFORM PROPERTY STRINGS "WIN32")
elseif(NV_HOST_PLATFORM STREQUAL "LINUX_DESKTOP")
    set_property(CACHE NV_TARGET_PLATFORM PROPERTY STRINGS "LINUX_DESKTOP" "LINUX_EMBEDDED")
else()
    message(FATAL_ERROR "Unknown host platform: '${NV_HOST_PLATFORM}'")
endif()

# Check if we are building for the original platform
if(NV_TARGET_PLATFORM STREQUAL "${NV_ORIGINAL_OS}")
    set(NV_BUILD_FOR_ORIGINAL_PLATFORM 1)
else()
    set(NV_BUILD_FOR_ORIGINAL_PLATFORM 0)
endif()

# Determine default window system if not specified by "-DNV_WINSYS"
if(NOT NV_WINSYS)
    if(NV_BUILD_FOR_ORIGINAL_PLATFORM)
        set(NV_WINSYS ${NV_ORIGINAL_WINSYS})
    else()
        # Choose default window system for the target platform
        if(NV_TARGET_PLATFORM STREQUAL "LINUX_DESKTOP")
            set(NV_WINSYS xcb)
        elseif(NV_TARGET_PLATFORM STREQUAL "WIN32")
            set(NV_WINSYS win32)
        elseif(NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED")
            set(NV_WINSYS x11)
        endif()
    endif()
endif()
message(STATUS "NV_WINSYS: ${NV_WINSYS}")

# Make NV_WINSYS to be an option selectable in cmake-GUI
# The supported window systems are determined based on the target platform
set(NV_WINSYS "${NV_WINSYS}" CACHE STRING "Select window system type to interact with graphics API")
if(NV_TARGET_PLATFORM STREQUAL "LINUX_DESKTOP")
    set_property(CACHE NV_WINSYS PROPERTY STRINGS xcb x11 vulkan-d2d)
elseif(NV_TARGET_PLATFORM STREQUAL "WIN32")
    set_property(CACHE NV_WINSYS PROPERTY STRINGS win32)
elseif(NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED")
    set_property(CACHE NV_WINSYS PROPERTY STRINGS x11 wayland vulkan-d2d egldevice)
elseif()
    message(FATAL_ERROR "Unknown target platform: '${NV_TARGET_PLATFORM}'")
endif()

if(NV_WINSYS STREQUAL xcb)
    set(NV_USE_XCB 1)
elseif(NV_WINSYS STREQUAL x11)
    set(NV_USE_X11 1)
elseif(NV_WINSYS STREQUAL vulkan-d2d)
    set(NV_USE_D2D 1)
elseif(NV_WINSYS STREQUAL win32)
    set(NV_USE_WIN32 1)
elseif(NV_WINSYS STREQUAL wayland)
    set(NV_USE_WAYLAND 1)
elseif(NV_WINSYS STREQUAL egldevice)
    set(NV_USE_EGL_DEVICE 1)
else()
    if(NV_TARGET_PLATFORM STREQUAL "WIN32")
        message(FATAL_ERROR "Specified wrong 'NV_WINSYS' argument. Must be 'win32' for Windows.")
    elseif(NV_TARGET_PLATFORM STREQUAL "LINUX_DESKTOP")
        message(FATAL_ERROR "Specified wrong 'NV_WINSYS' argument. Must be one of 'xcb'/'x11'/'vulkan-d2d' for Linux Desktop.")
    elseif(NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED")
        message(FATAL_ERROR "Specified wrong 'NV_WINSYS' argument. Must be one of 'xcb'/'x11'/'vulkan-d2d'/'wayland'/'egldevice' for Embedded Linux.")
    endif()
endif()

# Handle cross-compiling for embedded linux
if(NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED")

    # Check if the SDK is specified in environment
    if((NOT NV_SDKDIR) AND (DEFINED ENV{NV_SDKDIR}))
        set(NV_SDKDIR $ENV{NV_SDKDIR})
    endif()

    # Validate the SDK
    if(NOT NV_SDKDIR)
        message(FATAL_ERROR "Must specify 'NV_SDKDIR' offering the path to DriveOS/L4T sdk directory for compiling")
    endif()
    if(NOT EXISTS "${NV_SDKDIR}")
        message(FATAL_ERROR "'${NV_SDKDIR}' not found")
    endif()

    # Identify this is building for L4T or Drive OS
    if(EXISTS "${NV_SDKDIR}/drive-t186ref-linux")
        message(STATUS "Building for DriveOS")
        set(NV_LINUX_EMBEDDED_TARGET "DriveOS")
        set(NV_DRIVE_OS_DIR "${NV_SDKDIR}/drive-t186ref-linux")
    elseif(EXISTS "${NV_SDKDIR}/DRIVEOS/drive-t186ref-linux")
        message(STATUS "Building for DriveOS")
        set(NV_LINUX_EMBEDDED_TARGET "DriveOS")
        set(NV_DRIVE_OS_DIR "${NV_SDKDIR}/DRIVEOS/drive-t186ref-linux")
    elseif(EXISTS "${NV_SDKDIR}/DRIVEOS-safety/drive-t186ref-linux")
        message(STATUS "Building for DriveOS")
        set(NV_LINUX_EMBEDDED_TARGET "DriveOS")
        set(NV_DRIVE_OS_DIR "${NV_SDKDIR}/DRIVEOS-safety/drive-t186ref-linux")
    elseif(EXISTS "${NV_SDKDIR}/Linux_for_Tegra/rootfs")
        message(STATUS "Building for JetPack-L4T")
        set(NV_LINUX_EMBEDDED_TARGET "L4T")
    else()
        message(FATAL_ERROR "Cannot find DriveOS or JetPack-L4T SDK directory")
    endif()

    # Locate toolchain directory
    if(NV_LINUX_EMBEDDED_TARGET STREQUAL "DriveOS")

        if(EXISTS "${NV_DRIVE_OS_DIR}/../toolchains/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu")
            set(NV_BUILD_CROSS_BIN "${NV_DRIVE_OS_DIR}/../toolchains/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-")
        elseif(EXISTS "${NV_DRIVE_OS_DIR}/../toolchains/tegra-4.9-nv/usr/bin/aarch64-gnu-linux")
            set(NV_BUILD_CROSS_BIN "${NV_DRIVE_OS_DIR}/../toolchains/tegra-4.9-nv/usr/bin/aarch64-gnu-linux/aarch64-gnu-linux-")
        else()
            message(FATAL_ERROR "Cannot find DriveOS SDK toolchain")
        endif()

        set(NV_LINUX_EMBEDDED_INC_DIR "${NV_DRIVE_OS_DIR}/include")
        set(NV_LINUX_EMBEDDED_LIB_DIR "${NV_DRIVE_OS_DIR}/lib-target" "${NV_DRIVE_OS_DIR}/lib-target/${NV_WINSYS}")
        if(NV_USE_WAYLAND)
            set(NV_LINUX_EMBEDDED_LINKER_FLAGS "-Wl,-rpath-link=${NV_DRIVE_OS_DIR}/oss/liblzma/liblzma/lib/aarch64-linux-gnu:${NV_DRIVE_OS_DIR}/oss/zlib/zlib1g/lib/aarch64-linux-gnu:${NV_DRIVE_OS_DIR}/oss/xml2/libxml2/usr/lib/aarch64-linux-gnu")
        else()
            set(NV_LINUX_EMBEDDED_LINKER_FLAGS "")
        endif()

    elseif(NV_LINUX_EMBEDDED_TARGET STREQUAL "L4T")

        # Make sure aarch64-linux-gnu-g++ can be found from PATH environment
        find_program(NV_BUILD_CROSS_COMPILER NAMES "aarch64-linux-gnu-g++")
        if(NOT NV_BUILD_CROSS_COMPILER)
            message(FATAL_ERROR "Cannot find aarch64-linux-gnu-g++ in the \${PATH}. You need to install it by \"sudo apt-get install g++-aarch64-linux-gnu\"")
        endif()

        get_filename_component(NV_BUILD_CROSS_BIN_DIR "${NV_BUILD_CROSS_COMPILER}" DIRECTORY)
        set(NV_BUILD_CROSS_BIN "${NV_BUILD_CROSS_BIN_DIR}/aarch64-linux-gnu-")

        set(NV_LINUX_EMBEDDED_INC_DIR      "${NV_SDKDIR}/Linux_for_Tegra/rootfs/usr/include" "${NV_SDKDIR}/Linux_for_Tegra/rootfs/usr/include/drm" "${NV_SDKDIR}/Linux_for_Tegra/rootfs/usr/include/aarch64-linux-gnu")
        set(NV_LINUX_EMBEDDED_LIB_DIR      "")
        set(NV_LINUX_EMBEDDED_LINKER_FLAGS "--sysroot=${NV_SDKDIR}/Linux_for_Tegra/rootfs")

    endif()

    # Specify compiler/linker/... for cross-compiling
    # This must be done before any language is set (i.e., before any project() or enable_language() command)
    set(CMAKE_C_COMPILER   "${NV_BUILD_CROSS_BIN}gcc"    CACHE INTERNAL "")
    set(CMAKE_CXX_COMPILER "${NV_BUILD_CROSS_BIN}g++"    CACHE INTERNAL "")
    set(CMAKE_AR           "${NV_BUILD_CROSS_BIN}ar"     CACHE INTERNAL "")
    set(CMAKE_RANLIB       "${NV_BUILD_CROSS_BIN}ranlib" CACHE INTERNAL "")
    set(CMAKE_STRIP        "${NV_BUILD_CROSS_BIN}strip"  CACHE INTERNAL "")
    set(CMAKE_NM           "${NV_BUILD_CROSS_BIN}nm"     CACHE INTERNAL "")
    set(CMAKE_LINKER       "${NV_BUILD_CROSS_BIN}ld"     CACHE INTERNAL "")

    # Turn ld into a multi-pass linker by adding --{begin,end}-group (listing order of .a libs no longer matters).
    set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER>  <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> -Wl,--start-group <LINK_LIBRARIES> -Wl,--end-group")
    set(CMAKE_CXX_CREATE_SHARED_LIBRARY "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> -Wl,--start-group <LINK_LIBRARIES> -Wl,--end-group")

    # Specify platform-specific library search paths
    link_directories(${NV_LINUX_EMBEDDED_LIB_DIR})

endif()

project(${CPP_PROJECT_NAME})

# Determine bitness
if(CMAKE_SIZEOF_VOID_P STREQUAL "8")
    set(NV_USE_64BIT 1)
elseif(CMAKE_SIZEOF_VOID_P STREQUAL "4")
    set(NV_USE_32BIT 1)
else()
    message(FATAL_ERROR "Unrecognized bitness.")
endif()

if(NV_USE_64BIT)
    link_directories(
)
endif()

if(NV_USE_32BIT)
    link_directories(
)
endif()

# Checking arch mismatch
if((NV_USE_64BIT AND NV_ORIGINAL_ARCH STREQUAL 64) OR (NV_USE_32BIT AND NV_ORIGINAL_ARCH STREQUAL 32))
    message(STATUS "Building ${NV_ORIGINAL_ARCH}-bit app.")
elseif(NV_USE_64BIT AND NV_ORIGINAL_ARCH STREQUAL 32)
    message(WARNING "Application originally targeted 32-bit; compiling now as 64-bit.")
elseif(NV_USE_32BIT AND NV_ORIGINAL_ARCH STREQUAL 64)
    message(FATAL_ERROR "Application originally targeted 64-bit; compiling now as 32-bit.")
else()
    message(FATAL_ERROR "Unrecognized original bitwise.")
endif()
if(CMAKE_BUILD_TYPE)
    message(STATUS "Building with a ${CMAKE_BUILD_TYPE} configuration.")
endif()

# Control library linkage mode
if (NV_SHARED_REPLAY_LIB)
	set(ReplayExecutorLibraryType "SHARED")
	set(NV_REPLAY_LIB_TYPE "NV_REPLAY_LIB_SHARED")
else()
	set(ReplayExecutorLibraryType "STATIC")
	set(NV_REPLAY_LIB_TYPE "NV_REPLAY_LIB_STATIC")
endif()

################################################################################
# Replay Executor (library)
################################################################################

add_library(ReplayExecutor ${ReplayExecutorLibraryType}
    Application.cpp
    CommonReplay.cpp
    D3D11Replay.cpp
    DXGIReplay.cpp
    DataScope.cpp
    Helpers.cpp
    ReadOnlyDatabase.cpp
    ReplayHelpers.cpp
    ThreadPool.cpp
    Threading.cpp
)

target_include_directories(ReplayExecutor PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    include)

# The platform include may have old/incompatible Vulkan headers, hence they need to be put
# after the local include
if(NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED")
    target_include_directories(ReplayExecutor
        PUBLIC
            ${NV_LINUX_EMBEDDED_INC_DIR}
    )
endif()

target_compile_definitions(ReplayExecutor
    PUBLIC
            NV_HAS_FUNCTION_OVERRIDES

    PRIVATE
        ${NV_REPLAY_LIB_TYPE}
        ReplayExecutor_EXPORTS)

if(NV_TARGET_PLATFORM STREQUAL "LINUX_DESKTOP")
    target_compile_options(ReplayExecutor PUBLIC
        -std=c++14
        -fvisibility=hidden
        -Os
        -g
        -O2
        -Wall
        -Werror=return-type)
elseif(NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED")
    target_compile_options(ReplayExecutor PUBLIC
        -std=c++14
        -fvisibility=hidden
        -Os
        -g
        -O2
        -fomit-frame-pointer
        -finline-functions
        -finline-limit=300
        -fgcse-after-reload
        -fno-strict-aliasing
        -Wall
        -Wcast-align
        -Wno-unused-variable
        -Werror=return-type
    )
endif()

option(NV_USE_MANAGED_WINSYS "Use replayer managed windowing system" OFF)
if(NV_USE_MANAGED_WINSYS OR NOT NV_BUILD_FOR_ORIGINAL_PLATFORM OR NOT NV_WINSYS STREQUAL NV_ORIGINAL_WINSYS)
    target_compile_definitions(ReplayExecutor PUBLIC NV_USE_MANAGED_WINSYS)
endif()

target_include_directories(ReplayExecutor PUBLIC
)

if(NV_USE_64BIT)
    target_link_libraries(ReplayExecutor
    PRIVATE
)
endif()

if(NV_USE_32BIT)
    target_link_libraries(ReplayExecutor
    PRIVATE
)
endif()

# Specify platform-specific linker flags
if(NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED")
    target_link_libraries(ReplayExecutor
        PUBLIC
            ${NV_LINUX_EMBEDDED_LINKER_FLAGS}
    )
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # -W3     - Warning level 3 (see https://docs.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level?view=vs-2019)
    # -MP     - Build with multiple processes to speed up the build
    # -Ob2    - Inline expansion level, allows compiler to expand any function not explicitly marked for no inlining
    # -wdXXXX - disable a specific Warning (see https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4800-through-c4999?view=vs-2019)
    # -bigobj - Increase number of sections in .obj file to a capacity of 4Gb, we have some very large files
    # -GS-    - Disable buffer security check, this is local .exe that is primarily built from generated code and requires full performance
    target_compile_options(ReplayExecutor PUBLIC -W3 -MP -Ob2 -wd4351 -wd4819 -bigobj -GS-)
    # -MDd - Defines _DEBUG, _MT, and _DLL for multithreaded debug builds, uses shared run-time library
    target_compile_options(ReplayExecutor PUBLIC $<$<CONFIG:DEBUG>:-MDd>)
    # -MD - Defines _MT and _DLL for multithreaded builds, uses shared run-time library
    # -Oi - Generate instrinsic functions to replace some function calls with instrinsic functions for better performance
    target_compile_options(ReplayExecutor PUBLIC $<$<CONFIG:RELEASE>:-Oi -MD>)
    # /OPT:NOICF - Disable COMDAT folding
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /OPT:NOICF")
    # 32 MB stack
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:33554432")
    # /Zc:__cplusplus - Enable the __cplusplus preprocessor macro
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()

# Set platform specific properties.
if(NV_USE_WIN32)

    # Windows application & Win32 windowing system
    target_sources(ReplayExecutor
        PRIVATE
            Win32Application.cpp
            WindowSystem_Win32.cpp)
    target_compile_definitions(ReplayExecutor
        PUBLIC
            _CRT_SECURE_NO_DEPRECATE
            NOMINMAX
            NV_USE_WIN32=1
            VK_USE_PLATFORM_WIN32_KHR
            UNICODE
        PRIVATE
            ReplayExecutor_EXPORTS)

endif()

if((NV_TARGET_PLATFORM STREQUAL "LINUX_DESKTOP") OR (NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED"))

    # Linux application
    target_sources(ReplayExecutor
        PRIVATE
            LinuxApplication.cpp)

    # XCB Windowing System
    if(NV_USE_XCB)
        target_sources(ReplayExecutor
            PRIVATE
                WindowSystem_Xcb.cpp)
        target_compile_definitions(ReplayExecutor
            PUBLIC
                NV_USE_XCB=1
                VK_USE_PLATFORM_XCB_KHR)
        target_link_libraries(ReplayExecutor
            PRIVATE
                dl
                xcb
                xcb-icccm
                pthread)
    endif()

    # X11 Windowing System
    if(NV_USE_X11)
        target_sources(ReplayExecutor
            PRIVATE
                WindowSystem_X11.cpp)
        target_compile_definitions(ReplayExecutor
            PUBLIC
                NV_USE_X11=1
                VK_USE_PLATFORM_XLIB_KHR)
        target_link_libraries(ReplayExecutor
            PRIVATE
                dl
                X11
                Xau
                pthread)
    endif()

    # D2D Windowing System
    if(NV_USE_D2D)
        target_sources(ReplayExecutor
            PRIVATE
                WindowSystem_D2d.cpp)
        target_compile_definitions(ReplayExecutor
            PUBLIC
                NV_USE_D2D=1
                VK_USE_PLATFORM_D2D_KHR
        )
        target_link_libraries(ReplayExecutor
            PRIVATE
                dl
                pthread)
    endif()

    # Wayland Windowing System
    if(NV_USE_WAYLAND)
        target_sources(ReplayExecutor
            PRIVATE
                WindowSystem_Wayland.cpp
        )
        target_compile_definitions(ReplayExecutor
            PUBLIC
                NV_USE_WAYLAND=1
                VK_USE_PLATFORM_WAYLAND_KHR
        )
        target_link_libraries(ReplayExecutor
            PRIVATE
                xkbcommon
                wayland-client
                wayland-egl
                pthread
                dl
        )
    endif()

    # EGL Device Windowing System
    if(NV_USE_EGL_DEVICE)
        target_sources(ReplayExecutor
            PRIVATE
                WindowSystem_Egldevice.cpp
        )
        target_compile_definitions(ReplayExecutor
            PUBLIC
                NV_USE_EGL_DEVICE=1
        )
        target_link_libraries(ReplayExecutor
            PRIVATE
                pthread
                dl
        )
    endif()

endif()

################################################################################
# Generated Replay (library)
################################################################################

add_library(GeneratedReplay ${ReplayExecutorLibraryType}
    Frame0Part00.cpp
    FrameReset00.cpp
    FrameSetup00.cpp
    PerfMarkersReset.cpp
    PerfMarkersSetup.cpp
    ReplayProcedures.cpp
    Resources00.cpp
    WinResourcesReset.cpp
    WinResourcesSetup.cpp
    function_overrides.cpp
)

target_include_directories(GeneratedReplay
    PRIVATE
        include)

target_link_libraries(GeneratedReplay
    PRIVATE
        ReplayExecutor
    d3d11.lib
    d3d9.lib
    dxgi.lib
)

target_compile_definitions(GeneratedReplay
    PUBLIC
        ${NV_REPLAY_LIB_TYPE})

if(NV_USE_WIN32)
    target_compile_definitions(GeneratedReplay
        PUBLIC
            _CRT_SECURE_NO_DEPRECATE
            NV_USE_WIN32=1
            VK_USE_PLATFORM_WIN32_KHR)
endif()

################################################################################
# Main (executable)
################################################################################

add_executable(Main
    Main.cpp
)

set_target_properties(Main PROPERTIES OUTPUT_NAME ${CPP_OUTPUT_NAME})
set_directory_properties(PROPERTY VS_STARTUP_PROJECT Main)

if(NV_TARGET_PLATFORM STREQUAL "WIN32")
    target_compile_definitions(Main
        PRIVATE
            NOMINMAX)
endif()

if((NV_TARGET_PLATFORM STREQUAL "LINUX_DESKTOP") OR (NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED"))
    target_link_libraries(Main
        PRIVATE
            pthread)
endif()

# Dynamic DLL dependency
add_dependencies(Main GeneratedReplay)

# Link libraries
target_link_libraries(Main
    PRIVATE
        ReplayExecutor)

# Static link the generate replay for the non-shared (e.g. static build)
if (NOT NV_SHARED_REPLAY_LIB)
    target_link_libraries(Main PRIVATE
        GeneratedReplay)
endif()

################################################################################
# Install
################################################################################

# Install targets
if(NOT NV_INSTALL_FOLDER)
    set(NV_INSTALL_FOLDER bin)
endif()
install(TARGETS Main RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${NV_INSTALL_FOLDER}/)

if(NV_SHARED_REPLAY_LIB)
    if(NV_TARGET_PLATFORM STREQUAL "WIN32")
        install(TARGETS GeneratedReplay RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${NV_INSTALL_FOLDER}/)
        install(TARGETS ReplayExecutor RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${NV_INSTALL_FOLDER}/)
    else()
        install(TARGETS GeneratedReplay LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${NV_INSTALL_FOLDER}/)
        install(TARGETS ReplayExecutor LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${NV_INSTALL_FOLDER}/)
    endif()
endif()

set(RESOURCE_FILES_OR_FOLDERS)

if(NV_USE_64BIT)
    list(APPEND RESOURCE_FILES_OR_FOLDERS
)
endif()

if(NV_USE_32BIT)
    list(APPEND RESOURCE_FILES_OR_FOLDERS
)
endif()

if((NV_TARGET_PLATFORM STREQUAL "LINUX_DESKTOP") OR (NV_TARGET_PLATFORM STREQUAL "LINUX_EMBEDDED"))
    install(PROGRAMS "Linux/run_replay.sh" DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${NV_INSTALL_FOLDER}/ RENAME "${CPP_OUTPUT_NAME}.sh")
endif()

if(RESOURCE_FILES_OR_FOLDERS)
    set(RESOURCES)
    foreach(FILE_OR_FOLDER ${RESOURCE_FILES_OR_FOLDERS})

        # The behavior of "IS_DIRECTORY" is well-defined only for full paths.
        get_filename_component(ABSOLUTE_FILE_OR_FOLDER "${FILE_OR_FOLDER}" ABSOLUTE)

        if(IS_DIRECTORY ${ABSOLUTE_FILE_OR_FOLDER})
            file(GLOB SUB_FILES ${ABSOLUTE_FILE_OR_FOLDER}/*.*)
            list(APPEND RESOURCES ${SUB_FILES})
        else()
            list(APPEND RESOURCES ${FILE_OR_FOLDER})
        endif()
    endforeach()
    install(FILES ${RESOURCES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/${NV_INSTALL_FOLDER}/)
endif()
