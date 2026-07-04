#include "./../../include/string/SecureString.h"
#include <vector>
#include <unordered_map>
#include <optional>

int main() {
    SecureString str = "123";
    SecureString str2 = str; str2 += "456";
    SecureString str3(str2); str3.pop_back();

    str.clear();
    str = "3456";
    str.append("123");
    str.resize(3);
    str = "123";

    std::vector<SecureString> v1;
    std::unordered_map<int, SecureString> m1;
    std::optional<SecureString> o1;
}