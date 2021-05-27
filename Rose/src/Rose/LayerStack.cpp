#include "LayerStack.h"

namespace Rose
{
    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        for(Layer* layer : layers)
            delete layer;
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        layers.emplace(layers.begin() + layerInsertIndex, layer);
        layerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* layer)
    {
        layers.emplace_back(layer);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(layers.begin(), layers.end(), layer);
        if(it != layers.end())
        {
            layers.erase(it);
            layerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(layers.begin(), layers.end(), overlay);
        if(it != layers.end())
            layers.erase(it);
    }
}