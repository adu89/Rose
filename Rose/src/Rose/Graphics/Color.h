#pragma once

#include "Rose/Log.h"

namespace Rose {
    class Color
    {
    public:
        Color(int r, int g, int b, float alpha = 1.0f)
            : r(r), g(g), b(b), alpha(alpha)
        {
            ROSE_CORE_ASSERT(alpha <= 1.0f || alpha >= 0.0f, "Invalid alpha value.");
        }

        ~Color() {}

        int GetR() const { return r; }
        int GetG() const { return g; }
        int GetB() const { return b; }
        int GetAlpha() const { return alpha; }
        void SetAlpha(float a) { alpha = a; }

    private:
        float r;
        float g;
        float b;
        float alpha;
    };
}