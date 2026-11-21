DU AN CAY GIA PHA - CAC SOURCE CODE DA TICH HOP

Cac file chinh:
- main.cpp: menu tong va dieu phoi chuc nang.
- Tree.h, Tree.cpp: cau truc Person/FamilyTree va thuat toan cay.
- linkedList.h, linkedList.cpp: cac thao tac danh sach lien ket con va vo/chong.
- QuanLyThanhVien.h, QuanLyThanhVien.cpp: them/sua/xem/xoa va hien thi thanh vien.
- FamilyRelations.h, FamilyRelations.cpp: tra cuu cu to, cha/me, vo/chong, anh/chi/em, con cai.
- test_Tree.cpp: bo kiem thu rieng cho module Tree.

BIEN DICH CHUONG TRINH CHINH (PowerShell/MinGW):
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp Tree.cpp linkedList.cpp QuanLyThanhVien.cpp FamilyRelations.cpp -o main.exe
.\main.exe

KIEM THU MODULE TREE RIENG:
g++ -std=c++11 -Wall -Wextra -pedantic test_Tree.cpp Tree.cpp linkedList.cpp -o test_Tree.exe
.\test_Tree.exe

Luu y:
1. Chi bien dich mot main: khong dua test_Tree.cpp vao lenh build chuong trinh chinh.
2. Tree.h la noi duy nhat dinh nghia Person, ChildNode, SpouseNode va FamilyTree.
3. linkedList.h chi khai bao ham; linkedList.cpp chua phan cai dat.
4. Tra cuu quan he chon thanh vien theo ID de tranh nham nguoi khi trung ho ten.
5. Mo hinh hien tai chi luu mot con tro cha (Person::cha); danh sach vo/chong dang luu ten, chua phan biet ro cha va me.
