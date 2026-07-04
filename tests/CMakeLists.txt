add_executable(TestAllocate     allocator/test_allocate.cpp)
target_link_libraries(TestAllocate PRIVATE SecureAllocator)
add_test(NAME TestAllocate COMMAND TestAllocate)

add_executable(TestDeallocate   allocator/test_deallocate.cpp)
target_link_libraries(TestDeallocate PRIVATE SecureAllocator)
add_test(NAME TestDeallocate COMMAND TestDeallocate)

add_executable(TestMemzero      allocator/test_memzero.cpp)
target_link_libraries(TestMemzero PRIVATE SecureAllocator)
add_test(NAME TestMemzero COMMAND TestMemzero)

add_executable(TestRebind       allocator/test_rebind.cpp)
target_link_libraries(TestRebind PRIVATE SecureAllocator)
add_test(NAME TestRebind COMMAND TestRebind)

add_executable(TestVector       allocator/test_vector.cpp)
target_link_libraries(TestVector PRIVATE SecureAllocator)
add_test(NAME TestVector COMMAND TestVector)
