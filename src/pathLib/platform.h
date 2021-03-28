#ifndef __PLATFORM_H__
#define __PLATFORM_H__

enum Platform{WINDOWS, ANDROID, LINUX, IOS, OSX};

#ifdef __cplusplus
    extern "C"{
#endif

const int get_platform();

#ifdef __cplusplus
    }
#endif

#endif