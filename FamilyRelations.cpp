#include "FamilyRelations.h"

#include <iostream>

using namespace std;

void printPersonSummary(const Person* p) {
    if (p == nullptr) return;

    cout << "  - ID: " << p->id
         << " | Ho ten: " << p->hoTen
         << " | Nam sinh: " << p->namSinh
         << " | Nam mat: "
         << (p->namMat > 0 ? to_string(p->namMat) : "Con song")
         << " | Quan he: " << p->quanHe << '\n';
}

void viewAncestor(const Person* root) {
    cout << "\n--- THONG TIN CU TO ---\n";
    if (root == nullptr) {
        cout << "[Thong bao] Cay gia pha dang rong, chua co cu to.\n";
        return;
    }

    printPersonSummary(root);
    cout << "  Vo/chong: ";
    if (root->vc == nullptr) {
        cout << "Chua cap nhat\n";
        return;
    }

    for (SpouseNode* s = root->vc; s != nullptr; s = s->next) {
        cout << s->ten;
        if (s->next != nullptr) cout << ", ";
    }
    cout << '\n';
}

void findParents(const Person* target) {
    cout << "\n--- TRA CUU CHA/ME ---\n";
    if (target == nullptr) {
        cout << "[Thong bao] Khong co thanh vien de tra cuu.\n";
        return;
    }

    cout << "Thanh vien: " << target->hoTen << " (ID " << target->id << ")\n";
    if (target->cha == nullptr) {
        cout << "[Thong bao] Day la cu to/goc cay, khong co thong tin cha/me phia tren.\n";
        return;
    }

    cout << "Cha/me duoc lien ket trong cay:\n";
    printPersonSummary(target->cha);
    cout << "  Vo/chong duoc ghi nhan cua cha/me: ";
    if (target->cha->vc == nullptr) {
        cout << "Chua co thong tin\n";
        return;
    }

    for (SpouseNode* s = target->cha->vc; s != nullptr; s = s->next) {
        cout << s->ten;
        if (s->next != nullptr) cout << ", ";
    }
    cout << '\n';
}

void showSpouses(const Person* target) {
    cout << "\n--- DANH SACH VO/CHONG ---\n";
    if (target == nullptr) {
        cout << "[Thong bao] Khong co thanh vien de tra cuu.\n";
        return;
    }

    cout << "Thanh vien: " << target->hoTen << " (ID " << target->id << ")\n";
    if (target->vc == nullptr) {
        cout << "[Thong bao] Thanh vien chua co thong tin vo/chong.\n";
        return;
    }

    int count = 1;
    for (SpouseNode* s = target->vc; s != nullptr; s = s->next)
        cout << "  " << count++ << ". " << s->ten << '\n';
}

void findSiblings(const Person* target) {
    cout << "\n--- DANH SACH ANH/CHI/EM ---\n";
    if (target == nullptr) {
        cout << "[Thong bao] Khong co thanh vien de tra cuu.\n";
        return;
    }

    cout << "Thanh vien: " << target->hoTen << " (ID " << target->id << ")\n";
    if (target->cha == nullptr) {
        cout << "[Thong bao] Cu to khong co anh/chi/em duoc bieu dien trong cay.\n";
        return;
    }

    bool hasSibling = false;
    for (ChildNode* node = target->cha->con; node != nullptr; node = node->next) {
        Person* sibling = node->p;
        if (sibling == nullptr || sibling == target) continue;

        hasSibling = true;
        string role;
        if (sibling->namSinh < target->namSinh)
            role = "[Anh/Chi] ";
        else if (sibling->namSinh > target->namSinh)
            role = "[Em] ";
        else
            role = "[Cung nam sinh] ";

        cout << role;
        printPersonSummary(sibling);
    }

    if (!hasSibling)
        cout << "[Thong bao] Thanh vien nay la con mot trong danh sach con cua cha/me da lien ket.\n";
}

void showChildren(const Person* target) {
    cout << "\n--- DANH SACH CON CAI ---\n";
    if (target == nullptr) {
        cout << "[Thong bao] Khong co thanh vien de tra cuu.\n";
        return;
    }

    cout << "Thanh vien: " << target->hoTen << " (ID " << target->id << ")\n";
    if (target->con == nullptr) {
        cout << "[Thong bao] Thanh vien hien chua co con cai.\n";
        return;
    }

    int count = 1;
    bool hasChild = false;
    for (ChildNode* node = target->con; node != nullptr; node = node->next) {
        if (node->p == nullptr) continue;
        hasChild = true;
        cout << "  Con thu " << count++ << ":\n";
        printPersonSummary(node->p);
    }

    if (!hasChild)
        cout << "[Thong bao] Thanh vien hien chua co con cai.\n";
}