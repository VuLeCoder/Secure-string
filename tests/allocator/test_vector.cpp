#include <cassert>
#include <vector>
#include "./../../include/allocator/SecureAllocator.h"

int main()
{
    std::vector<int, SecureAllocator<int>> vec;

    for(int i=0; i<100; ++i)
        vec.push_back(i);

    assert(vec.size() == 100);

    for(int i=0; i<100; ++i)
        assert(vec[i] == i);

    return 0;
}