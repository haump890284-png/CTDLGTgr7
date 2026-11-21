#include "FamilyRelations.h"
#include "linkedList.h"
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

static string catKhoangTrangNoiBo(const string& s) {
    size_t a = s.find_first_not_of(" \t");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

static Person* chonThanhVienTraCuu(FamilyTree& t, const string& tieuDe) {
    if (t.root == nullptr) {
        cout << "  [!] Cay gia pha dang rong.\n";
        return nullptr;
    }

    string ten;
    cout << tieuDe << "\n";
    cout << "  Nhap ho ten can tra cuu: ";
    if (!getline(cin, ten)) return nullptr;
    ten = catKhoangTrangNoiBo(ten);

    if (ten.empty()) {
        cout << "  [!] Ho ten khong duoc de trong.\n";
        return nullptr;
    }

    vector<Person*> ds;
    TimTheoTen(t.root, ten, ds);

    if (ds.empty()) {
        cout << "  [!] Khong tim thay thanh vien \"" << ten << "\" trong gia pha.\n";
        return nullptr;
    }

    if (ds.size() == 1) {
        return ds[0];
    }

    cout << "  Co " << ds.size() << " nguoi trung ten, vui long chon theo ID:\n";
    for (Person* p : ds) {
        cout << "    ID " << p->id << " | Nam sinh: " << p->namSinh
             << " | Cha/me: " << (p->cha ? p->cha->hoTen : "(cu to)") << "\n";
    }

    cout << "  Nhap ID: ";
    string sId;
    if (!getline(cin, sId)) return nullptr;
    sId = catKhoangTrangNoiBo(sId);

    bool hopLe = !sId.empty() && sId.size() <= 9;
    for (char c : sId) {
        if (!isdigit((unsigned char)c)) hopLe = false;
    }
    if (!hopLe) {
        cout << "  [!] ID khong hop le.\n";
        return nullptr;
    }

    int id = stoi(sId);
    for (Person* p : ds) {
        if (p->id == id) return p;
    }

    cout << "  [!] ID khong nam trong danh sach tren.\n";
    return nullptr;
}

void inTomTatThanhVien(const Person* p) {
    if (p == nullptr) return;
    cout << "  - [ID " << p->id << "] Ho ten: " << p->hoTen
         << " | Nam sinh: " << p->namSinh
         << " | Nam mat: " << (p->namMat > 0 ? to_string(p->namMat) : "Con song")
         << " | Vai ve: " << p->quanHe << "\n";
}

void xemCuTo(const FamilyTree& t) {
    cout << "\n--- THONG TIN CU TO ---\n";
    Person* cuTo = layCuTo(t);
    if (cuTo == nullptr) {
        cout << "  [!] Cay gia pha hien dang trong, chua co thong tin cu to.\n";
        return;
    }

    inTomTatThanhVien(cuTo);
    cout << "  - Vo/Chong cua cu to: ";
    printSpouses(cuTo->vc);
    cout << "\n";
}

void timChaMe(FamilyTree& t) {
    cout << "\n--- TRA CUU THONG TIN CHA/ME ---\n";
    Person* target = chonThanhVienTraCuu(t, "[TRA CUU CHA/ME]");
    if (target == nullptr) return;

    if (target->cha == nullptr) {
        cout << "  [Thong bao] \"" << target->hoTen << "\" la Cu To (goc gia pha), khong co thong tin cha/me phia tren.\n";
        return;
    }

    Person* par = target->cha;
    cout << "  Cha/Me truc tiep trong cay:\n";
    inTomTatThanhVien(par);

    cout << "  Nguoi phoi ngau (Me/Cha con lai): ";
    printSpouses(par->vc);
    cout << "\n";
}

void hienThiVoChong(FamilyTree& t) {
    cout << "\n--- DANH SACH VO/CHONG ---\n";
    Person* target = chonThanhVienTraCuu(t, "[TRA CUU VO/CHONG]");
    if (target == nullptr) return;

    if (target->vc == nullptr) {
        cout << "  [Thong bao] \"" << target->hoTen << "\" hien chua ket hon hoac chua co thong tin vo/chong.\n";
        return;
    }

    cout << "  Vo/chong cua \"" << target->hoTen << "\":\n";
    SpouseNode* curr = target->vc;
    int stt = 1;
    while (curr != nullptr) {
        cout << "    " << stt++ << ". " << curr->ten << "\n";
        curr = curr->next;
    }
}

void timAnhChiEm(FamilyTree& t) {
    cout << "\n--- DANH SACH ANH/CHI/EM ---\n";
    Person* target = chonThanhVienTraCuu(t, "[TRA CUU ANH/CHI/EM]");
    if (target == nullptr) return;

    if (target->cha == nullptr) {
        cout << "  [Thong bao] \"" << target->hoTen << "\" la Cu To, khong co du lieu anh/chi/em cung cha me.\n";
        return;
    }

    ChildNode* siblingNode = target->cha->con;
    bool coAnhChiEm = false;

    while (siblingNode != nullptr) {
        if (siblingNode->p != target) {
            coAnhChiEm = true;
            string vaiVe = "";
            if (siblingNode->p->namSinh < target->namSinh) {
                vaiVe = "[Anh/Chi] ";
            } else if (siblingNode->p->namSinh > target->namSinh) {
                vaiVe = "[Em]      ";
            } else {
                vaiVe = "[Cung nam]";
            }
            cout << "  " << vaiVe;
            inTomTatThanhVien(siblingNode->p);
        }
        siblingNode = siblingNode->next;
    }

    if (!coAnhChiEm) {
        cout << "  [Thong bao] \"" << target->hoTen << "\" la con mot, khong co anh/chi/em.\n";
    }
}

void hienThiConCai(FamilyTree& t) {
    cout << "\n--- DANH SACH CON CAI ---\n";
    Person* target = chonThanhVienTraCuu(t, "[TRA CUU CON CAI]");
    if (target == nullptr) return;

    if (target->con == nullptr) {
        cout << "  [Thong bao] \"" << target->hoTen << "\" hien chua co con cai.\n";
        return;
    }

    cout << "  Danh sach con cai cua \"" << target->hoTen << "\" (" << countChildren(target->con) << " nguoi):\n";
    ChildNode* curr = target->con;
    int stt = 1;
    while (curr != nullptr) {
        cout << "  Con thu " << stt++ << ":\n";
        inTomTatThanhVien(curr->p);
        curr = curr->next;
    }
}