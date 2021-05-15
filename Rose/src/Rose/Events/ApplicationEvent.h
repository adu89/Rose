#pragma once

#include "Event.h"

#include <sstream>

namespace Rose
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : width(width), height(height)
        {
        }

        unsigned int GetWidth() { return width; }
        unsigned int GetHeight() { return height; }
    
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << width << ", " << height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        unsigned int width, height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent()
        {
        }
        
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppTickEvent : public Event
    {
    public:
        AppTickEvent()
        {
        }

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}