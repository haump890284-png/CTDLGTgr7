HUONG DAN CHAY DU AN CAY GIA PHA
================================

1. CAC FILE
-----------
main.cpp                 Menu va dieu phoi chuong trinh (TV1)
Tree.h                   Dinh nghia Person, ChildNode, SpouseNode, FamilyTree va prototype Tree
Tree.cpp                 Cai dat cac ham Tree (TV2)
linkedList.h             Chi khai bao cac ham Linked List
linkedList.cpp           Cai dat cac ham danh sach con va vo/chong (TV3)
QuanLyThanhVien.h        Prototype cac chuc nang quan ly thanh vien
QuanLyThanhVien.cpp      Cai dat them/sua/xem/xoa/hien thi thanh vien (TV4)
test_Tree.cpp            Bo kiem thu Tree rieng, co main() rieng

2. NGUYEN TAC TUONG THICH
-------------------------
- Tree.h la noi DUY NHAT dinh nghia Person, ChildNode, SpouseNode, FamilyTree.
- ChildNode dung Person* p; SpouseNode dung string ten.
- linkedList.h include Tree.h va chi chua prototype, khong dinh nghia struct.
- linkedList.cpp chua phan cai dat cac ham Linked List.
- Tree.cpp goi addChild/findChild tu Linked List khi them con.
- QuanLyThanhVien.cpp khong khai bao lai struct va khong co main() rieng.
- main.cpp la noi duy nhat co ham main() cua chuong trinh.

3. BIEN DICH CHUONG TRINH
-------------------------
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp Tree.cpp linkedList.cpp QuanLyThanhVien.cpp -o gia_pha

Chay tren Linux/macOS:
./gia_pha

Chay tren Windows:
gia_pha.exe

4. CHAY KIEM THU TREE RIENG
---------------------------
g++ -std=c++11 -Wall -Wextra -pedantic test_Tree.cpp Tree.cpp linkedList.cpp -o test_tree
./test_tree

Luu y: test_Tree.cpp co main() rieng, khong bien dich cung main.cpp.

5. MENU DA NOI
--------------
- Them thanh vien: dung module QuanLyThanhVien (TV4), bao gom kiem tra dau vao.
- Sua thanh vien: module TV4.
- Xoa thanh vien va nhanh con: module TV4, dung removeChild cua Linked List.
- Quan ly vo/chong: menu TV1 goi addSpouse/removeSpouse/renameSpouse cua TV3.
- Hien thi cay dang phan cap: module TV4.
- Xem thong tin chi tiet: module TV4.
- Tra cuu quan he (menu 10): van la cho trong vi chua co source module TV5 trong cac file duoc gui.

6. QUAN LY BO NHO
-----------------
- removeChild/clearChildren chi giai phong node lien ket ChildNode, KHONG xoa Person*.
- huyNode giai phong de quy cac Person con, node ChildNode va danh sach SpouseNode.
- Khi thoat chuong trinh, main.cpp goi giaiPhongCay(cay.root).
