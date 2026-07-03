#include <vector>
#include <iostream>
#include "./../include/allocator/SecureAllocator.h"

int main() {
    std::vector<int, SecureAllocator<int>> v;

    v.push_back(1);
    v.push_back(2);

    std::cout << v[0];
}