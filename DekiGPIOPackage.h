#pragma once

#ifdef _WIN32
    #ifdef DEKI_GPIO_EXPORTS
        #define DEKI_GPIO_API __declspec(dllexport)
    #else
        #define DEKI_GPIO_API __declspec(dllimport)
    #endif
#else
    #define DEKI_GPIO_API __attribute__((visibility("default")))
#endif
