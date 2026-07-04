#pragma once
#include <cstddef>

namespace secure { 
    void secure_memzero(void* ptr, std::size_t size);
    bool lock_memory(void* ptr, std::size_t size);
    bool unlock_memory(void* ptr, std::size_t size);

    bool secure_compare(const void* ptr1, const void* ptr2, std::size_t size);
};
