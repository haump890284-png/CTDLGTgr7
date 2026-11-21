// =====================================================================
// DE TAI : CAY GIA PHA (Tree + Linked list)
// FILE   : Tree.h
// PHAN CUA: Lam Huy - Xay dung cau truc Tree
//   1. Thiet ke cau truc node luu thong tin mot nguoi
//   2. Xay dung cay gia pha (khoi tao cay)
//   3. Tao cay va them thanh vien moi (gan node vao cay)
//   4. Tim kiem mot nguoi trong cay (theo ID, theo ho ten)
//   5. Quan ly node cu to (tao, lay, them the he moi phia tren cu to)
//
// MO HINH: cay tong quat (moi nguoi co so con khong co dinh).
//   - Moi node Person giu con tro 'con' tro toi DSLK don cac con
//     (cach bieu dien "danh sach con" - Chuong 5, cay K-phan, nhung
//     dung DSLK don cua Chuong 4 thay vi vector).
//   - Them con tro nguoc 'cha' de truy nguoc len cha/me, cu to O(h).
//   - Khoa duy nhat la 'id' vi ho ten co the trung nhau.
//
// GHEP CODE:
//   - Ten struct / ten truong / ten ham giong het khu vuc [A] trong file
//     cua Tran Huy Hoang -> chi can xoa [A] va #include "Tree.h".
//   - SpouseNode va ChildNode la cau truc DSLK da thong nhat voi Chan Huy.
//     Neu file cua Chan Huy da khai bao 2 struct nay thi xoa phan
//     "CAU TRUC DSLK" ben duoi va #include file cua Chan Huy vao day.
// =====================================================================
#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
using namespace std;

// ---------------------- CAU TRUC DSLK (thong nhat voi Chan Huy) -------
struct Person;

struct SpouseNode {          // node DSLK don ten vo/chong
    string ten;
    SpouseNode* next;
};

struct ChildNode {           // node DSLK don cac con cua 1 nguoi
    Person* p;               // tro toi node con trong cay
    ChildNode* next;
};

// ---------------------- CAU TRUC NODE CAY (Lam Huy) -------------------
struct Person {
    int id;                  // khoa duy nhat, tu tang
    string hoTen;            // ho ten
    string quanHe;           // quan he voi cha/me: "con trai", "con gai"...; cu to = "cu to"
    int namSinh;
    int namMat;              // 0 = con song
    Person* cha;             // con tro nguoc len cha/me (nullptr neu la cu to)
    SpouseNode* vc;          // dau DSLK vo/chong
    ChildNode* con;          // dau DSLK con (con dau tien)
};

struct FamilyTree {
    Person* root = nullptr;  // node cu to (goc cua cay)
    int nextId = 1;          // ID se cap cho nguoi tiep theo
};

// ---------------------- 1. Khoi tao / tao node ------------------------
void    khoiTaoCay(FamilyTree& t);                       // O(1)
bool    laCayRong(const FamilyTree& t);                  // O(1)
Person* TaoNode(FamilyTree& t, const string& ten, const string& qh,
                int ns, int nm);                         // O(1)

// ---------------------- 2. Them thanh vien ----------------------------
void    ThemCon(Person* cha, Person* con);               // them cuoi DSLK con, O(k)
bool    themVaoCay(FamilyTree& t, Person* cha, Person* p); // gan node vao cay

// ---------------------- 3. Quan ly cu to ------------------------------
Person* taoCuTo(FamilyTree& t, const string& ten, int ns, int nm);
Person* layCuTo(const FamilyTree& t);                    // O(1)
Person* timCuTo(Person* p);                              // di nguoc len goc, O(h)
bool    themCuToMoi(FamilyTree& t, Person* cuToMoi, const string& qhCuToCu);

// ---------------------- 4. Tim kiem -----------------------------------
Person* TimTheoId(Person* r, int id);                    // DFS NLR, O(n)
void    TimTheoTen(Person* r, const string& ten, vector<Person*>& kq); // O(n)
bool    soSanhTen(const string& a, const string& b);     // khong phan biet hoa/thuong, khoang trang thua

// ---------------------- 5. Cac dai luong cua cay (Chuong 5) -----------
int  layDoi(const Person* p);                            // muc + 1 (cu to la doi 1), O(h)
int  chieuCao(const Person* r);                          // chieu cao cay con, O(n)
int  bacCuaNode(const Person* p);                        // so con, O(k)
int  demSoNode(const Person* r);                         // so nguoi, O(n)
int  demSoLa(const Person* r);                           // so nguoi chua co con, O(n)
void inTheoDoi(const FamilyTree& t);                     // duyet theo muc (BFS), O(n)

#endif
