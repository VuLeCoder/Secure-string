#include <type_traits>
#include "./../../include/allocator/SecureAllocator.h"

int main() {
    SecureAllocator<int> a;

    SecureAllocator<char> b(a);

    static_assert(
        std::is_constructible_v<
            SecureAllocator<char>,
            SecureAllocator<int>>);
    return 0;
}