//---------------------------------------------------------------------------
// File: WindowSystem_D2d.cpp
//
// Distributed as part of NVIDIA Tegra Graphics Debugger serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------

#include "WindowSystem.h"

class DummyD2dSystem : public WindowSystem
{
public:

    virtual void CreateDisplay() override
    {
    }

    virtual void DestroyDisplay() override
    {
    }

    virtual void CreateNativeWindow(void* data, int width, int height) override
    {
    }

    virtual void DestroyAllWindows() override
    {
    }

    virtual void DestroyWindow(void* winAddr) override
    {
    }

    virtual void* GetDisplayAddr() override
    {
        return nullptr;
    }

    virtual void* GetWindowAddr() override
    {
        return nullptr;
    }

    DummyD2dSystem() = default;
};

WindowSystem& WindowSystemInstance()
{
    static DummyD2dSystem instance;
    return instance;
}
