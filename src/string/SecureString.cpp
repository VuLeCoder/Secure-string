#include "./../../include/string/SecureString.h"
#include <cstddef>
#include <utility>

SecureString::SecureString() : data_() {}
SecureString::SecureString(const char* data) : data_(data) {}
SecureString::SecureString(std::string_view data) : data_(data) {}

SecureString::SecureString(const SecureString& other) : data_(other.data_) {}
SecureString::SecureString(SecureString&& other) noexcept : data_(std::move(other.data_)) {}

SecureString::~SecureString() {
    secure::secure_memzero(data_.data(), data_.capacity());
};

SecureString& SecureString::operator=(const SecureString& other) {
    if(this != &other) {
        secure::secure_memzero(data_.data(), data_.capacity());
        data_ = other.data_;
    }
    return *this;
}

SecureString& SecureString::operator=(SecureString&& other) noexcept {
    if(this != &other) {
        secure::secure_memzero(data_.data(), data_.capacity());
        data_ = std::move(other.data_);
    }
    return *this;
}

char* SecureString::data() noexcept {
    return data_.data();
}

const char* SecureString::data() const noexcept {
    return data_.data();
}

const char* SecureString::c_str() const noexcept {
    return data_.c_str();
}

size_t SecureString::size() const noexcept {
    return data_.size();
}

bool SecureString::empty() const noexcept {
    return data_.empty();
}

char& SecureString::operator[](size_t i) {
    return data_[i];
}

const char& SecureString::operator[](size_t i) const {
    return data_[i];
}

void SecureString::clear() {
    secure::secure_memzero(data_.data(), data_.capacity());
    data_.clear();
}

void SecureString::resize(size_t n) {
    if(n < data_.size()) {
        secure::secure_memzero(data_.data() + n, data_.size() - n);
    }
    data_.resize(n);
}

void SecureString::append(std::string_view sv) {
    data_.append(sv);
}

void SecureString::push_back(char c) {
    data_.push_back(c);
}

void SecureString::pop_back() {
    size_t n = data_.size();
    secure::secure_memzero(data_.data() + n - 1, 1);
    data_.pop_back();
}

bool SecureString::operator==(const SecureString& other) const {
    return data_ == other.data_;
}

bool SecureString::equals(const SecureString& other) const {
    if(size() != other.size()) {
        return false;
    }

    return secure::secure_compare(data(), other.data(), size());
}

SecureString& SecureString::operator+=(SecureString& add) {
    data_ += add.data_;
    return *this;
}

SecureString& SecureString::operator+=(std::string_view s) {
    data_ += s;
    return *this;
}
