#include "./../../include/string/SecureString.h"
#include <cassert>
#include <iostream>
#include <string_view>
#include <new>

// Helper to check if memory is zeroed
bool is_zeroed(const char* ptr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (ptr[i] != 0) {
            return false;
        }
    }
    return true;
}

void test_constructors_and_assignments() {
    std::cout << "Running test_constructors_and_assignments...\n";

    // 1. Default constructor
    SecureString s1;
    assert(s1.empty());
    assert(s1.size() == 0);

    // 2. C-string constructor
    SecureString s2("hello");
    assert(s2.size() == 5);
    assert(std::string_view(s2.data(), s2.size()) == "hello");

    // 3. string_view constructor
    std::string_view sv = "world_with_null\0_chars";
    // We construct a string view that has explicit size and includes the null char
    std::string_view sv_with_null("world_with_null\0_chars", 22);
    SecureString s3(sv_with_null);
    assert(s3.size() == 22);
    assert(s3[15] == '\0');

    // 4. Copy constructor
    SecureString s4(s3);
    assert(s4 == s3);
    assert(s4.size() == s3.size());

    // 5. Move constructor
    SecureString s3_copy(s3);
    SecureString s5(std::move(s3_copy));
    assert(s5 == s3);
    assert(s3_copy.empty());

    // 6. Copy assignment
    SecureString s6;
    s6 = s2;
    assert(s6 == s2);
    assert(std::string_view(s6.data(), s6.size()) == "hello");

    // 7. Move assignment
    SecureString s7;
    SecureString s2_copy(s2);
    s7 = std::move(s2_copy);
    assert(s7 == s2);
    assert(s2_copy.empty());
}

void test_mutators_and_accessors() {
    std::cout << "Running test_mutators_and_accessors...\n";

    SecureString s("hello");
    assert(s[0] == 'h');
    s[0] = 'y';
    assert(s[0] == 'y');

    // Append
    s.append(" world");
    assert(std::string_view(s.data(), s.size()) == "yello world");

    // operator+= (SecureString)
    SecureString s_add("!");
    s += s_add;
    assert(std::string_view(s.data(), s.size()) == "yello world!");

    // operator+= (string_view)
    s += " :)";
    assert(std::string_view(s.data(), s.size()) == "yello world! :)");

    // push_back
    s.push_back('?');
    assert(s[s.size() - 1] == '?');

    // pop_back
    s.pop_back();
    assert(s[s.size() - 1] == ')');
}


void test_security_memory_zeroing() {
    std::cout << "Running test_security_memory_zeroing...\n";

    // 1. Test clear() zeroes the capacity
    {
        SecureString s("super_secret_password_long_enough_to_avoid_or_trigger_sso");
        const char* p = s.data();
        size_t cap = s.capacity();
        assert(cap > 0);
        
        // Before clear, verify data is there
        assert(!is_zeroed(p, s.size()));

        s.clear();
        assert(s.empty());
        // After clear, verify ALL capacity is zeroed out
        assert(is_zeroed(p, cap));
    }

    // 2. Test resize() shrinking zeroes the discarded memory
    {
        SecureString s("secret12345");
        const char* p = s.data();
        size_t orig_size = s.size();
        size_t cap = s.capacity();

        s.resize(6); // Shrink to "secret"
        assert(s.size() == 6);
        assert(std::string_view(s.data(), s.size()) == "secret");

        // The discarded bytes starting at index 6 all the way to capacity should be zeroed
        assert(is_zeroed(p + 6, cap - 6));
    }

    // 3. Test pop_back() zeroes the popped char
    {
        SecureString s("secret");
        const char* p = s.data();
        s.pop_back();
        assert(s.size() == 5);
        assert(p[5] == 0); // Popped char should be zeroed
    }

    // 4. Test assignment zeroes old memory
    {
        // Let's do a pure SSO case where reallocation is guaranteed not to happen:
        SecureString s_sso("secret");
        const char* p_sso = s_sso.data();
        size_t cap_sso = s_sso.capacity();

        s_sso = "a";
        assert(s_sso.size() == 1);
        // The remaining capacity starting at index 1 must be zeroed
        assert(is_zeroed(p_sso + 1, cap_sso - 1));
    }

    // 5. Test destructor zeroes SSO memory (using placement new)
    {
        alignas(SecureString) char buf[sizeof(SecureString)];
        
        // Construct string inside buf
        SecureString* s = new (buf) SecureString("short_secret");
        const char* p = s->data();
        size_t cap = s->capacity();
        
        // Verify if it is SSO (stored inside the object itself)
        bool is_sso = (p >= buf && p < buf + sizeof(SecureString));
        
        s->~SecureString(); // Call destructor manually

        if (is_sso) {
            // If it was SSO, we can safely check that the destructor zeroed the SSO buffer
            assert(is_zeroed(p, cap));
            std::cout << "SSO destructor zeroing verified successfully!\n";
        } else {
            std::cout << "String was not SSO (heap allocated), skipping SSO destructor zeroing check.\n";
        }
    }
}

int main() {
    test_constructors_and_assignments();
    test_mutators_and_accessors();
    test_security_memory_zeroing();

    std::cout << "All SecureString comprehensive tests passed successfully!\n";
    return 0;
}
