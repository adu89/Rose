#pragma once

#include "Rose/Geometry/Rectangle.h"
#include "Rose/Input.h"

namespace Rose {
    struct UIState 
    {
        UIState() 
            : MousePosition(0, 0), IsMouseDown(false), HotItem(0), ActiveItem(0) 
        {
        }

        MousePosition MousePosition;
        bool IsMouseDown;
        int HotItem;
        int ActiveItem;
    };

    class Widgets
    {
    public:
        static bool Button(int id, const Rectangle& rectangle, UIState& uiState);
    };
}