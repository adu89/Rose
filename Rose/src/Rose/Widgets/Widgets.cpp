#include "Widgets.h"

#include "Rose/Graphics/Graphics.h"
#include "Rose/Graphics/Colors.h"

namespace Rose {
    bool Widgets::Button(int id, const Rectangle& rectangle, UIState& uiState) 
    {
        MousePosition mousePosition = uiState.MousePosition;
        Color color = Colors::Blue;

        if(rectangle.Contains(mousePosition.X, mousePosition.Y))
        {
            uiState.HotItem = id;

            if(uiState.ActiveItem == 0 && uiState.IsMouseDown)
                uiState.ActiveItem = id;
        }

        if(uiState.HotItem == id)
        {
            if(uiState.ActiveItem == id)
            {
                Graphics::DrawRectangle(rectangle, Colors::Green);
            }
            else 
            {
                Graphics::DrawRectangle(rectangle, Colors::Red);
            }
        } 
        else 
        {
            Graphics::DrawRectangle(rectangle, Colors::Blue);
        }

        if(uiState.HotItem == id && uiState.ActiveItem == id && !uiState.IsMouseDown)
        {
            Graphics::DrawRectangle(rectangle, Colors::Blue);
            return true;
        }

        return false;
    }
}