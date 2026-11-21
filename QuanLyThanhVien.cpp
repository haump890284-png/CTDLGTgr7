#include "QuanLyThanhVien.h"
#include "linkedList.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>

using namespace std;

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
        addSpouse(p->vc, r);                            // <-- goi ham cua Chan Huy
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
void huyNode(Person* p) {                              // giai phong hau tu: con truoc, cha sau
    if (p == nullptr) return;

    while (p->con != nullptr) {
        ChildNode* nodeCon = p->con;
        Person* nguoiCon = nodeCon->p;
        p->con = nodeCon->next;
        huyNode(nguoiCon);
        delete nodeCon;
    }

    clearSpouses(p->vc);
    delete p;
}

void goKhoiDSCon(Person* cha, Person* con) {
    if (cha == nullptr || con == nullptr) return;
    removeChild(cha->con, con); // chi cat node lien ket, khong xoa Person
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


// Giai phong toan bo cay khi chuong trinh ket thuc.
void giaiPhongCay(Person* root) {
    huyNode(root);
}
