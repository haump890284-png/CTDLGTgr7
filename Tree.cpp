// =====================================================================
// FILE   : Tree.cpp
// PHAN CUA: Lam Huy - Xay dung cau truc Tree (cai dat cac ham trong Tree.h)
// n = so nguoi trong cay, h = chieu cao cay, k = so con cua 1 nguoi
// =====================================================================
#include "Tree.h"
#include <iostream>
#include <queue>
#include <cctype>
using namespace std;

// =====================================================================
// 1. KHOI TAO CAY / TAO NODE
// =====================================================================

// Khoi tao cay rong (giong init cua LinkedList/BinaryTree trong bai giang)
void khoiTaoCay(FamilyTree& t) {
    t.root = nullptr;
    t.nextId = 1;
}

bool laCayRong(const FamilyTree& t) {
    return t.root == nullptr;
}

// Tao 1 node moi (tuong tu createNode o Chuong 4, 5).
// Node moi chua co cha, chua co vo/chong, chua co con.
Person* TaoNode(FamilyTree& t, const string& ten, const string& qh, int ns, int nm) {
    Person* node = new Person;
    node->id      = t.nextId++;    // cap ID tu tang -> khong bao gio trung
    node->hoTen   = ten;
    node->quanHe  = qh;
    node->namSinh = ns;
    node->namMat  = nm;
    node->cha = nullptr;
    node->vc  = nullptr;
    node->con = nullptr;
    return node;
}

// =====================================================================
// 2. THEM THANH VIEN
// =====================================================================

// Gan node 'con' lam con cua 'cha': them vao CUOI DSLK con de giu thu tu
// anh truoc - em sau. Dong thoi gan con tro nguoc con->cha.
// Do phuc tap: O(k) vi phai di toi cuoi DSLK con.
void ThemCon(Person* cha, Person* con) {
    if (cha == nullptr || con == nullptr) return;
    con->cha = cha;

    ChildNode* newNode = new ChildNode;
    newNode->p = con;
    newNode->next = nullptr;

    if (cha->con == nullptr) {             // chua co con nao -> la con dau
        cha->con = newNode;
        return;
    }
    ChildNode* last = cha->con;            // tim node cuoi
    while (last->next != nullptr)
        last = last->next;
    last->next = newNode;
}

// Ham tong quat de gan 1 node vao cay:
//   - cha == nullptr va cay rong  -> p tro thanh cu to
//   - cha == nullptr va cay da co cu to -> tu choi (dung themCuToMoi)
//   - nguoc lai -> p la con cua cha
// Tra ve true neu gan thanh cong.
bool themVaoCay(FamilyTree& t, Person* cha, Person* p) {
    if (p == nullptr) return false;
    if (cha == nullptr) {
        if (t.root != nullptr) return false;
        p->cha = nullptr;
        p->quanHe = "cu to";
        t.root = p;
        return true;
    }
    ThemCon(cha, p);
    return true;
}

// =====================================================================
// 3. QUAN LY NODE CU TO
// =====================================================================

// Tao cay: tao node cu to khi cay dang rong. Tra ve nullptr neu da co cu to.
Person* taoCuTo(FamilyTree& t, const string& ten, int ns, int nm) {
    if (t.root != nullptr) return nullptr;
    Person* p = TaoNode(t, ten, "cu to", ns, nm);
    t.root = p;
    return p;
}

Person* layCuTo(const FamilyTree& t) {
    return t.root;
}

// Tu 1 nguoi bat ky, di nguoc theo con tro cha cho toi goc. O(h)
Person* timCuTo(Person* p) {
    if (p == nullptr) return nullptr;
    while (p->cha != nullptr)
        p = p->cha;
    return p;
}

// Bo sung mot the he moi PHIA TREN cu to hien tai
// (vd: tim duoc thong tin ong co cua cu to cu).
//   cuToMoi : node vua tao bang TaoNode, chua gan vao cay
//   qhCuToCu: quan he cua cu to cu voi cu to moi ("con trai", "con gai"...)
// Tra ve false neu du lieu khong hop le.
bool themCuToMoi(FamilyTree& t, Person* cuToMoi, const string& qhCuToCu) {
    if (cuToMoi == nullptr) return false;
    if (cuToMoi->cha != nullptr || cuToMoi->con != nullptr) return false; // phai la node moi
    if (t.root == nullptr) {                       // cay rong -> lam cu to luon
        return themVaoCay(t, nullptr, cuToMoi);
    }
    if (cuToMoi->namSinh > t.root->namSinh) return false; // cha khong the sinh sau con

    Person* cuToCu = t.root;
    cuToCu->quanHe = qhCuToCu;
    cuToMoi->quanHe = "cu to";
    ThemCon(cuToMoi, cuToCu);                      // cu to cu thanh con cua cu to moi
    t.root = cuToMoi;
    return true;
}

// =====================================================================
// 4. TIM KIEM
// =====================================================================

// Tim theo ID: duyet theo chieu sau, thu tu truoc (NLR).
// Tham node hien tai truoc, sau do lan luot tung cay con.
// Tim thay thi dung ngay. Thoi gian O(n), bo nho de quy O(h).
Person* TimTheoId(Person* r, int id) {
    if (r == nullptr) return nullptr;
    if (r->id == id) return r;                                    // N
    for (ChildNode* c = r->con; c != nullptr; c = c->next) {     // cac cay con
        Person* kq = TimTheoId(c->p, id);
        if (kq != nullptr) return kq;
    }
    return nullptr;
}

// Chuan hoa ten: bo khoang trang dau/cuoi, gop nhieu khoang trang thanh 1,
// chuyen chu ASCII ve chu thuong. (Chu co dau UTF-8 duoc giu nguyen.)
static string chuanHoaTen(const string& s) {
    string kq;
    bool truocLaCach = true;
    for (char ch : s) {
        if (ch == ' ' || ch == '\t') {
            if (!truocLaCach) kq += ' ';
            truocLaCach = true;
        } else {
            kq += (char)tolower((unsigned char)ch);
            truocLaCach = false;
        }
    }
    if (!kq.empty() && kq.back() == ' ') kq.pop_back();
    return kq;
}

bool soSanhTen(const string& a, const string& b) {
    return chuanHoaTen(a) == chuanHoaTen(b);
}

// Tim theo ho ten: tim kiem tuyen tinh tren cay (duyet NLR) va gom TAT CA
// nguoi trung ten vao kq (vi ho ten co the trung). O(n).
void TimTheoTen(Person* r, const string& ten, vector<Person*>& kq) {
    if (r == nullptr) return;
    if (soSanhTen(r->hoTen, ten)) kq.push_back(r);
    for (ChildNode* c = r->con; c != nullptr; c = c->next)
        TimTheoTen(c->p, ten, kq);
}

// =====================================================================
// 5. CAC DAI LUONG CUA CAY (theo dinh nghia Chuong 5)
// =====================================================================

// Muc cua cu to = 0 -> doi thu (muc + 1). O(h)
int layDoi(const Person* p) {
    if (p == nullptr) return 0;
    int doi = 1;
    while (p->cha != nullptr) {
        p = p->cha;
        doi++;
    }
    return doi;
}

// Chieu cao = so canh tren duong di dai nhat tu node xuong 1 la.
// Cay chi co 1 node -> 0; cay rong -> -1. Duyet LRN: tinh cac con truoc.
int chieuCao(const Person* r) {
    if (r == nullptr) return -1;
    int maxCon = -1;
    for (ChildNode* c = r->con; c != nullptr; c = c->next) {
        int h = chieuCao(c->p);
        if (h > maxCon) maxCon = h;
    }
    return maxCon + 1;
}

// Bac cua node = so cay con = so con truc tiep
int bacCuaNode(const Person* p) {
    if (p == nullptr) return 0;
    int dem = 0;
    for (ChildNode* c = p->con; c != nullptr; c = c->next) dem++;
    return dem;
}

int demSoNode(const Person* r) {
    if (r == nullptr) return 0;
    int dem = 1;
    for (ChildNode* c = r->con; c != nullptr; c = c->next)
        dem += demSoNode(c->p);
    return dem;
}

// La = node khong co con (nguoi chua co con)
int demSoLa(const Person* r) {
    if (r == nullptr) return 0;
    if (r->con == nullptr) return 1;
    int dem = 0;
    for (ChildNode* c = r->con; c != nullptr; c = c->next)
        dem += demSoLa(c->p);
    return dem;
}

// In cay theo tung doi: duyet theo muc (level-order / BFS) dung hang doi.
// Moi vong while xu ly tron 1 muc (so phan tu hien co trong queue).
// Thoi gian O(n), bo nho O(so nguoi nhieu nhat o 1 doi).
void inTheoDoi(const FamilyTree& t) {
    if (t.root == nullptr) {
        cout << "  Cay gia pha dang rong.\n";
        return;
    }
    queue<Person*> q;
    q.push(t.root);
    int doi = 1;
    while (!q.empty()) {
        int soNguoi = (int)q.size();               // so nguoi cua doi hien tai
        cout << "  Doi " << doi << ": ";
        for (int i = 0; i < soNguoi; i++) {
            Person* cur = q.front(); q.pop();
            cout << cur->hoTen << " [ID " << cur->id << "]";
            if (i < soNguoi - 1) cout << ", ";
            for (ChildNode* c = cur->con; c != nullptr; c = c->next)
                q.push(c->p);                       // dua cac con vao cuoi hang doi
        }
        cout << "\n";
        doi++;
    }
}
