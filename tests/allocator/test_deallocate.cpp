#include <cassert>
#include "./../../include/allocator/SecureAllocator.h"

int main() {
    SecureAllocator<int> allocator;

    int* p = allocator.allocate(3);

    p[0] = 10;
    p[1] = 20;
    p[2] = 30;

    assert(p[0] == 10);
    assert(p[1] == 20);
    assert(p[2] == 30);

    allocator.deallocate(p, 3);
    return 0;
}