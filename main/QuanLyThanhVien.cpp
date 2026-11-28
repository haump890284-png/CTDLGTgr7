#include "QuanLyThanhVien.h"
#include "LinkedList.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>

using namespace std;

// ====================== CAC HAM HO TRO NHAP LIEU ======================
const int NAM_MIN = 1000;

// Tra ve nam hien tai de kiem tra nam sinh va nam mat.
int namHienTai() {
    time_t t = time(nullptr);
    return localtime(&t)->tm_year + 1900;
}

// Cat khoang trang o dau va cuoi chuoi nhap.
string catKhoangTrang(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

// Doc mot dong tu ban phim va thong bao neu het du lieu.
bool docDong(string& s) {
    return static_cast<bool>(getline(cin, s));
}

// Nhap ho ten khong rong va khong chua chu so; co the cho phep Enter de bo qua.
bool nhapHoTen(const string& nhan, string& out, bool allowEmpty = false) {
    string s;
    while (true) {
        cout << nhan;
        if (!docDong(s)) return false;
        s = catKhoangTrang(s);
        if (s.empty() && allowEmpty) return true;
        if (s.empty()) {
            cout << "  [!] Ho ten khong duoc de trong.\n";
            continue;
        }

        bool coChuSo = false;
        for (char c : s) {
            if (isdigit(static_cast<unsigned char>(c))) coChuSo = true;
        }
        if (coChuSo) {
            cout << "  [!] Ho ten khong duoc chua chu so.\n";
            continue;
        }
        out = s;
        return true;
    }
}

// Nhap so nguyen khong am va cho phep bo trong khi dang cap nhat thong tin.
bool nhapSo(const string& nhan, int& out, bool allowEmpty, bool& boTrong) {
    string s;
    boTrong = false;
    while (true) {
        cout << nhan;
        if (!docDong(s)) return false;
        s = catKhoangTrang(s);
        if (s.empty() && allowEmpty) {
            boTrong = true;
            return true;
        }
        if (s.empty()) {
            cout << "  [!] Khong duoc de trong.\n";
            continue;
        }

        bool ok = s.size() <= 9;
        for (char c : s) {
            if (!isdigit(static_cast<unsigned char>(c))) ok = false;
        }
        if (!ok) {
            cout << "  [!] Vui long nhap so nguyen khong am.\n";
            continue;
        }
        out = stoi(s);
        return true;
    }
}

// Chuyen enum gioi tinh thanh chuoi de hien thi tren man hinh.
static string tenGioiTinh(GioiTinh gioiTinh) {
    if (gioiTinh == GioiTinh::Nam) return "Nam";
    if (gioiTinh == GioiTinh::Nu) return "Nu";
    return "Chua xac dinh";
}

// Yeu cau nguoi dung chon gioi tinh Nam hoac Nu.
static bool nhapGioiTinh(GioiTinh& gioiTinh) {
    while (true) {
        cout << "Gioi tinh (1. Nam, 2. Nu): ";
        int luaChon;
        bool boTrong;
        if (!nhapSo("", luaChon, false, boTrong)) return false;
        if (luaChon == 1) {
            gioiTinh = GioiTinh::Nam;
            return true;
        }
        if (luaChon == 2) {
            gioiTinh = GioiTinh::Nu;
            return true;
        }
        cout << "  [!] Chi duoc chon 1 (Nam) hoac 2 (Nu).\n";
    }
}

// Kiem tra nam sinh va nam mat cua mot thanh vien so voi mot phu huynh.
string kiemTraVoiMotPhuHuynh(int ns, const Person* phuHuynh, const string& vaiTro) {
    if (phuHuynh == nullptr) return "";
    if (ns < phuHuynh->namSinh) {
        return "Nam sinh cua con khong the som hon " + vaiTro + " (" +
               to_string(phuHuynh->namSinh) + ").";
    }
    if (phuHuynh->namMat != 0 && ns > phuHuynh->namMat + 1) {
        return "Nam sinh cua con bat hop ly vi " + vaiTro + " da mat nam " +
               to_string(phuHuynh->namMat) + ".";
    }
    return "";
}

// Kiem tra rang buoc nam sinh, nam mat va ca hai lien ket cha ruot/me ruot.
string kiemTraNam(int ns, int nm, const Person* chaRuot, const Person* meRuot) {
    int nay = namHienTai();
    if (ns < NAM_MIN || ns > nay) {
        return "Nam sinh phai trong khoang " + to_string(NAM_MIN) + " - " + to_string(nay) + ".";
    }
    if (nm != 0) {
        if (nm < ns) return "Nam mat khong duoc nho hon nam sinh.";
        if (nm > nay) return "Nam mat khong duoc lon hon nam hien tai.";
    }

    string loiCha = kiemTraVoiMotPhuHuynh(ns, chaRuot, "cha ruot");
    if (!loiCha.empty()) return loiCha;
    return kiemTraVoiMotPhuHuynh(ns, meRuot, "me ruot");
}

// Nhap nam sinh va nam mat den khi du lieu hop le voi ca cha va me.
bool nhapNamHopLe(int& ns, int& nm, const Person* chaRuot,
                  const Person* meRuot, const Person* cu = nullptr) {
    bool boTrong;
    while (true) {
        string nhanS = cu ? "Nam sinh [" + to_string(cu->namSinh) + "] (Enter = giu): " : "Nam sinh: ";
        string nhanM = cu ? "Nam mat [" + (cu->namMat ? to_string(cu->namMat) : string("con song")) +
                            "] (Enter = giu, 0 = con song): "
                          : "Nam mat (0 = con song): ";
        int s2 = cu ? cu->namSinh : 0;
        int m2 = cu ? cu->namMat : 0;

        if (!nhapSo(nhanS, s2, cu != nullptr, boTrong)) return false;
        if (boTrong) s2 = cu->namSinh;
        if (!nhapSo(nhanM, m2, cu != nullptr, boTrong)) return false;
        if (boTrong) m2 = cu->namMat;

        string loi = kiemTraNam(s2, m2, chaRuot, meRuot);
        if (loi.empty()) {
            ns = s2;
            nm = m2;
            return true;
        }
        cout << "  [!] " << loi << " Moi nhap lai.\n";
    }
}

// ====================== CAC HAM CHON THANH VIEN ======================
// In thong tin tom tat mot nguoi trong danh sach ket qua tim kiem.
void inTomTatUngVien(const Person* p) {
    if (p == nullptr) return;
    cout << "   ID " << p->id << " | " << p->hoTen
         << " | " << tenGioiTinh(p->gioiTinh)
         << " | sinh " << p->namSinh << '\n';
}

// Tim va chon mot thanh vien theo ho ten; xu ly truong hop trung ten bang ID.
Person* chonNguoi(FamilyTree& t, const string& tieuDe) {
    if (!t.root) {
        cout << "  [!] Cay gia pha dang rong.\n";
        return nullptr;
    }

    string ten;
    cout << tieuDe << "\n";
    if (!nhapHoTen("  Nhap ho ten can tim: ", ten)) return nullptr;

    vector<Person*> ds;
    TimTheoTen(t.root, ten, ds);
    if (ds.empty()) {
        cout << "  [!] Khong tim thay \"" << ten << "\".\n";
        return nullptr;
    }
    if (ds.size() == 1) return ds[0];

    cout << "  Co " << ds.size() << " nguoi trung ten, hay chon theo ID:\n";
    for (Person* p : ds) inTomTatUngVien(p);

    bool boTrong;
    int id;
    if (!nhapSo("  Nhap ID: ", id, false, boTrong)) return nullptr;
    for (Person* p : ds) {
        if (p->id == id) return p;
    }
    cout << "  [!] ID khong nam trong danh sach tren.\n";
    return nullptr;
}

// Chon cha hoac me theo ten, cho phep bo qua va loc dung gioi tinh tuong ung.
bool chonNguoiTheoVaiTro(FamilyTree& t, const string& nhan,
                         GioiTinh gioiTinhCanChon, Person*& ketQua) {
    ketQua = nullptr;
    string ten;
    if (!nhapHoTen(nhan + " (Enter = chua ro/bo qua): ", ten, true)) return false;
    if (ten.empty()) return true;

    vector<Person*> dsTimDuoc;
    TimTheoTen(t.root, ten, dsTimDuoc);
    if (dsTimDuoc.empty()) {
        cout << "  [!] Khong tim thay thanh vien \"" << ten << "\" trong cay.\n";
        return false;
    }

    vector<Person*> ungVien;
    for (Person* p : dsTimDuoc) {
        if (p->gioiTinh == gioiTinhCanChon) ungVien.push_back(p);
    }
    if (ungVien.empty()) {
        cout << "  [!] Khong co nguoi ten \"" << ten << "\" co gioi tinh phu hop ("
             << tenGioiTinh(gioiTinhCanChon) << ").\n";
        return false;
    }
    if (ungVien.size() == 1) {
        ketQua = ungVien[0];
        return true;
    }

    cout << "  Co nhieu nguoi cung ten va cung gioi tinh, hay chon ID:\n";
    for (Person* p : ungVien) inTomTatUngVien(p);
    bool boTrong;
    int id;
    if (!nhapSo("  Nhap ID: ", id, false, boTrong)) return false;
    for (Person* p : ungVien) {
        if (p->id == id) {
            ketQua = p;
            return true;
        }
    }
    cout << "  [!] ID khong nam trong danh sach ung vien.\n";
    return false;
}

// ====================== B3. THEM THANH VIEN ==========================
// Nhap thong tin thanh vien, chon rieng cha/me va chi tao mot canh duyet.
void themThanhVien(FamilyTree& t) {
    Person* chaRuot = nullptr;
    Person* meRuot = nullptr;
    Person* nutChaDuyet = nullptr;

    if (!laCayRong(t)) {
        cout << "[THEM] Chon cha ruot va me ruot cua thanh vien moi.\n";
        if (!chonNguoiTheoVaiTro(t, "Nhap ho ten CHA RUOT", GioiTinh::Nam, chaRuot)) return;
        if (!chonNguoiTheoVaiTro(t, "Nhap ho ten ME RUOT", GioiTinh::Nu, meRuot)) return;

        if (chaRuot == nullptr && meRuot == nullptr) {
            cout << "  [!] Phai chon it nhat cha hoac me de gan thanh vien vao cay.\n";
            return;
        }
    } else {
        cout << "[THEM] Cay dang rong -> thanh vien dau tien se la CU TO.\n";
    }

    string ten;
    if (!nhapHoTen("Ho ten: ", ten)) return;

    GioiTinh gioiTinh;
    if (!nhapGioiTinh(gioiTinh)) return;

    int ns, nm;
    if (!nhapNamHopLe(ns, nm, chaRuot, meRuot)) return;

    // Chon mot trong hai phu huynh lam nut cha duyet de tranh dua mot nguoi vao cay hai lan.
    if (chaRuot != nullptr && meRuot != nullptr) {
        while (true) {
            cout << "Nut cha de duyet cay (1. Cha ruot, 2. Me ruot): ";
            int luaChon;
            bool boTrong;
            if (!nhapSo("", luaChon, false, boTrong)) return;
            if (luaChon == 1) {
                nutChaDuyet = chaRuot;
                break;
            }
            if (luaChon == 2) {
                nutChaDuyet = meRuot;
                break;
            }
            cout << "  [!] Chi duoc chon 1 hoac 2.\n";
        }
    } else {
        nutChaDuyet = (chaRuot != nullptr) ? chaRuot : meRuot;
    }

    // Tu dong xac dinh quan he con trai/con gai tu gioi tinh da nhap.
    string quanHe = laCayRong(t) ? "cu to" :
                    (gioiTinh == GioiTinh::Nam ? "con trai" : "con gai");
    Person* p = TaoNode(t, ten, quanHe, ns, nm, gioiTinh);

    bool themThanhCong;
    if (laCayRong(t)) {
        themThanhCong = themVaoCay(t, nullptr, p);
    } else {
        themThanhCong = GanChaMe(p, chaRuot, meRuot, nutChaDuyet);
    }

    if (!themThanhCong) {
        delete p;
        cout << "  [!] Khong the them thanh vien. Kiem tra lai lien ket cha/me va lien ket duyet.\n";
        return;
    }

    cout << "  Da them \"" << ten << "\" (ID " << p->id << ").\n";

    // Luu vo/chong bang Person* den mot thanh vien da ton tai trong cay.
    cout << "Them vo/chong da co trong gia pha? (1. Co, 0. Khong): ";
    int luaChonVoChong;
    bool boTrong;
    if (!nhapSo("", luaChonVoChong, false, boTrong)) return;
    if (luaChonVoChong == 1) {
        Person* doiTac = chonNguoi(t, "[VO/CHONG] Chon thanh vien la vo/chong:");
        if (doiTac == p) {
            cout << "  [!] Mot nguoi khong the la vo/chong cua chinh minh.\n";
        } else if (doiTac != nullptr && ThemVoChong(p, doiTac)) {
            cout << "  Da lien ket vo/chong hai chieu voi " << doiTac->hoTen << ".\n";
        } else if (doiTac != nullptr) {
            cout << "  [!] Khong the tao lien ket vo/chong.\n";
        }
    } else if (luaChonVoChong != 0) {
        cout << "  [!] Lua chon khong hop le, bo qua them vo/chong.\n";
    }
}

// ====================== B4. SUA THONG TIN ============================
// Cap nhat ten, quan he hien thi va moc thoi gian sau khi kiem tra cac rang buoc.
void suaThongTin(FamilyTree& t) {
    Person* p = chonNguoi(t, "[SUA] Chon nguoi can sua:");
    if (!p) return;

    cout << "Nhan Enter de giu nguyen gia tri hien tai.\n";
    cout << "Gioi tinh hien tai: " << tenGioiTinh(p->gioiTinh)
         << " (khong sua gioi tinh tai day de tranh sai lech lien ket cha/me).\n";

    string ten = p->hoTen;
    string qh = p->quanHe;
    int ns, nm;
    if (!nhapHoTen("Ho ten [" + p->hoTen + "]: ", ten, true)) return;
    if (p->chaRuot || p->meRuot) {
        if (!nhapHoTen("Quan he [" + p->quanHe + "]: ", qh, true)) return;
    }
    if (!nhapNamHopLe(ns, nm, p->chaRuot, p->meRuot, p)) return;

    // Kiem tra ca nhung nguoi co lien ket huyet thong toi p, ke ca khi p khong la nut cha duyet.
    // Duyet cay de bao dam nam sinh/nam mat moi cua p khong mau thuan voi con ruot.
    vector<Person*> stack;
    if (t.root) stack.push_back(t.root);
    while (!stack.empty()) {
        Person* cur = stack.back();
        stack.pop_back();
        if (cur->chaRuot == p || cur->meRuot == p) {
            if (cur->namSinh < ns) {
                cout << "  [!] Khong sua duoc: con \"" << cur->hoTen
                     << "\" sinh som hon nam sinh moi cua thanh vien.\n";
                return;
            }
            if (nm != 0 && cur->namSinh > nm + 1) {
                cout << "  [!] Khong sua duoc: con \"" << cur->hoTen
                     << "\" sinh sau nam mat moi cua thanh vien.\n";
                return;
            }
        }
        for (ChildNode* c = cur->con; c; c = c->next) stack.push_back(c->p);
    }

    p->hoTen = ten;
    p->quanHe = qh;
    p->namSinh = ns;
    p->namMat = nm;

    cout << "  Da cap nhat.\n";
}

// ====================== B5. XEM THONG TIN ============================
// Dem so con duoc gan truc tiep trong danh sach canh duyet.
int demCon(const Person* p) {
    int d = 0;
    for (ChildNode* c = p->con; c; c = c->next) d++;
    return d;
}

// In day du thong tin thanh vien, bao gom cha ruot, me ruot va nut cha duyet.
void inThongTin(const Person* p) {
    if (p == nullptr) return;
    cout << "----------------------------------------\n";
    cout << " ID        : " << p->id << "\n";
    cout << " Ho ten    : " << p->hoTen << "\n";
    cout << " Gioi tinh : " << tenGioiTinh(p->gioiTinh) << "\n";
    cout << " Quan he   : " << p->quanHe << "\n";
    cout << " Nam sinh  : " << p->namSinh << "\n";
    cout << " Nam mat   : ";
    if (p->namMat) cout << p->namMat;
    else cout << "(con song)";
    cout << "\n";
    if (p->namMat) cout << " Tho       : " << (p->namMat - p->namSinh) << " tuoi\n";

    cout << " Cha ruot  : ";
    if (p->chaRuot) cout << p->chaRuot->hoTen << " (ID " << p->chaRuot->id << ")";
    else cout << "(chua co thong tin)";
    cout << "\n Me ruot   : ";
    if (p->meRuot) cout << p->meRuot->hoTen << " (ID " << p->meRuot->id << ")";
    else cout << "(chua co thong tin)";
    cout << "\n Nut cha duyet: ";
    if (p->cha) cout << p->cha->hoTen << " (ID " << p->cha->id << ")";
    else cout << "(nut goc/khong co)";

    cout << "\n Vo/chong  : ";
    printSpouses(p->vc);
    cout << "\n So con duyet: " << demCon(p) << "\n";
    cout << "----------------------------------------\n";
}

// Tim va hien thi thong tin chi tiet cua mot thanh vien.
void xemThongTin(FamilyTree& t) {
    Person* p = chonNguoi(t, "[XEM] Chon nguoi can xem:");
    if (p) inThongTin(p);
}

// ====================== B6. XOA THANH VIEN ===========================
// Dem so node trong nhanh duyet se bi xoa neu xoa mot thanh vien.
int demCayCon(const Person* p) {
    if (p == nullptr) return 0;
    int d = 1;
    for (ChildNode* c = p->con; c; c = c->next) d += demCayCon(c->p);
    return d;
}

// Thu thap dia chi cac node trong nhanh duyet truoc khi giai phong bo nho.
void thuThapNodeXoa(const Person* p, vector<const Person*>& ds) {
    if (p == nullptr) return;
    ds.push_back(p);
    for (ChildNode* c = p->con; c; c = c->next) thuThapNodeXoa(c->p, ds);
}

// Kiem tra mot con tro co nam trong danh sach node sap bi giai phong hay khong.
bool namTrongDanhSachXoa(const Person* p, const vector<const Person*>& ds) {
    for (const Person* node : ds) {
        if (node == p) return true;
    }
    return false;
}

// Xoa cac lien ket cha/me ruot tro den node sap bi giai phong trong phan cay con lai.
void lamSachLienKetChaMe(Person* p, const vector<const Person*>& dsXoa) {
    if (p == nullptr) return;
    if (namTrongDanhSachXoa(p->chaRuot, dsXoa)) p->chaRuot = nullptr;
    if (namTrongDanhSachXoa(p->meRuot, dsXoa)) p->meRuot = nullptr;

    // Loai bo cac lien ket vo/chong hai chieu dang tro den thanh vien sap bi giai phong.
    SpouseNode* cur = p->vc;
    while (cur != nullptr) {
        SpouseNode* tiep = cur->next;
        if (namTrongDanhSachXoa(cur->p, dsXoa)) removeSpouse(p->vc, cur->p);
        cur = tiep;
    }

    for (ChildNode* c = p->con; c; c = c->next) lamSachLienKetChaMe(c->p, dsXoa);
}

// Giai phong mot node va toan bo nhanh con theo thu tu hau tu.
void huyNode(Person* p) {
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

// Cat lien ket con khoi danh sach duyet cua phu huynh ma khong xoa node Person.
void goKhoiDSCon(Person* cha, Person* con) {
    if (cha == nullptr || con == nullptr) return;
    removeChild(cha->con, con);
}

// Xoa mot thanh vien va nhanh hau due, dong thoi lam sach lien ket cha/me con tro den nhanh do.
void xoaThanhVien(FamilyTree& t) {
    Person* p = chonNguoi(t, "[XOA] Chon nguoi can xoa:");
    if (!p) return;

    int k = demCayCon(p);
    cout << "  Se xoa \"" << p->hoTen << "\"";
    if (k > 1) cout << " va " << (k - 1) << " nguoi la con chau";
    if (!p->cha) cout << " (day la CU TO -> xoa toan bo cay!)";
    cout << ". Xac nhan? (c/k): ";

    string r;
    if (!docDong(r) || (r != "c" && r != "C")) {
        cout << "  Da huy.\n";
        return;
    }

    vector<const Person*> dsXoa;
    thuThapNodeXoa(p, dsXoa);
    if (p->cha) goKhoiDSCon(p->cha, p);
    else t.root = nullptr;

    // Cac thanh vien khong nam trong nhanh bi xoa khong duoc giu con tro cha/me da giai phong.
    lamSachLienKetChaMe(t.root, dsXoa);
    huyNode(p);
    cout << "  Da xoa " << k << " nguoi.\n";
}

// ====================== B7. HIEN THI CAY =============================
// Duyet DFS tien tu va hien thi gioi tinh, ID, moc thoi gian theo do sau.
void inCay(const Person* p, const string& tienTo, bool laCuoi, bool laGoc) {
    if (p == nullptr) return;
    cout << tienTo;
    if (!laGoc) cout << (laCuoi ? "`-- " : "|-- ");
    cout << p->hoTen << " (" << p->namSinh << "-";
    if (p->namMat) cout << p->namMat;
    else cout << "nay";
    cout << ", " << tenGioiTinh(p->gioiTinh) << ")";

    if (p->vc) {
        cout << "  + ";
        printSpouses(p->vc);
    }
    cout << "  [ID " << p->id << "]\n";

    string tiepTheo = tienTo + (laGoc ? "" : (laCuoi ? "    " : "|   "));
    for (ChildNode* c = p->con; c; c = c->next) {
        inCay(c->p, tiepTheo, c->next == nullptr, false);
    }
}

// Hien thi cay gia pha theo cau truc lien ket duyet da chon.
void hienThiCay(FamilyTree& t) {
    if (!t.root) {
        cout << "  Cay gia pha dang rong.\n";
        return;
    }
    cout << "========== CAY GIA PHA (" << demCayCon(t.root) << " nguoi) ==========\n";
    inCay(t.root, "", true, true);
}

// Giai phong toan bo cay khi chuong trinh ket thuc.
void giaiPhongCay(Person* root) {
    huyNode(root);
}
