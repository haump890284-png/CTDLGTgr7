#include "FamilyRelations.h"
#include <iostream>

using namespace std;

void printPersonSummary(PersonNode* p) {
    if (p == nullptr) return;
    cout << "  - Ho ten: " << p->fullName
         << " | Nam sinh: " << p->birthYear
         << " | Nam mat: " << (p->deathYear > 0 ? to_string(p->deathYear) : "Con song")
         << " | Vai ve: " << p->relationToParent << "\n";
}

void viewAncestor(PersonNode* root) {
    cout << "\n--- THONG TIN CU TO ---\n";
    if (root == nullptr) {
        cout << "[Thong bao] Cay gia pha hien dang trong, chua co thong tin cu to!\n";
        return;
    }
    printPersonSummary(root);

    cout << "  - Vo/Chong cua cu to: ";
    if (root->spouseHead == nullptr) {
        cout << "Chua cap nhat\n";
    } else {
        SpouseNode* s = root->spouseHead;
        while (s != nullptr) {
            cout << s->fullName << (s->next != nullptr ? ", " : "");
            s = s->next;
        }
        cout << "\n";
    }
}

void findParents(PersonNode* root, const string& targetName) {
    cout << "\n--- TRA CUU CHA/ME CUA [" << targetName << "] ---\n";
    if (root == nullptr) {
        cout << "[Loi] Cay gia pha rong!\n";
        return;
    }

    PersonNode* target = findPerson(root, targetName);
    if (target == nullptr) {
        cout << "[Thong bao] Khong tim thay thanh vien \"" << targetName << "\" trong gia pha.\n";
        return;
    }

    if (target->parent == nullptr) {
        cout << "[Thong bao] \"" << targetName << "\" la Cu To (goc gia pha), khong co thong tin cha/me phia tren.\n";
        return;
    }

    PersonNode* par = target->parent;
    cout << "Cha/Me truc tiep trong cay:\n";
    printPersonSummary(par);

    cout << "Nguoi phoi ngau (Me/Cha con lai): ";
    if (par->spouseHead == nullptr) {
        cout << "Chua co thong tin\n";
    } else {
        SpouseNode* s = par->spouseHead;
        while (s != nullptr) {
            cout << s->fullName << (s->next != nullptr ? ", " : "");
            s = s->next;
        }
        cout << "\n";
    }
}

void showSpouses(PersonNode* root, const string& targetName) {
    cout << "\n--- DANH SACH VO/CHONG CUA [" << targetName << "] ---\n";
    if (root == nullptr) {
        cout << "[Loi] Cay gia pha rong!\n";
        return;
    }

    PersonNode* target = findPerson(root, targetName);
    if (target == nullptr) {
        cout << "[Thong bao] Khong tim thay thanh vien \"" << targetName << "\" trong gia pha.\n";
        return;
    }

    if (target->spouseHead == nullptr) {
        cout << "[Thong bao] \"" << targetName << "\" hien chua ket hon hoac chua co thong tin vo/chong.\n";
        return;
    }

    SpouseNode* curr = target->spouseHead;
    int count = 1;
    while (curr != nullptr) {
        cout << "  " << count++ << ". " << curr->fullName << "\n";
        curr = curr->next;
    }
}

void findSiblings(PersonNode* root, const string& targetName) {
    cout << "\n--- DANH SACH ANH/CHI/EM CUA [" << targetName << "] ---\n";
    if (root == nullptr) {
        cout << "[Loi] Cay gia pha rong!\n";
        return;
    }

    PersonNode* target = findPerson(root, targetName);
    if (target == nullptr) {
        cout << "[Thong bao] Khong tim thay thanh vien \"" << targetName << "\" trong gia pha.\n";
        return;
    }

    if (target->parent == nullptr) {
        cout << "[Thong bao] \"" << targetName << "\" la Cu To, khong co du lieu anh/chi/em cung cha me.\n";
        return;
    }

    ChildNode* siblingNode = target->parent->childHead;
    bool hasSibling = false;

    while (siblingNode != nullptr) {
        if (siblingNode->person != target) {
            hasSibling = true;
            string role = "";
            if (siblingNode->person->birthYear < target->birthYear) {
                role = "[Anh/Chi] ";
            } else if (siblingNode->person->birthYear > target->birthYear) {
                role = "[Em]      ";
            } else {
                role = "[Cung nam]";
            }
            cout << "  " << role;
            printPersonSummary(siblingNode->person);
        }
        siblingNode = siblingNode->next;
    }

    if (!hasSibling) {
        cout << "[Thong bao] \"" << targetName << "\" la con mot, khong co anh/chi/em.\n";
    }
}

void showChildren(PersonNode* root, const string& targetName) {
    cout << "\n--- DANH SACH CON CAI CUA [" << targetName << "] ---\n";
    if (root == nullptr) {
        cout << "[Loi] Cay gia pha rong!\n";
        return;
    }

    PersonNode* target = findPerson(root, targetName);
    if (target == nullptr) {
        cout << "[Thong bao] Khong tim thay thanh vien \"" << targetName << "\" trong gia pha.\n";
        return;
    }

    if (target->childHead == nullptr) {
        cout << "[Thong bao] \"" << targetName << "\" hien chua co con cai.\n";
        return;
    }

    ChildNode* curr = target->childHead;
    int count = 1;
    while (curr != nullptr) {
        cout << "  Con thu " << count++ << ":\n";
        printPersonSummary(curr->person);
        curr = curr->next;
    }
}