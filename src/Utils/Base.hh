#pragma once

// Platform detection using predefined macros
#ifdef _WIN32
/* Windows x64/x86 */
#define DR_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
/* Some Apple device */
#define DR_PLATFORM_MACOS
#elif defined(__linux__)
#define DR_PLATFORM_LINUX
#else
/* Unknown compiler/platform */
#error "Unknown platform!"
#endif  // End of platform detection

#ifdef DR_DEBUG
#if defined(DR_PLATFORM_WINDOWS)
#define DR_DEBUGBREAK() __debugbreak()
#elif defined(DR_PLATFORM_LINUX)
#include <signal.h>
#define DR_DEBUGBREAK() raise(SIGTRAP)
#elif defined(DR_PLATFORM_MACOS)
#include <signal.h>
#define DR_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define DR_ENABLE_ASSERTS
#else
#define DR_DEBUGBREAK()
#endif

// TODO: Make this macro able to take in no arguments except condition
#ifdef DR_ENABLE_ASSERTS
#define DR_ASSERT(x, ...)                                   \
    {                                                       \
        if (!(x)) {                                         \
            DR_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            DR_DEBUGBREAK();                                \
        }                                                   \
    }
#define DR_CORE_ASSERT(x, ...)                                   \
    {                                                            \
        if (!(x)) {                                              \
            DR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            DR_DEBUGBREAK();                                     \
        }                                                        \
    }
#else
#define DR_ASSERT(x, ...)
#define DR_CORE_ASSERT(x, ...)
#endif