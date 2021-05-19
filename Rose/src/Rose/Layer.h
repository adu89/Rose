#pragma once

#include <string>
#include "Events/Event.h"

namespace Rose
{
    class Layer
    {
    public:
        Layer(const std::string& debugName = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate() {};
        virtual void OnEvent(Event& event) {};

        inline const std::string& GetName() const { return debugName; }
    protected:
        std::string debugName;
    };
}