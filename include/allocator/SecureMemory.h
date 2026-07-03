#pragma once

#include <cstddef>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#endif

inline void secure_memzero(void* ptr, std::size_t size) {

    #ifdef _WIN32
        SecureZeroMemory(ptr, size);

    #elif defined(__STDC_LIB_EXT1__)
        memset_s(ptr, size, 0, size);

    #else
        volatile unsigned char* p = static_cast<volatile unsigned char*>(ptr);
        while(size--) {
            *p++ = 0;
        }
    
    #endif
}
