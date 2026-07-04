#include "./../../include/allocator/SecureMemory.h"

#include <cstddef>
#include <cstring>
#include <memoryapi.h>
#include <minwindef.h>
#include <windows.h>

void secure::secure_memzero(void* ptr, std::size_t size) {
    SecureZeroMemory(ptr, size);
}

bool secure::lock_memory(void *ptr, std::size_t size) {
    return VirtualLock(ptr, size) != FALSE;
}

bool secure::unlock_memory(void *ptr, std::size_t size) {
    return VirtualUnlock(ptr, size) != FALSE;
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