// =====================================================================
// FILE   : test_Tree.cpp  -  Lam Huy tu kiem tra phan Tree (khong nop vao main)
// Bien dich: g++ -std=c++11 -Wall -o test_tree test_Tree.cpp Tree.cpp
// =====================================================================
#include "Tree.h"
#include <iostream>
using namespace std;

int soLoi = 0;
void kiemTra(bool dk, const string& moTa) {
    cout << (dk ? "  [PASS] " : "  [FAIL] ") << moTa << "\n";
    if (!dk) soLoi++;
}

// Giai phong cay de test khong ro ri bo nho (duyet LRN: con truoc, cha sau).
// Trong chuong trinh that dung huyNode() cua Hoang.
void giaiPhong(Person* p) {
    if (p == nullptr) return;
    ChildNode* c = p->con;
    while (c != nullptr) {
        ChildNode* tiep = c->next;
        giaiPhong(c->p);
        delete c;
        c = tiep;
    }
    delete p;
}

int main() {
    FamilyTree t;
    khoiTaoCay(t);

    cout << "== TC1: Cay rong ==\n";
    kiemTra(laCayRong(t), "Cay moi khoi tao la cay rong");
    kiemTra(layCuTo(t) == nullptr, "Cay rong khong co cu to");
    kiemTra(TimTheoId(t.root, 1) == nullptr, "Tim tren cay rong tra ve nullptr");
    kiemTra(chieuCao(t.root) == -1, "Chieu cao cay rong = -1");

    cout << "== TC2: Tao cu to va them thanh vien ==\n";
    Person* a = taoCuTo(t, "Nguyen Van An", 1920, 1990);
    kiemTra(a != nullptr && t.root == a && a->id == 1, "Tao cu to thanh cong, ID = 1");
    kiemTra(taoCuTo(t, "Nguoi khac", 1900, 0) == nullptr, "Khong tao duoc cu to thu 2");

    Person* b = TaoNode(t, "Nguyen Van Binh", "con trai", 1945, 2010);
    Person* c = TaoNode(t, "Nguyen Thi Cuc",  "con gai",  1948, 0);
    Person* d = TaoNode(t, "Nguyen Van Dung", "con trai", 1952, 0);
    themVaoCay(t, a, b); themVaoCay(t, a, c); themVaoCay(t, a, d);
    Person* e = TaoNode(t, "Nguyen Van Em",   "con trai", 1970, 0);
    Person* f = TaoNode(t, "Nguyen Thi Phuong","con gai", 1973, 0);
    themVaoCay(t, b, e); themVaoCay(t, b, f);
    Person* g = TaoNode(t, "Nguyen Van An",   "con trai", 1995, 0);   // trung ten cu to
    ThemCon(e, g);

    kiemTra(a->con->p == b && a->con->next->p == c && a->con->next->next->p == d,
            "Thu tu con giu dung: Binh -> Cuc -> Dung");
    kiemTra(g->cha == e && e->cha == b && b->cha == a, "Con tro nguoc 'cha' dung");
    Person* x = TaoNode(t, "Nguoi thua", "con trai", 1990, 0);
    kiemTra(!themVaoCay(t, nullptr, x), "Khong gan duoc nguoi thu 2 lam cu to");
    delete x;

    cout << "== TC3: Tim kiem ==\n";
    kiemTra(TimTheoId(t.root, 5) == e, "Tim theo ID 5 ra Nguyen Van Em");
    kiemTra(TimTheoId(t.root, 999) == nullptr, "Tim ID khong ton tai -> nullptr");
    vector<Person*> kq;
    TimTheoTen(t.root, "Nguyen Van An", kq);
    kiemTra(kq.size() == 2, "Hai nguoi trung ho ten -> tim ra 2 ket qua");
    kq.clear();
    TimTheoTen(t.root, "  nguyen   thi CUC ", kq);
    kiemTra(kq.size() == 1 && kq[0] == c, "Tim khong phan biet hoa/thuong, khoang trang thua");
    kq.clear();
    TimTheoTen(t.root, "Tran Van Khong", kq);
    kiemTra(kq.empty(), "Tim nguoi khong ton tai -> rong");

    cout << "== TC4: Cu to va cac dai luong cua cay ==\n";
    kiemTra(timCuTo(g) == a, "Tu chau Nguyen Van An (1995) truy nguoc ra cu to");
    kiemTra(layDoi(a) == 1 && layDoi(b) == 2 && layDoi(g) == 4, "Doi: cu to 1, con 2, chat 4");
    kiemTra(chieuCao(t.root) == 3, "Chieu cao cay = 3");
    kiemTra(bacCuaNode(a) == 3 && bacCuaNode(d) == 0, "Bac: cu to 3 con, Dung 0 con");
    kiemTra(demSoNode(t.root) == 7, "Tong so nguoi = 7");
    kiemTra(demSoLa(t.root) == 4, "So la (chua co con) = 4: Cuc, Dung, Phuong, An(1995)");

    cout << "== TC5: Them the he moi phia tren cu to ==\n";
    Person* sai = TaoNode(t, "Sinh sau", "", 1930, 0);
    kiemTra(!themCuToMoi(t, sai, "con trai"), "Cu to moi sinh sau cu to cu -> tu choi");
    delete sai;
    Person* z = TaoNode(t, "Nguyen Van To", "", 1890, 1960);
    kiemTra(themCuToMoi(t, z, "con trai"), "Them cu to moi thanh cong");
    kiemTra(t.root == z && a->cha == z && a->quanHe == "con trai" && z->quanHe == "cu to",
            "Goc doi sang cu to moi, cu to cu thanh con");
    kiemTra(layDoi(g) == 5 && chieuCao(t.root) == 4, "Doi va chieu cao cap nhat dung");

    cout << "== In theo doi (BFS) ==\n";
    inTheoDoi(t);

    giaiPhong(t.root);
    khoiTaoCay(t);
    cout << "\nKet qua: " << (soLoi == 0 ? "TAT CA DEU PASS" : to_string(soLoi) + " LOI") << "\n";
    return soLoi;
}
