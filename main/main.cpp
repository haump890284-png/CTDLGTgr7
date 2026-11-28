#include "Tree.h"
#include "QuanLyThanhVien.h"
#include "FamilyRelations.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ==================== CAC HAM NHAP LIEU DUNG CHUNG ====================
// Nhap so nguyen tren mot dong va tu choi ky tu thua sau gia tri.
bool nhapSoNguyen(const string& loiDan, int& giaTri) {
    while (true) {
        cout << loiDan;
        string dong;
        if (!getline(cin, dong)) return false;

        stringstream ss(dong);
        char kyTuThua;
        if ((ss >> giaTri) && !(ss >> kyTuThua)) return true;
        cout << "Du lieu khong hop le. Vui long nhap so nguyen.\n";
    }
}

// Nhap chuoi khong rong tu ban phim.
bool nhapChuoi(const string& loiDan, string& giaTri) {
    while (true) {
        cout << loiDan;
        if (!getline(cin, giaTri)) return false;
        if (giaTri.find_first_not_of(" \t\r\n") != string::npos) return true;
        cout << "Thong tin khong duoc de trong. Vui long nhap lai.\n";
    }
}

// Chuyen gioi tinh trong enum thanh chuoi de hien thi thong tin.
static string tenGioiTinh(GioiTinh gioiTinh) {
    if (gioiTinh == GioiTinh::Nam) return "Nam";
    if (gioiTinh == GioiTinh::Nu) return "Nu";
    return "Chua xac dinh";
}

// Yeu cau nguoi dung chon gioi tinh cho cu to hoac to tien moi.
static bool nhapGioiTinh(GioiTinh& gioiTinh) {
    while (true) {
        int luaChon;
        if (!nhapSoNguyen("Gioi tinh (1. Nam, 2. Nu): ", luaChon)) return false;
        if (luaChon == 1) {
            gioiTinh = GioiTinh::Nam;
            return true;
        }
        if (luaChon == 2) {
            gioiTinh = GioiTinh::Nu;
            return true;
        }
        cout << "Lua chon gioi tinh khong hop le.\n";
    }
}

// Kiem tra nam sinh va nam mat co nam trong thu tu thoi gian hop le hay khong.
bool namHopLeCoBan(int namSinh, int namMat) {
    return namSinh > 0 && namMat >= 0 &&
           (namMat == 0 || namMat >= namSinh);
}

// ==================== CAC CHUC NANG DIEU PHOI CUA TV1 ====================
// In thong tin co ban cua mot nguoi, bao gom ca hai cha me ruot.
void inThongTinNguoi(const Person* p) {
    if (p == nullptr) {
        cout << "Khong tim thay thanh vien.\n";
        return;
    }

    cout << "\nMa thanh vien : " << p->id
         << "\nHo va ten     : " << p->hoTen
         << "\nGioi tinh     : " << tenGioiTinh(p->gioiTinh)
         << "\nQuan he       : " << p->quanHe
         << "\nNam sinh      : " << p->namSinh
         << "\nNam mat       : ";

    if (p->namMat == 0) cout << "Con song\n";
    else cout << p->namMat << '\n';

    cout << "Cha ruot      : ";
    if (p->chaRuot) cout << p->chaRuot->hoTen << " (ID " << p->chaRuot->id << ")\n";
    else cout << "Chua co thong tin\n";

    cout << "Me ruot       : ";
    if (p->meRuot) cout << p->meRuot->hoTen << " (ID " << p->meRuot->id << ")\n";
    else cout << "Chua co thong tin\n";

    cout << "Nut cha duyet : ";
    if (p->cha) cout << p->cha->hoTen << " (ID " << p->cha->id << ")\n";
    else cout << "Khong co (nut goc)\n";

    cout << "Vo/chong      : ";
    printSpouses(p->vc);
    cout << '\n';
}

// Tao cu to dau tien va luu gioi tinh cung cac thong tin ca nhan.
void taoCuToMoi(FamilyTree& cay) {
    if (!laCayRong(cay)) {
        cout << "Cay da co cu to.\n";
        return;
    }

    string ten;
    int namSinh, namMat;
    GioiTinh gioiTinh;
    if (!nhapChuoi("Nhap ho ten cu to: ", ten) ||
        !nhapGioiTinh(gioiTinh) ||
        !nhapSoNguyen("Nhap nam sinh: ", namSinh) ||
        !nhapSoNguyen("Nhap nam mat (0 neu con song): ", namMat))
        return;

    if (!namHopLeCoBan(namSinh, namMat)) {
        cout << "Nam sinh hoac nam mat khong hop le.\n";
        return;
    }

    Person* cuTo = taoCuTo(cay, ten, namSinh, namMat, gioiTinh);
    if (cuTo == nullptr) {
        cout << "Tao cu to that bai.\n";
        return;
    }
    cout << "Tao "
         << (gioiTinh == GioiTinh::Nam ? "cu to" : "ba to")
         << " thanh cong. ID: " << cuTo->id << '\n';
}

// Tim va hien thi thong tin mot thanh vien dua tren ID.
void timThanhVienTheoId(const FamilyTree& cay) {
    if (laCayRong(cay)) {
        cout << "Cay gia pha dang rong.\n";
        return;
    }

    int id;
    if (!nhapSoNguyen("Nhap ID can tim: ", id)) return;
    inThongTinNguoi(TimTheoId(cay.root, id));
}

// Tim thanh vien theo ho ten va hien thi tat ca ket qua trung ten.
void timThanhVienTheoTen(const FamilyTree& cay) {
    if (laCayRong(cay)) {
        cout << "Cay gia pha dang rong.\n";
        return;
    }

    string ten;
    if (!nhapChuoi("Nhap ho ten can tim: ", ten)) return;

    vector<Person*> ketQua;
    TimTheoTen(cay.root, ten, ketQua);
    if (ketQua.empty()) {
        cout << "Khong tim thay thanh vien co ten: " << ten << '\n';
        return;
    }

    cout << "Tim thay " << ketQua.size() << " ket qua:\n";
    for (size_t i = 0; i < ketQua.size(); ++i) {
        cout << "\n--- Ket qua " << i + 1 << " ---\n";
        inThongTinNguoi(ketQua[i]);
    }
}

// Thong ke so luong node, chieu cao, so la va bac cua cu to trong cay duyet.
void thongKeCay(const FamilyTree& cay) {
    if (laCayRong(cay)) {
        cout << "Cay gia pha dang rong.\n";
        return;
    }

    cout << "\nTong so thanh vien : " << demSoNode(cay.root)
         << "\nChieu cao cay      : " << chieuCao(cay.root)
         << "\nSo thanh vien la   : " << demSoLa(cay.root)
         << "\nSo con cua cu to   : " << bacCuaNode(cay.root) << '\n';
}

// Them mot the he o phia tren cu to va cap nhat lien ket cha/me theo gioi tinh.
void themTheHeTrenCuTo(FamilyTree& cay) {
    string ten, quanHeCuToCu;
    int namSinh, namMat;
    GioiTinh gioiTinh;

    if (!nhapChuoi("Nhap ho ten to tien moi: ", ten) ||
        !nhapGioiTinh(gioiTinh))
        return;

    // Chi nhap quan he voi cu to cu khi cay da co node goc.
    if (!laCayRong(cay) &&
        !nhapChuoi("Nhap quan he cua cu to hien tai voi cu to moi: ", quanHeCuToCu))
        return;

    if (!nhapSoNguyen("Nhap nam sinh: ", namSinh) ||
        !nhapSoNguyen("Nhap nam mat (0 neu con song): ", namMat))
        return;

    if (!namHopLeCoBan(namSinh, namMat)) {
        cout << "Nam sinh hoac nam mat khong hop le.\n";
        return;
    }

    // Bao dam to tien moi dung thu tu thoi gian va khong ghi de cha/me ruot da biet.
    if (cay.root != nullptr) {
        if (namSinh > cay.root->namSinh) {
            cout << "Nam sinh cua cu to moi khong the sau nam sinh cua cu to hien tai.\n";
            return;
        }
        if (namMat != 0 && cay.root->namSinh > namMat + 1) {
            cout << "Nam mat cua cu to moi khong hop ly so voi nam sinh cua cu to hien tai.\n";
            return;
        }
        if (gioiTinh == GioiTinh::Nam && cay.root->chaRuot != nullptr) {
            cout << "Cu to hien tai da co thong tin cha ruot; khong the gan them cha ruot moi.\n";
            return;
        }
        if (gioiTinh == GioiTinh::Nu && cay.root->meRuot != nullptr) {
            cout << "Cu to hien tai da co thong tin me ruot; khong the gan them me ruot moi.\n";
            return;
        }
    }

    Person* moi = TaoNode(cay, ten, "cu to", namSinh, namMat, gioiTinh);
    if (!themCuToMoi(cay, moi, quanHeCuToCu)) {
        delete moi;
        cout << "Khong the them cu to moi. Kiem tra lai thong tin.\n";
        return;
    }
    cout << "Da them "
         << (gioiTinh == GioiTinh::Nam ? "cu to moi" : "ba to moi")
         << ". ID: " << moi->id << '\n';

    // Hien thi ro lien ket huyet thong vua duoc cap nhat tren cu to cu.
    if (cay.root->con != nullptr) {
        Person* cuToCu = cay.root->con->p;
        cout << "Da ghi nhan " << cuToCu->hoTen << " la ";
        if (gioiTinh == GioiTinh::Nam) cout << "con cua cha ruot ";
        else cout << "con cua me ruot ";
        cout << moi->hoTen << ".\n";
    }
}

// Them, xoa hoac doi ten vo/chong bang dia chi Person* de xac dinh dung nguoi.
void quanLyVoChong(FamilyTree& cay) {
    if (laCayRong(cay)) {
        cout << "Cay gia pha dang rong.\n";
        return;
    }

    int id;
    if (!nhapSoNguyen("Nhap ID thanh vien: ", id)) return;
    Person* p = TimTheoId(cay.root, id);
    if (p == nullptr) {
        cout << "Khong tim thay thanh vien.\n";
        return;
    }

    cout << "Danh sach vo/chong cua " << p->hoTen << ": ";
    printSpouses(p->vc);
    cout << "\n1. Them vo/chong\n2. Xoa vo/chong\n3. Doi ten vo/chong\n0. Quay lai\n";

    int chon;
    if (!nhapSoNguyen("Chon: ", chon)) return;
    if (chon == 0) return;
    if (chon < 1 || chon > 3) {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    int idDoiTac;
    if (!nhapSoNguyen("Nhap ID nguoi vo/chong: ", idDoiTac)) return;
    Person* doiTac = TimTheoId(cay.root, idDoiTac);
    if (doiTac == nullptr) {
        cout << "Khong tim thay nguoi co ID vua nhap.\n";
        return;
    }
    if (doiTac == p) {
        cout << "Mot nguoi khong the la vo/chong cua chinh minh.\n";
        return;
    }

    switch (chon) {
        case 1:
            cout << (ThemVoChong(p, doiTac)
                     ? "Da them lien ket vo/chong hai chieu.\n"
                     : "Khong the them lien ket vo/chong.\n");
            break;
        case 2: {
            bool daXoaA = removeSpouse(p->vc, doiTac);
            bool daXoaB = removeSpouse(doiTac->vc, p);
            cout << ((daXoaA || daXoaB)
                     ? "Da xoa lien ket vo/chong hai chieu.\n"
                     : "Hai nguoi chua co lien ket vo/chong.\n");
            break;
        }
        case 3: {
            string tenMoi;
            if (!nhapChuoi("Nhap ho ten moi cua nguoi vo/chong: ", tenMoi)) return;
            cout << (renameSpouse(p->vc, doiTac, tenMoi)
                     ? "Da cap nhat ho ten nguoi vo/chong.\n"
                     : "Khong tim thay lien ket vo/chong de doi ten.\n");
            break;
        }
    }
}

// Chon mot thanh vien theo ID de tra cuu cac quan he trong gia pha.
Person* chonThanhVienTheoID(FamilyTree& cay) {
    if (laCayRong(cay)) {
        cout << "Cay gia pha dang rong.\n";
        return nullptr;
    }

    int id;
    if (!nhapSoNguyen("Nhap ID thanh vien can tra cuu: ", id)) return nullptr;
    Person* p = TimTheoId(cay.root, id);
    if (p == nullptr) cout << "Khong tim thay thanh vien co ID " << id << ".\n";
    return p;
}

// Dieu phoi cac chuc nang tra cuu cu to, cha me, vo chong, anh chi em va con cai.
void traCuuQuanHeGiaDinh(FamilyTree& cay) {
    if (laCayRong(cay)) {
        cout << "Cay gia pha dang rong. Hay them du lieu truoc.\n";
        return;
    }

    while (true) {
        cout << "\n========== TRA CUU QUAN HE GIA DINH =========\n"
             << "1. Xem thong tin cu to/ba to\n"
             << "2. Tra cuu cha/me, ong/ba va to tien\n"
             << "3. Xem danh sach vo/chong\n"
             << "4. Tim anh/chi/em\n"
             << "5. Xem danh sach con cai\n"
             << "0. Quay lai\n"
             << "=============================================\n";

        int luaChon;
        if (!nhapSoNguyen("Chon chuc nang: ", luaChon)) return;
        if (luaChon == 0) return;
        if (luaChon == 1) {
            viewAncestor(cay.root);
            continue;
        }
        if (luaChon < 2 || luaChon > 5) {
            cout << "Lua chon khong hop le.\n";
            continue;
        }

        Person* target = chonThanhVienTheoID(cay);
        if (target == nullptr) continue;

        switch (luaChon) {
            case 2: findParents(target); break;
            case 3: showSpouses(target); break;
            case 4: findSiblings(target); break;
            case 5: showChildren(target); break;
            default: cout << "Lua chon khong hop le.\n";
        }
    }
}

// In danh sach cac chuc nang chinh cua chuong trinh quan ly gia pha.
void inMenu() {
    cout << "\n========== QUAN LY CAY GIA PHA =========\n"
         << "1. Tao cu to/ba to\n"
         << "2. Them thanh vien (TV4)\n"
         << "3. Hien thi cay theo tung doi\n"
         << "4. Tim thanh vien theo ID\n"
         << "5. Tim thanh vien theo ho ten\n"
         << "6. Thong ke cay gia pha\n"
         << "7. Them the he to tien phia tren\n"
         << "8. Sua thong tin thanh vien (TV4)\n"
         << "9. Xoa thanh vien (TV4)\n"
         << "10. Tra cuu quan he gia dinh (TV5)\n"
         << "11. Quan ly danh sach vo/chong (TV3)\n"
         << "12. Hien thi cay dang phan cap (TV4)\n"
         << "13. Xem thong tin chi tiet thanh vien (TV4)\n"
         << "0. Thoat\n"
         << "========================================\n";
}

// Khoi tao cay, tiep nhan lua chon menu va giai phong bo nho khi ket thuc.
int main() {
    FamilyTree cay;
    khoiTaoCay(cay);

    while (true) {
        inMenu();
        int luaChon;
        if (!nhapSoNguyen("Nhap lua chon: ", luaChon)) break;

        switch (luaChon) {
            case 1: taoCuToMoi(cay); break;
            case 2: themThanhVien(cay); break;
            case 3: inTheoDoi(cay); break;
            case 4: timThanhVienTheoId(cay); break;
            case 5: timThanhVienTheoTen(cay); break;
            case 6: thongKeCay(cay); break;
            case 7: themTheHeTrenCuTo(cay); break;
            case 8: suaThongTin(cay); break;
            case 9: xoaThanhVien(cay); break;
            case 10: traCuuQuanHeGiaDinh(cay); break;
            case 11: quanLyVoChong(cay); break;
            case 12: hienThiCay(cay); break;
            case 13: xemThongTin(cay); break;
            case 0:
                giaiPhongCay(cay.root);
                cay.root = nullptr;
                cout << "Da thoat chuong trinh.\n";
                return 0;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }

    giaiPhongCay(cay.root);
    cay.root = nullptr;
    cout << "Da thoat chuong trinh.\n";
    return 0;
}
