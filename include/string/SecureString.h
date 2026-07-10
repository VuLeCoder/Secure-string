#pragma once
#include <string>
#include "allocator/SecureAllocator.h"

class SecureString {
private:
    std::basic_string<char, std::char_traits<char>, SecureAllocator<char>> data_;

public:
    SecureString() noexcept;
    SecureString(const char*);

    SecureString(const SecureString&);
    SecureString(SecureString&&) noexcept;

    ~SecureString() noexcept;

    SecureString& operator=(const SecureString&);
    SecureString& operator=(SecureString&&) noexcept;

    char* data() noexcept;
    const char* data() const noexcept;

    const char* c_str() const noexcept;
    std::string_view view() const noexcept;

    size_t capacity() const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;

    char& operator[](size_t) noexcept;
    const char& operator[](size_t) const noexcept;

    void clear() noexcept;
    void resize(size_t);
    void assign(const char*, size_t);

    void append(std::string_view);
    void push_back(char);
    void pop_back() noexcept;

    bool operator==(const SecureString&) const noexcept;
    bool equals(const SecureString&) const noexcept;
    
    SecureString& operator+=(const SecureString&);
    SecureString& operator+=(const char*);
    SecureString& operator+=(std::string_view);

    bool operator!=(const SecureString&) const noexcept;

    bool find(const SecureString&) const;
};
