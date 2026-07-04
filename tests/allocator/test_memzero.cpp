#include <cassert>
#include <cstring>
#include "./../../include/allocator/SecureMemory.h"

int main()
{
    char buffer[32];

    std::memset(buffer, 0xAA, sizeof(buffer));

    secure::secure_memzero(buffer, sizeof(buffer));

    for(char c : buffer) {
        assert(c == 0);
    }
    return 0;
}