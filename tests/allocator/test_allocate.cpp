#include <cassert>
#include "./../../include/allocator/SecureAllocator.h"

int main() {
    SecureAllocator<int> allocator;

    int* p = allocator.allocate(5);

    assert(p != nullptr);

    allocator.deallocate(p, 5);

    return 0;
}