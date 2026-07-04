#include "./../../include/allocator/SecureMemory.h"

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
