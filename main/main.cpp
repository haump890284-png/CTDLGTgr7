#include "Tree.h"
#include "linkedList.h"
#include "QuanLyThanhVien.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ==================== HAM NHAP LIEU DUNG CHUNG ====================
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

bool nhapChuoi(const string& loiDan, string& giaTri) {
    while (true) {
        cout << loiDan;
        if (!getline(cin, giaTri)) return false;
        if (giaTri.find_first_not_of(" \\t\\r\\n") != string::npos)
            return true;
        cout << "Thong tin khong duoc de trong. Vui long nhap lai.\n";
    }
}

bool namHopLeCoBan(int namSinh, int namMat) {
    return namSinh > 0 && namMat >= 0 &&
           (namMat == 0 || namMat >= namSinh);
}

// ==================== CAC CHUC NANG DIEU PHOI CUA TV1 ====================
void inThongTinNguoi(const Person* p) {
    if (p == nullptr) {
        cout << "Khong tim thay thanh vien.\n";
        return;
    }

    cout << "\nMa thanh vien : " << p->id
         << "\nHo va ten     : " << p->hoTen
         << "\nQuan he       : " << p->quanHe
         << "\nNam sinh      : " << p->namSinh
         << "\nNam mat       : ";

    if (p->namMat == 0) cout << "Con song\n";
    else cout << p->namMat << '\n';

    cout << "Vo/chong      : ";
    printSpouses(p->vc);
    cout << '\n';
}

void taoCuToMoi(FamilyTree& cay) {
    if (!laCayRong(cay)) {
        cout << "Cay da co cu to.\n";
        return;
    }

    string ten;
    int namSinh, namMat;
    if (!nhapChuoi("Nhap ho ten cu to: ", ten) ||
        !nhapSoNguyen("Nhap nam sinh: ", namSinh) ||
        !nhapSoNguyen("Nhap nam mat (0 neu con song): ", namMat))
        return;

    if (!namHopLeCoBan(namSinh, namMat)) {
        cout << "Nam sinh hoac nam mat khong hop le.\n";
        return;
    }

    Person* cuTo = taoCuTo(cay, ten, namSinh, namMat);
    if (cuTo == nullptr) {
        cout << "Tao cu to that bai.\n";
        return;
    }
    cout << "Tao cu to thanh cong. ID: " << cuTo->id << '\n';
}

void timThanhVienTheoId(const FamilyTree& cay) {
    if (laCayRong(cay)) {
        cout << "Cay gia pha dang rong.\n";
        return;
    }

    int id;
    if (!nhapSoNguyen("Nhap ID can tim: ", id)) return;
    inThongTinNguoi(TimTheoId(cay.root, id));
}

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

void themTheHeTrenCuTo(FamilyTree& cay) {
    string ten, quanHeCuToCu;
    int namSinh, namMat;

    if (!nhapChuoi("Nhap ho ten cu to moi: ", ten) ||
        !nhapChuoi("Nhap quan he cua cu to hien tai voi cu to moi: ", quanHeCuToCu) ||
        !nhapSoNguyen("Nhap nam sinh: ", namSinh) ||
        !nhapSoNguyen("Nhap nam mat (0 neu con song): ", namMat))
        return;

    if (!namHopLeCoBan(namSinh, namMat)) {
        cout << "Nam sinh hoac nam mat khong hop le.\n";
        return;
    }

    Person* moi = TaoNode(cay, ten, "cu to", namSinh, namMat);
    if (!themCuToMoi(cay, moi, quanHeCuToCu)) {
        delete moi;
        cout << "Khong the them cu to moi. Kiem tra lai thong tin.\n";
        return;
    }
    cout << "Da them cu to moi. ID: " << moi->id << '\n';
}

// Quan ly danh sach vo/chong bang cac ham Linked List cua TV3.
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
    string ten, tenMoi;

    switch (chon) {
        case 1:
            if (!nhapChuoi("Nhap ten vo/chong: ", ten)) return;
            addSpouse(p->vc, ten);
            cout << "Da them vo/chong.\n";
            break;
        case 2:
            if (!nhapChuoi("Nhap ten can xoa: ", ten)) return;
            cout << (removeSpouse(p->vc, ten)
                     ? "Da xoa vo/chong.\n"
                     : "Khong tim thay ten can xoa.\n");
            break;
        case 3:
            if (!nhapChuoi("Nhap ten cu: ", ten) ||
                !nhapChuoi("Nhap ten moi: ", tenMoi)) return;
            cout << (renameSpouse(p->vc, ten, tenMoi)
                     ? "Da doi ten.\n"
                     : "Khong tim thay ten can doi.\n");
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le.\n";
    }
}

void inMenu() {
    cout << "\n========== QUAN LY CAY GIA PHA =========\n"
         << "1. Tao cu to\n"
         << "2. Them thanh vien \n" //Hoang
         << "3. Hien thi cay theo tung doi\n"
         << "4. Tim thanh vien theo ID\n"
         << "5. Tim thanh vien theo ho ten\n"
         << "6. Thong ke cay gia pha\n"
         << "7. Them the he phia tren cu to\n"
         << "8. Sua thong tin thanh vien \n" //Hoang
         << "9. Xoa thanh vien \n" //Hoang
         << "10. Tra cuu quan he gia dinh \n" //Tuong
         << "11. Quan ly danh sach vo/chong \n" //ChanHuy
         << "12. Hien thi cay dang phan cap \n"//Hoang
         << "13. Xem thong tin chi tiet thanh vien \n"//Hoang
         << "0. Thoat\n"
         << "========================================\n";
}

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
            case 10:
                cout << "Module tra cuu quan he cua TV5 chua duoc cung cap.\n";
                break;
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
