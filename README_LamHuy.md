# Phần Lâm Huy – Xây dựng cấu trúc Tree (Cây gia phả)

## Các file
| File | Nội dung |
|---|---|
| `Tree.h` | Khai báo cấu trúc node `Person`, `FamilyTree` (và `SpouseNode`, `ChildNode` đã thống nhất với Chấn Huy) cùng các hàm |
| `Tree.cpp` | Cài đặt các hàm |
| `test_Tree.cpp` | Test riêng phần Tree (24 test case), **không** đưa vào chương trình chính |

Biên dịch test: `g++ -std=c++11 -Wall -o test_tree test_Tree.cpp Tree.cpp`

## Thiết kế cấu trúc dữ liệu
- **Cây tổng quát**: mỗi người có số con không cố định nên không dùng cây nhị phân.
  Trong Chương 5, cây K-phân lưu các con bằng `vector`; ở đây thay `vector` bằng **DSLK đơn** (Chương 4) đúng yêu cầu đề "Tree + Linked list".
- Node `Person`: `id`, `hoTen`, `quanHe`, `namSinh`, `namMat` (0 = còn sống), `cha` (con trỏ ngược), `vc` (đầu DSLK vợ/chồng), `con` (đầu DSLK con).
- **`id` tự tăng làm khóa** vì họ tên có thể trùng nhau.
- **Con trỏ `cha`** giúp đi ngược lên cha/mẹ và cụ tổ trong O(h) thay vì phải duyệt cả cây O(n). Phần này hỗ trợ Nhật Tường (tìm cha/mẹ, anh/chị/em).
- Con mới được **thêm vào cuối** DSLK con để giữ thứ tự anh trước, em sau.

## Các hàm và độ phức tạp  (n = số người, h = chiều cao, k = số con)
| Hàm | Chức năng | Độ phức tạp |
|---|---|---|
| `khoiTaoCay`, `laCayRong` | Khởi tạo / kiểm tra cây rỗng | O(1) |
| `TaoNode` | Tạo node mới (giống `createNode` trong bài giảng) | O(1) |
| `ThemCon` | Gắn con vào cuối DSLK con và gán `con->cha` | O(k) |
| `themVaoCay` | Gắn node vào cây: làm cụ tổ nếu cây rỗng, nếu không thì làm con | O(k) |
| `taoCuTo`, `layCuTo` | Tạo cây (node gốc) / lấy cụ tổ | O(1) |
| `timCuTo(p)` | Từ một người đi ngược lên gốc | O(h) |
| `themCuToMoi` | Thêm một thế hệ mới phía trên cụ tổ hiện tại | O(1) |
| `TimTheoId` | DFS thứ tự trước (NLR), tìm thấy thì dừng | O(n) |
| `TimTheoTen` | Duyệt NLR, gom **tất cả** người trùng tên, không phân biệt hoa/thường và khoảng trắng thừa | O(n) |
| `layDoi` | Đời thứ mấy = mức + 1 | O(h) |
| `chieuCao` | Chiều cao cây (duyệt LRN) | O(n) |
| `bacCuaNode`, `demSoNode`, `demSoLa` | Bậc, số nút, số lá (Chương 5) | O(k), O(n), O(n) |
| `inTheoDoi` | Duyệt theo mức (BFS, dùng `queue`), in từng đời | O(n) |

Tìm kiếm trên cây gia phả là **tìm kiếm tuyến tính** (Chương 2) vì cây không có thứ tự như BST nên không tìm nhị phân được.

## Ghép code (cho Hậu / Hoàng)
1. Xóa khu vực **[A]** trong file của Hoàng (dòng 26–85), thay bằng `#include "Tree.h"`.
2. Hàm `ThemVoChong` trong [A] là của **Chấn Huy**, lấy từ file của Chấn Huy.
3. Nếu file của Chấn Huy đã khai báo `SpouseNode` / `ChildNode` thì xóa 2 struct đó trong `Tree.h` và `#include` file của Chấn Huy.
4. Biên dịch: `g++ -std=c++11 -o gia_pha main.cpp Tree.cpp <cac file khac>.cpp`

Đã thử ghép với `QuanLyThanhVien_HuyHoang.cpp`: thêm, xem, xử lý trùng tên, xóa nhánh và hiển thị cây đều chạy đúng, không rò rỉ bộ nhớ.

## Câu hỏi vấn đáp có thể gặp
- *Vì sao không dùng cây nhị phân?* Một người có thể có 0..nhiều con, số con không giới hạn.
- *Vì sao DSLK mà không dùng mảng?* Số con thay đổi liên tục; DSLK chỉ cấp phát đúng số node cần, thêm/xóa không phải dời phần tử.
- *Vì sao cần `id`?* Hai người có thể trùng họ tên, `id` là khóa duy nhất để phân biệt.
- *Vì sao thêm con trỏ `cha`?* Để truy cha/mẹ, cụ tổ trong O(h) thay vì O(n).
- *Có thể tìm nhanh hơn O(n) không?* Có thể dùng thêm bảng băm (Chương 6) với khóa là `id` để tìm trung bình O(1). Nhưng khi đó mọi thao tác thêm/xóa đều phải cập nhật bảng băm, nên nhóm để đây là hướng cải tiến.
