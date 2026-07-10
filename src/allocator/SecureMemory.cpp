#include "allocator/SecureMemory.h"

#include <cstddef>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

void secure::secure_memzero(void* ptr, std::size_t size) {
    #ifdef _WIN32
    SecureZeroMemory(ptr, size);
    #else
    explicit_bzero(ptr, size);
    #endif
}

bool secure::lock_memory(void *ptr, std::size_t size) {
    #ifdef _WIN32
    return VirtualLock(ptr, size) != FALSE;
    #else
    mlock(ptr, size);
    #endif
}

bool secure::unlock_memory(void *ptr, std::size_t size) {
    #ifdef _WIN32
    return VirtualUnlock(ptr, size) != FALSE;
    #else
    munlock(ptr, size);
    #endif
}

bool secure::secure_compare(const void *ptr1, const void *ptr2, std::size_t size) {
    const auto* a = static_cast<const unsigned char*>(ptr1);
    const auto* b = static_cast<const unsigned char*>(ptr2);
    
    unsigned char diff = 0;
    for(std::size_t i=0; i<size; ++i) {
        diff |= a[i] ^ b[i];
    }
    return diff == 0;
}