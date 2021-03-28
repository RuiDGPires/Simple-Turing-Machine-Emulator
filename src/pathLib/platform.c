#include "platform.h"

#if defined(_WIN32)
    #define PLATFORM_I WINDOWS // Windows
#elif defined(_WIN64)
    #define PLATFORM_I WINDOWS// Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_I WINDOWS // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__ANDROID__)
    #define PLATFORM_I ANDROID // Android (implies Linux, so it must come first)
#elif defined(__linux__)
    #define PLATFORM_I LINUX // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_I IOS // Apple iOS
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_I IOS // Apple iOS
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_I OSX // Apple OSX
    #endif
#else
    #define PLATFORM_I -1
#endif

// Return a name of platform, if determined, otherwise - an empty string
const int get_platform() {
    return (PLATFORM_I == -1) ? -1 : PLATFORM_I;
}