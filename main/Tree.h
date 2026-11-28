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
//   - Moi node Person giu con tro 'con' tro toi DSLK don cac con.
//   - Moi node Person co DSLK 'vc' luu cac con tro Person* cua vo/chong.
//   - Them con tro nguoc 'cha' de truy nguoc len cha/me, cu to O(h).
//   - Khoa duy nhat la 'id' vi ho ten co the trung nhau.
// =====================================================================
#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
using namespace std;

// Kieu du lieu gioi tinh cua thanh vien.
enum class GioiTinh {
    ChuaXacDinh,
    Nam,
    Nu
};

// Khai bao truoc Person de cac node lien ket co the luu Person*.
struct Person;

// Node danh sach lien ket vo/chong, luu dia chi Person de xac dinh chinh xac.
struct SpouseNode {
    Person* p;
    SpouseNode* next;
};

// Node danh sach lien ket cac con, tro den node con trong cay duyet.
struct ChildNode {
    Person* p;
    ChildNode* next;
};

// Cau truc luu thong tin mot thanh vien trong cay gia pha.
struct Person {
    int id;                    // Khoa duy nhat, tu tang.
    string hoTen;              // Ho ten thanh vien.
    string quanHe;             // Quan he hien thi voi the he phia tren.
    GioiTinh gioiTinh;         // Gioi tinh de phan biet cha ruot va me ruot.
    int namSinh;
    int namMat;                // 0 = con song.
    Person* chaRuot;            // Lien ket huyet thong den cha ruot.
    Person* meRuot;             // Lien ket huyet thong den me ruot.
    Person* cha;                // Nut cha duyet duy nhat, chi dung cho cau truc cay.
    SpouseNode* vc;             // Danh sach lien ket den Person* vo/chong.
    ChildNode* con;             // Danh sach cac node con trong cay duyet.
};

// Quan ly cay gia pha va ID tiep theo can cap.
struct FamilyTree {
    Person* root = nullptr;  // node cu to (goc cua cay)
    int nextId = 1;          // ID se cap cho nguoi tiep theo
};

// Cac ham khoi tao va kiem tra trang thai cay.
void    khoiTaoCay(FamilyTree& t);                       // O(1)
bool    laCayRong(const FamilyTree& t);                  // O(1)
Person* TaoNode(FamilyTree& t, const string& ten, const string& qh,
                int ns, int nm, GioiTinh gioiTinh);       // O(1)

// Cac ham them thanh vien vao cay.
void    ThemCon(Person* cha, Person* con);               // them vao danh sach con duyet va cap nhat cha/me theo gioi tinh.
bool    GanChaMe(Person* con, Person* chaRuot, Person* meRuot, Person* nutChaDuyet);
bool    ThemVoChong(Person* a, Person* b);                // lien ket vo/chong hai chieu.
bool    themVaoCay(FamilyTree& t, Person* cha, Person* p); // gan node vao cay duyet.

// Cac ham quan ly cu to cua cay gia pha.
Person* taoCuTo(FamilyTree& t, const string& ten, int ns, int nm, GioiTinh gioiTinh);
Person* layCuTo(const FamilyTree& t);                    // O(1)
Person* timCuTo(Person* p);                              // di nguoc len goc, O(h)
bool    themCuToMoi(FamilyTree& t, Person* cuToMoi, const string& qhCuToCu);

// Cac ham tim kiem thanh vien trong cay.
Person* TimTheoId(Person* r, int id);                    // DFS NLR, O(n)
void    TimTheoTen(Person* r, const string& ten, vector<Person*>& kq); // O(n)
bool    soSanhTen(const string& a, const string& b);     // khong phan biet hoa/thuong, khoang trang thua

// Cac ham tinh dai luong cua cay gia pha.
int  layDoi(const Person* p);                            // muc + 1 (cu to la doi 1), O(h)
int  chieuCao(const Person* r);                          // chieu cao cay con, O(n)
int  bacCuaNode(const Person* p);                        // so con, O(k)
int  demSoNode(const Person* r);                         // so nguoi, O(n)
int  demSoLa(const Person* r);                           // so nguoi chua co con, O(n)
void inTheoDoi(const FamilyTree& t);                     // duyet theo muc (BFS), O(n)

#endif
