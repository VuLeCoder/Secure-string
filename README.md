# SecureString

Thư viện C++ cung cấp lớp `SecureString` để quản lý chuỗi ký tự nhạy cảm (như mật khẩu, khóa bí mật, token) một cách an toàn. Thư viện sử dụng cơ chế khóa bộ nhớ trong RAM và tự động xóa sạch dữ liệu (zero out) khi đối tượng bị hủy hoặc thay đổi để tránh rò rỉ dữ liệu.

## Tính năng bảo mật
- **Ngăn chặn ghi đĩa (Paging)**: Sử dụng API `VirtualLock` của Windows để khóa trang bộ nhớ trong RAM vật lý.
- **Xóa sạch dữ liệu (Zeroing Memory)**: Sử dụng API `SecureZeroMemory` của Windows để xóa sạch toàn bộ vùng nhớ (`capacity`) khi chuỗi bị giải phóng, dọn dẹp, thay đổi kích thước, hoặc thu nhỏ chuỗi.
- **Bảo vệ SSO (Small String Optimization)**: Dọn dẹp cả vùng đệm Stack của String khi đối tượng bị hủy (tránh rò rỉ khi lưu chuỗi ngắn).
- **So sánh an toàn (Constant-time Comparison)**: Tránh các cuộc tấn công dựa trên thời gian (Timing attacks) khi so sánh chuỗi bằng hàm `secure_compare`.

---

## Môi trường hoạt động
- **Hệ điều hành**: Windows (Sử dụng Windows API: `<memoryapi.h>`, `<windows.h>`).
- **Chuẩn C++**: C++20 hoặc mới hơn.
- **Trình biên dịch**: MSVC, MinGW hoặc Clang trên Windows hỗ trợ C++20.
- **Build System**: CMake 3.10+.

---

## Hướng dẫn cài đặt & tích hợp (Installation & Integration)
### Tích hợp trực tiếp thông qua CMake (add_subdirectory)
Đây là cách đơn giản nhất khi phát triển dự án. Bạn có thể sao chép thư mục mã nguồn thư viện (hoặc thêm dưới dạng Git Submodule) vào thư mục con trong dự án của bạn (ví dụ: `third_party/secure-string`).

1. Thêm các dòng sau vào file `CMakeLists.txt` dự án của bạn:
   ```cmake
   # Thêm thư mục mã nguồn thư viện
   add_subdirectory(third_party/secure-string)

   # Tạo target dự án của bạn
   add_executable(my_project main.cpp)

   # Liên kết dự án của bạn với thư viện SecureString
   target_link_libraries(my_project PRIVATE SecureString)
   ```

2. Trong mã nguồn dự án của bạn, include file header và sử dụng:
   ```cpp
   #include <string/SecureString.h>
   ```

---

## Hướng dẫn Phát triển & Chạy Test

Nếu bạn muốn chỉnh sửa thư viện hoặc chạy thử các unit test tự động có sẵn:

### 1. Cấu hình CMake với Unit Test
Kích hoạt build kèm các file unit test:
```powershell
cmake -B build -DBUILD_TESTS=ON
```

### 2. Biên dịch (Build)
Biên dịch dự án dưới cấu hình `Debug` hoặc `Release`:
```powershell
cmake --build build --config Debug
```

### 3. Chạy các Unit Test
Di chuyển vào thư mục `build` và sử dụng `ctest` để chạy toàn bộ các bài test bao gồm kiểm tra tính đúng đắn và kiểm tra rò rỉ bộ nhớ (zero memory):
```powershell
cd build
ctest -C Debug --output-on-failure
```

---

## Cách sử dụng trong mã nguồn C++

Thư viện được thiết kế để sử dụng tương tự như `std::string` nhưng có các cơ chế an toàn đi kèm:

```cpp
#include "string/SecureString.h"
#include <iostream>

int main() {
    // 1. Khởi tạo chuỗi nhạy cảm
    SecureString secret_key = "my_super_secret_key_123";

    // 2. Sử dụng giống như std::string thông thường
    std::cout << "Kích thước chuỗi: " << secret_key.size() << "\n";
    std::cout << "Ký tự đầu tiên: " << secret_key[0] << "\n";

    // 3. Sử dụng Iterators để lặp
    for (char c : secret_key) {
        // Xử lý ký tự ...
    }

    // 4. So sánh an toàn thời gian thực (Constant-time Comparison) để chống timing attacks
    SecureString other_key = "my_super_secret_key_123";
    if (secret_key.equals(other_key)) {
        std::cout << "Hai khóa trùng khớp!\n";
    }

    // 5. Chủ động xóa sạch dữ liệu khỏi bộ nhớ RAM
    secret_key.clear(); // Toàn bộ buffer dung lượng (capacity) sẽ bị đưa về 0x00 ngay lập tức

    return 0; // Khi ra khỏi block, destructor chạy và tự động xóa sạch dữ liệu trên Stack (SSO)
}
```
