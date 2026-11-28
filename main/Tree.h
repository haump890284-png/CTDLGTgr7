#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
using namespace std;

struct Person;

struct SpouseNode {          // node DSLK don ten vo/chong
    string ten;
    SpouseNode* next;
};

struct ChildNode {           // node DSLK don cac con cua 1 nguoi
    Person* p;               // tro toi node con trong cay
    ChildNode* next;
};

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

void    khoiTaoCay(FamilyTree& t);                       // O(1)
bool    laCayRong(const FamilyTree& t);                  // O(1)
Person* TaoNode(FamilyTree& t, const string& ten, const string& qh,
                int ns, int nm);                         // O(1)

void    ThemCon(Person* cha, Person* con);               // them cuoi DSLK con, O(k)
bool    themVaoCay(FamilyTree& t, Person* cha, Person* p); // gan node vao cay

Person* taoCuTo(FamilyTree& t, const string& ten, int ns, int nm);
Person* layCuTo(const FamilyTree& t);                    // O(1)
Person* timCuTo(Person* p);                              // di nguoc len goc, O(h)
bool    themCuToMoi(FamilyTree& t, Person* cuToMoi, const string& qhCuToCu);

Person* TimTheoId(Person* r, int id);                    // DFS NLR, O(n)
void    TimTheoTen(Person* r, const string& ten, vector<Person*>& kq); // O(n)
bool    soSanhTen(const string& a, const string& b);     // khong phan biet hoa/thuong, khoang trang thua

int  layDoi(const Person* p);                            // muc + 1 (cu to la doi 1), O(h)
int  chieuCao(const Person* r);                          // chieu cao cay con, O(n)
int  bacCuaNode(const Person* p);                        // so con, O(k)
int  demSoNode(const Person* r);                         // so nguoi, O(n)
int  demSoLa(const Person* r);                           // so nguoi chua co con, O(n)
void inTheoDoi(const FamilyTree& t);                     // duyet theo muc (BFS), O(n)

#endif
