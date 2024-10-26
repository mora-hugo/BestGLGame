#pragma once

#include "Interface.h"

class IImGUIWindow : public Interface {
public:
    ~IImGUIWindow() override = default;
    virtual void ImGUIFrameBegin() = 0;
    virtual void ImGUIRender() = 0;

protected:
    virtual void InitializeIMGUI() = 0;
};