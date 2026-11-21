// =====================================================================
// DE TAI: CAY GIA PHA (Tree + Linked list)
// PHAN CUA: Tran Huy Hoang - Quan ly thong tin thanh vien
//   1. Them / sua thong tin thanh vien (phoi hop Lam Huy)
//   2. Xem thong tin mot nguoi
//   3. Xoa thanh vien
//   4. Hien thi toan bo cay gia pha
//   5. Xu ly nhap sai / thieu thong tin
//
// LUU Y GHEP CODE:
//  - Khu vuc [A] (Person, FamilyTree, TimTheoId, ThemCon...) la BAN TAM
//    cua phan Lam Huy (Tree) va Chan Huy (Linked list) de file nay chay
//    doc lap. Khi ghep, thay [A] bang code that cua ban do, giu nguyen
//    TEN TRUONG; chi can sua lai lenh goi ham neu ten ham khac.
//  - Khu vuc [B] la phan CHINH cua Hoang.
//  - main() chi de Hoang test rieng; menu that do Hau xay dung.
// Bien dich: g++ -std=c++11 -o gia_pha QuanLyThanhVien_HuyHoang.cpp
// =====================================================================
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ctime>
using namespace std;

// ====================== [A] BAN TAM CUA NHOM ==========================
// --- Chan Huy: danh sach lien ket don ---
struct SpouseNode {              // DSLK don ten vo/chong
    string ten;
    SpouseNode* next;
};
struct Person;
struct ChildNode {               // DSLK don cac con cua 1 nguoi
    Person* p;
    ChildNode* next;
};

// --- Lam Huy: node cay ---
struct Person {
    int id;                      // khoa duy nhat (vi ho ten co the trung)
    string hoTen;
    string quanHe;               // quan he voi cha/me: "con trai", "con gai"...
    int namSinh;
    int namMat;                  // 0 = con song
    Person* cha;                 // con tro nguoc len cha/me (null neu la cu to)
    SpouseNode* vc;              // dau DSLK vo/chong
    ChildNode* con;              // dau DSLK con
};
struct FamilyTree {
    Person* root = nullptr;      // cu to
    int nextId = 1;
};

Person* TaoNode(FamilyTree& t, const string& ten, const string& qh, int ns, int nm) {
    Person* p = new Person{t.nextId++, ten, qh, ns, nm, nullptr, nullptr, nullptr};
    return p;
}
void ThemVoChong(Person* p, const string& ten) {          // them cuoi DSLK
    SpouseNode* n = new SpouseNode{ten, nullptr};
    if (!p->vc) { p->vc = n; return; }
    SpouseNode* c = p->vc;
    while (c->next) c = c->next;
    c->next = n;
}
void ThemCon(Person* cha, Person* con) {                  // them cuoi DSLK con
    con->cha = cha;
    ChildNode* n = new ChildNode{con, nullptr};
    if (!cha->con) { cha->con = n; return; }
    ChildNode* c = cha->con;
    while (c->next) c = c->next;
    c->next = n;
}
Person* TimTheoId(Person* r, int id) {                    // DFS tien tu, O(n)
    if (!r) return nullptr;
    if (r->id == id) return r;
    for (ChildNode* c = r->con; c; c = c->next)
        if (Person* kq = TimTheoId(c->p, id)) return kq;
    return nullptr;
}
void TimTheoTen(Person* r, const string& ten, vector<Person*>& kq) {
    if (!r) return;
    if (r->hoTen == ten) kq.push_back(r);
    for (ChildNode* c = r->con; c; c = c->next) TimTheoTen(c->p, ten, kq);
}
// ====================== het [A] =======================================


// ====================== [B] PHAN CUA HOANG ============================

// ---------- B1. Nhap lieu & kiem tra hop le ----------
const int NAM_MIN = 1000;
int namHienTai() {
    time_t t = time(nullptr);
    return localtime(&t)->tm_year + 1900;
}
string catKhoangTrang(const string& s) {
    size_t a = s.find_first_not_of(" \t");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}
// Doc 1 dong; tra false neu het du lieu (EOF)
bool docDong(string& s) { return (bool)getline(cin, s); }

// Doc ho ten khong rong. allowEmpty=true: bo trong = giu gia tri cu (dung khi sua)
bool nhapHoTen(const string& nhan, string& out, bool allowEmpty = false) {
    string s;
    while (true) {
        cout << nhan;
        if (!docDong(s)) return false;
        s = catKhoangTrang(s);
        if (s.empty() && allowEmpty) return true;       // giu nguyen
        if (s.empty()) { cout << "  [!] Ho ten khong duoc de trong.\n"; continue; }
        bool coChuSo = false;
        for (char c : s) if (isdigit((unsigned char)c)) coChuSo = true;
        if (coChuSo) { cout << "  [!] Ho ten khong duoc chua chu so.\n"; continue; }
        out = s; return true;
    }
}
// Doc so nguyen an toan (khong bi treo khi nhap chu)
bool nhapSo(const string& nhan, int& out, bool allowEmpty, bool& boTrong) {
    string s; boTrong = false;
    while (true) {
        cout << nhan;
        if (!docDong(s)) return false;
        s = catKhoangTrang(s);
        if (s.empty() && allowEmpty) { boTrong = true; return true; }
        if (s.empty()) { cout << "  [!] Khong duoc de trong.\n"; continue; }
        bool ok = s.size() <= 9;
        for (char c : s) if (!isdigit((unsigned char)c)) ok = false;
        if (!ok) { cout << "  [!] Vui long nhap so nguyen khong am.\n"; continue; }
        out = stoi(s); return true;
    }
}
// Kiem tra rang buoc nghiep vu, tra ve "" neu hop le, nguoc lai la thong bao loi
string kiemTraNam(int ns, int nm, const Person* cha) {
    int nay = namHienTai();
    if (ns < NAM_MIN || ns > nay) return "Nam sinh phai trong khoang " + to_string(NAM_MIN) + " - " + to_string(nay) + ".";
    if (nm != 0) {
        if (nm < ns)  return "Nam mat (" + to_string(nm) + ") nho hon nam sinh (" + to_string(ns) + ").";
        if (nm > nay) return "Nam mat khong duoc lon hon nam hien tai.";
    }
    if (cha && ns < cha->namSinh) return "Con (" + to_string(ns) + ") khong the sinh truoc cha/me (" + to_string(cha->namSinh) + ").";
    if (cha && cha->namMat != 0 && ns > cha->namMat + 1) // me/cha mat qua 1 nam thi bat thuong
        return "Con sinh sau khi cha/me mat tren 1 nam (" + to_string(cha->namMat) + ").";
    return "";
}
// Nhap nam sinh + nam mat, lap lai cho den khi hop le
bool nhapNamHopLe(int& ns, int& nm, const Person* cha, const Person* cu = nullptr) {
    bool bt;
    while (true) {
        string nhanS = cu ? "Nam sinh [" + to_string(cu->namSinh) + "] (Enter = giu): " : "Nam sinh: ";
        string nhanM = cu ? "Nam mat [" + (cu->namMat ? to_string(cu->namMat) : string("con song")) + "] (Enter = giu, 0 = con song): "
                          : "Nam mat (0 = con song): ";
        int s2 = cu ? cu->namSinh : 0, m2 = cu ? cu->namMat : 0;
        if (!nhapSo(nhanS, s2, cu != nullptr, bt)) return false;
        if (bt) s2 = cu->namSinh;
        if (!nhapSo(nhanM, m2, cu != nullptr, bt)) return false;
        if (bt) m2 = cu->namMat;
        string loi = kiemTraNam(s2, m2, cha);
        if (loi.empty()) { ns = s2; nm = m2; return true; }
        cout << "  [!] " << loi << " Moi nhap lai.\n";
    }
}

// ---------- B2. Chon nguoi (xu ly trung ho ten) ----------
// Tra ve Person* hoac nullptr neu khong tim thay / huy
Person* chonNguoi(FamilyTree& t, const string& tieuDe) {
    if (!t.root) { cout << "  [!] Cay gia pha dang rong.\n"; return nullptr; }
    string ten;
    cout << tieuDe << "\n";
    if (!nhapHoTen("  Nhap ho ten can tim: ", ten)) return nullptr;
    vector<Person*> ds;
    TimTheoTen(t.root, ten, ds);
    if (ds.empty()) { cout << "  [!] Khong tim thay \"" << ten << "\".\n"; return nullptr; }
    if (ds.size() == 1) return ds[0];
    cout << "  Co " << ds.size() << " nguoi trung ten, hay chon theo ID:\n";
    for (Person* p : ds)
        cout << "   ID " << p->id << " | sinh " << p->namSinh
             << " | cha/me: " << (p->cha ? p->cha->hoTen : "(cu to)") << "\n";
    bool bt; int id;
    if (!nhapSo("  Nhap ID: ", id, false, bt)) return nullptr;
    for (Person* p : ds) if (p->id == id) return p;
    cout << "  [!] ID khong nam trong danh sach tren.\n";
    return nullptr;
}

// ---------- B3. Them thanh vien ----------
// Hoang lo: nhap lieu + kiem tra. Lam Huy lo: gan node vao cay (ThemCon / gan root).
void themThanhVien(FamilyTree& t) {
    Person* cha = nullptr;
    if (t.root) {
        cha = chonNguoi(t, "[THEM] Chon CHA/ME cua nguoi moi:");
        if (!cha) return;
    } else {
        cout << "[THEM] Cay dang rong -> nguoi dau tien se la CU TO.\n";
    }
    string ten, qh = "cu to";
    int ns, nm;
    if (!nhapHoTen("Ho ten: ", ten)) return;
    if (cha) {
        // cung cha, trung ho ten + nam sinh => nghi trung lap
        for (ChildNode* c = cha->con; c; c = c->next)
            if (c->p->hoTen == ten) {
                cout << "  [?] " << cha->hoTen << " da co con ten \"" << ten
                     << "\" (sinh " << c->p->namSinh << "). Van them? (c/k): ";
                string r; if (!docDong(r)) return;
                if (r != "c" && r != "C") { cout << "  Da huy.\n"; return; }
                break;
            }
        if (!nhapHoTen("Quan he voi cha/me (vd: con trai, con gai): ", qh)) return;
    }
    if (!nhapNamHopLe(ns, nm, cha)) return;

    Person* p = TaoNode(t, ten, qh, ns, nm);
    if (cha) ThemCon(cha, p); else t.root = p;      // <-- goi ham cua Lam Huy
    cout << "  Da them \"" << ten << "\" (ID " << p->id << ").\n";

    string r;                                         // vo/chong (Chan Huy)
    while (true) {
        cout << "Them ten vo/chong? (Enter = bo qua): ";
        if (!docDong(r)) return;
        r = catKhoangTrang(r);
        if (r.empty()) break;
        ThemVoChong(p, r);                            // <-- goi ham cua Chan Huy
    }
}

// ---------- B4. Sua thong tin ----------
void suaThongTin(FamilyTree& t) {
    Person* p = chonNguoi(t, "[SUA] Chon nguoi can sua:");
    if (!p) return;
    cout << "Nhan Enter de giu nguyen gia tri hien tai.\n";
    string ten = p->hoTen, qh = p->quanHe;
    int ns, nm;
    if (!nhapHoTen("Ho ten [" + p->hoTen + "]: ", ten, true)) return;
    if (p->cha && !nhapHoTen("Quan he [" + p->quanHe + "]: ", qh, true)) return;
    if (!nhapNamHopLe(ns, nm, p->cha, p)) return;
    // Kiem tra rang buoc voi cac con: con khong duoc sinh truoc cha/me
    for (ChildNode* c = p->con; c; c = c->next)
        if (c->p->namSinh < ns) {
            cout << "  [!] Khong sua duoc: con \"" << c->p->hoTen << "\" sinh nam "
                 << c->p->namSinh << " som hon nam sinh moi.\n";
            return;
        }
    p->hoTen = ten; p->quanHe = qh; p->namSinh = ns; p->namMat = nm;
    cout << "  Da cap nhat.\n";
}

// ---------- B5. Xem thong tin mot nguoi ----------
int demCon(const Person* p) { int d = 0; for (ChildNode* c = p->con; c; c = c->next) d++; return d; }
void inThongTin(const Person* p) {
    cout << "----------------------------------------\n";
    cout << " ID        : " << p->id << "\n";
    cout << " Ho ten    : " << p->hoTen << "\n";
    cout << " Quan he   : " << p->quanHe << "\n";
    cout << " Nam sinh  : " << p->namSinh << "\n";
    cout << " Nam mat   : "; if (p->namMat) cout << p->namMat; else cout << "(con song)"; cout << "\n";
    if (p->namMat) cout << " Tho       : " << (p->namMat - p->namSinh) << " tuoi\n";
    cout << " Cha/me    : " << (p->cha ? p->cha->hoTen : "(la cu to)") << "\n";
    cout << " Vo/chong  : ";
    if (!p->vc) cout << "(chua co)";
    for (SpouseNode* s = p->vc; s; s = s->next) cout << s->ten << (s->next ? ", " : "");
    cout << "\n So con    : " << demCon(p) << "\n";
    cout << "----------------------------------------\n";
}
void xemThongTin(FamilyTree& t) {
    Person* p = chonNguoi(t, "[XEM] Chon nguoi can xem:");
    if (p) inThongTin(p);
}

// ---------- B6. Xoa thanh vien ----------
// CHINH SACH: xoa 1 nguoi => xoa luon toan bo nhanh con chau (vi con chau
// khong the "mo coi" trong cay). Hoi xac nhan, cho biet so nguoi bi xoa.
int demCayCon(const Person* p) {                       // so nut cua cay con, O(k)
    int d = 1;
    for (ChildNode* c = p->con; c; c = c->next) d += demCayCon(c->p);
    return d;
}
void huyNode(Person* p) {                              // duyet hau tu (LRN): con truoc, cha sau
    ChildNode* c = p->con;
    while (c) {
        ChildNode* tiep = c->next;
        huyNode(c->p);
        delete c;                                      // giai phong o DSLK con
        c = tiep;
    }
    SpouseNode* s = p->vc;
    while (s) { SpouseNode* tiep = s->next; delete s; s = tiep; }
    delete p;
}
void goKhoiDSCon(Person* cha, Person* con) {           // thao tac xoa node trong DSLK don
    ChildNode** pp = &cha->con;
    while (*pp && (*pp)->p != con) pp = &(*pp)->next;
    if (*pp) { ChildNode* x = *pp; *pp = x->next; delete x; }
}
void xoaThanhVien(FamilyTree& t) {
    Person* p = chonNguoi(t, "[XOA] Chon nguoi can xoa:");
    if (!p) return;
    int k = demCayCon(p);
    cout << "  Se xoa \"" << p->hoTen << "\"";
    if (k > 1) cout << " va " << (k - 1) << " nguoi la con chau";
    if (!p->cha) cout << " (day la CU TO -> xoa toan bo cay!)";
    cout << ". Xac nhan? (c/k): ";
    string r; if (!docDong(r) || (r != "c" && r != "C")) { cout << "  Da huy.\n"; return; }
    if (p->cha) { goKhoiDSCon(p->cha, p); }            // thao tac cat nhanh khoi cha truoc
    else        { t.root = nullptr; }
    huyNode(p);
    cout << "  Da xoa " << k << " nguoi.\n";
}

// ---------- B7. Hien thi toan bo cay ----------
// Duyet DFS tien tu (NLR), thut le theo do sau. O(n).
void inCay(const Person* p, const string& tienTo, bool laCuoi, bool laGoc) {
    cout << tienTo;
    if (!laGoc) cout << (laCuoi ? "`-- " : "|-- ");
    cout << p->hoTen << " (" << p->namSinh << "-";
    if (p->namMat) cout << p->namMat; else cout << "nay";
    cout << ")";
    if (p->vc) {
        cout << "  + ";
        for (SpouseNode* s = p->vc; s; s = s->next) cout << s->ten << (s->next ? ", " : "");
    }
    cout << "  [ID " << p->id << "]\n";
    string tiepTheo = tienTo + (laGoc ? "" : (laCuoi ? "    " : "|   "));
    for (ChildNode* c = p->con; c; c = c->next)
        inCay(c->p, tiepTheo, c->next == nullptr, false);
}
void hienThiCay(FamilyTree& t) {
    if (!t.root) { cout << "  Cay gia pha dang rong.\n"; return; }
    cout << "========== CAY GIA PHA (" << demCayCon(t.root) << " nguoi) ==========\n";
    inCay(t.root, "", true, true);
}

// ====================== het [B] =======================================

// ---------- main: chi de Hoang test rieng ----------
int main() {
    FamilyTree t;
    string c;
    while (true) {
        cout << "\n1.Them  2.Sua  3.Xem  4.Xoa  5.Hien thi cay  0.Thoat\nChon: ";
        if (!docDong(c)) break;
        c = catKhoangTrang(c);
        if      (c == "1") themThanhVien(t);
        else if (c == "2") suaThongTin(t);
        else if (c == "3") xemThongTin(t);
        else if (c == "4") xoaThanhVien(t);
        else if (c == "5") hienThiCay(t);
        else if (c == "0") break;
        else cout << "  [!] Lua chon khong hop le.\n";
    }
    if (t.root) huyNode(t.root);                       // giai phong bo nho khi thoat
    return 0;
}
