# QUẢN LÝ CÂY GIA PHẢ (C++ – Tree & Linked List)

Đồ án học phần **Cấu trúc dữ liệu và Giải thuật** (Mã học phần: `124002`)  
**Trường:** Đại học Giao thông Vận tải TP. Hồ Chí Minh (UTH) – Ban Công nghệ số  
**Giảng viên hướng dẫn:** TS. Lê Văn Quốc Anh  
**Nhóm:** Chủ đề 7

## Thành viên nhóm
| STT | Họ và tên | Vai trò chính |
| :-: | :--- | :--- |
| 1 | Mai Phi Hậu | Phân tích, xây dựng menu chính (`main.cpp`) & tích hợp |
| 2 | Lâm Gia Huy | Cấu trúc cây tổng quát (`Tree.h/.cpp`) & unit test (`test_Tree.cpp`) |
| 3 | Lê Huy Chấn | Danh sách liên kết đơn con và vợ/chồng (`linkedList.h/.cpp`) |
| 4 | Trần Huy Hoàng | Quản lý thành viên, hiển thị cây & kiểm tra dữ liệu (`QuanLyThanhVien.h/.cpp`) |
| 5 | Võ Nhật Tường | Tra cứu quan hệ gia đình (`FamilyRelations.h/.cpp`) |
| 6 | Đỗ Khánh Duy | Dữ liệu mẫu, kiểm thử tích hợp (`IT01–IT10`), benchmark & demo |

## Cấu trúc thư mục
Toàn bộ mã nguồn và tệp kiểm thử nằm trong thư mục `main/`:
- `main.cpp`: Menu chính và điều phối các chức năng.
- `Tree.h`, `Tree.cpp`: Định nghĩa cấu trúc `Person`, `ChildNode`, `SpouseNode`, `FamilyTree` và các thuật toán cây (DFS, BFS, thống kê).
- `linkedList.h`, `linkedList.cpp`: Thao tác danh sách liên kết đơn cho danh sách con và vợ/chồng.
- `QuanLyThanhVien.h`, `QuanLyThanhVien.cpp`: Thêm, sửa, xem, xóa thành viên, hiển thị cây phân cấp và kiểm tra đầu vào.
- `FamilyRelations.h`, `FamilyRelations.cpp`: Tra cứu cụ tổ, cha/mẹ, vợ/chồng, anh/chị/em và con cái.
- `test_Tree.cpp`: Bộ kiểm thử độc lập cho module Tree (24/24 assertion PASS).
- `benchmark.cpp`: Chương trình đo hiệu năng tìm kiếm theo ID với 100, 500 và 1.000 thành viên.
- `test_input.txt` & `test_log.txt`: Kịch bản đầu vào và nhật ký kết quả chạy thực tế 10 test case tích hợp (`IT01–IT10`).

## Hướng dẫn biên dịch và chạy (PowerShell / MinGW)

Di chuyển vào thư mục chứa mã nguồn trước khi chạy lệnh:
```powershell
cd main
