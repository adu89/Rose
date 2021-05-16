#pragma once

#ifdef ROSE_ENABLE_ASSERTS
    #define ROSE_ASSERT(x, ...) { if(!(x)) { ROSE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define ROSE_CORE_ASSERT(x, ...) { if(!(x)) { ROSE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define ROSE_ASSERT(x, ...)
    #define ROSE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (x << 1)

