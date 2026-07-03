#pragma once

#include <cstddef>
#include <new>
#include <limits>

#include "./SecureMemory.h"

template<typename T>
class SecureAllocator {
public:
    using value_type = T;

    SecureAllocator() = default;

    template<typename U>
    SecureAllocator(const SecureAllocator<U>&) {}

    T* allocate(std::size_t n);

    void deallocate(T* p, std::size_t n);
};

template<typename T>
T* SecureAllocator<T>::allocate(std::size_t n)
{
	if(n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
        throw std::bad_alloc();
    }

    return static_cast<T*>(
        ::operator new(n * sizeof(T))
    );
}

template<typename T>
void SecureAllocator<T>::deallocate(T* p, std::size_t n)
{
    if(p) {
        secure_memzero(p, n * sizeof(T));
    }
    ::operator delete(p);
}

