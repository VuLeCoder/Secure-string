#pragma once

#include <new>
#include <limits>
#include <type_traits>
#include <stdexcept>

#include "SecureMemory.h"

template<typename T>
class SecureAllocator {
public:
    using value_type = T;
    using is_always_equal = std::true_type;
    
    SecureAllocator() = default;
    
    template<typename U>
    constexpr SecureAllocator(const SecureAllocator<U>&) noexcept {}
    
    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n) noexcept;
    
    template<typename U>
    friend bool operator==(const SecureAllocator&, const SecureAllocator<U>&) noexcept {
        return true;
    }
    
    template<typename U>
    friend bool operator!=(const SecureAllocator&, const SecureAllocator<U>&) noexcept {
        return false;
    }
};

template<typename T>
T* SecureAllocator<T>::allocate(std::size_t n)
{
    if(n <= 0) {
        return nullptr;
    }
    
	if(n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
        throw std::bad_alloc();
    }

    T* ptr = static_cast<T*>(::operator new(n * sizeof(T)));
    if (!secure::lock_memory(ptr, n * sizeof(T))) {
        ::operator delete(ptr);
        throw std::runtime_error("Failed to lock secure memory.");
    }
    return ptr;
}

template<typename T>
void SecureAllocator<T>::deallocate(T* p, std::size_t n) noexcept
{
    if(p) {
        secure::secure_memzero(p, n * sizeof(T));
        secure::unlock_memory(p, n * sizeof(T));
    }
    ::operator delete(p);
}
