#pragma once

#include <utility>

namespace Rose 
{
    struct MousePosition
    {
        MousePosition(float x, float y) 
            : X(x), Y(y) 
        {
        }

        float X;
        float Y;
    };
    class Input 
    {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static MousePosition GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
        static std::pair<int, int> GetWindowSize();
    };  
}