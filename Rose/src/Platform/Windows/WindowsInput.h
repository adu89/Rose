#pragma once

#include "Rose/Input.h"

namespace Rose 
{
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePosition() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}