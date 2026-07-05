#include "./../../include/string/SecureString.h"
#include <cstddef>
#include <utility>

SecureString::SecureString() noexcept : data_() {}
SecureString::SecureString(const char* data) : data_(data) {}

SecureString::SecureString(const SecureString& other) : data_(other.data_) {}
SecureString::SecureString(SecureString&& other) noexcept : data_(std::move(other.data_)) {}

SecureString::~SecureString() noexcept{
    secure::secure_memzero(data_.data(), data_.capacity());
}

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

std::string_view SecureString::view() const noexcept {
    return std::string_view(data_.data(), data_.size());
}

size_t SecureString::capacity() const noexcept {
    return data_.capacity();
}

size_t SecureString::size() const noexcept {
    return data_.size();
}

bool SecureString::empty() const noexcept {
    return data_.empty();
}

char& SecureString::operator[](size_t i) noexcept {
    return data_[i];
}

const char& SecureString::operator[](size_t i) const noexcept {
    return data_[i];
}

void SecureString::clear() noexcept {
    secure::secure_memzero(data_.data(), data_.capacity());
    data_.clear();
}

void SecureString::resize(size_t n) {
    if(n < data_.size()) {
        secure::secure_memzero(data_.data() + n, data_.size() - n);
    }
    data_.resize(n);
}

void SecureString::assign(const char* data, size_t size) {
    clear();
    data_.assign(data, size);
}

void SecureString::append(std::string_view sv) {
    data_.append(sv);
}

void SecureString::push_back(char c) {
    data_.push_back(c);
}

void SecureString::pop_back() noexcept {
    size_t n = data_.size();
    if(n > 0) {
        secure::secure_memzero(data_.data() + n - 1, 1);
        data_.pop_back();
    }
}

bool SecureString::operator==(const SecureString& other) const noexcept {
    return data_ == other.data_;
}

bool SecureString::equals(const SecureString& other) const noexcept {
    if(size() != other.size()) {
        return false;
    }

    return secure::secure_compare(data(), other.data(), size());
}

SecureString& SecureString::operator+=(const SecureString& add) {
    data_ += add.data_;
    return *this;
}

SecureString& SecureString::operator+=(const char* add) {
    data_ += add;
    return *this;
}

SecureString& SecureString::operator+=(std::string_view s) {
    data_ += s;
    return *this;
}

bool SecureString::find(const SecureString& other) const {
    return data_.find(other.data_) != std::string::npos;
}

bool SecureString::operator!=(const SecureString& other) const noexcept{
    return data_ != other.data_;
}
