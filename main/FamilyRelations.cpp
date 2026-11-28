#include "FamilyRelations.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Luu thong tin mot to tien kem vai tro va nhanh huyet thong dan den nguoi do.
struct AncestorInfo {
    const Person* person;
    string relationship;
    vector<const Person*> path;
};

// In thong tin tom tat cua mot thanh vien.
void printPersonSummary(const Person* p) {
    if (p == nullptr) return;

    const char* gioiTinh = p->gioiTinh == GioiTinh::Nam ? "Nam" :
                           (p->gioiTinh == GioiTinh::Nu ? "Nu" : "Chua xac dinh");
    cout << "  - ID: " << p->id
         << " | Ho ten: " << p->hoTen
         << " | Gioi tinh: " << gioiTinh
         << " | Nam sinh: " << p->namSinh
         << " | Nam mat: "
         << (p->namMat > 0 ? to_string(p->namMat) : "Con song")
         << " | Quan he: " << p->quanHe << '\n';
}

// In thong tin cu to va danh sach vo/chong da duoc ghi nhan.
void viewAncestor(const Person* root) {
    cout << "\n--- THONG TIN ";
    if (root != nullptr && root->gioiTinh == GioiTinh::Nu) cout << "BA TO";
    else if (root != nullptr && root->gioiTinh == GioiTinh::Nam) cout << "CU TO";
    else cout << "TO TIEN GOC";
    cout << " ---\n";
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
        if (s->p != nullptr) cout << s->p->hoTen;
        else cout << "Khong xac dinh";
        if (s->next != nullptr) cout << ", ";
    }
    cout << '\n';
}

// Kiem tra mot nguoi da xuat hien tren cung nhanh to tien hay chua de tranh lap chu trinh.
static bool appearsInPath(const vector<const Person*>& path, const Person* person) {
    for (const Person* item : path) {
        if (item == person) return true;
    }
    return false;
}

// Them cha ruot hoac me ruot vao the he tiep theo neu lien ket khong tao chu trinh.
static void appendAncestor(vector<AncestorInfo>& nextGeneration,
                           const AncestorInfo& current,
                           const Person* parent,
                           const string& parentRole) {
    if (parent == nullptr || appearsInPath(current.path, parent)) return;

    AncestorInfo ancestor;
    ancestor.person = parent;
    ancestor.relationship = parentRole + " cua " + current.relationship;
    ancestor.path = current.path;
    ancestor.path.push_back(parent);
    nextGeneration.push_back(ancestor);
}

// Chuyen duong dan huyet thong thanh ten vai tro de hien thi rieng tung vi tri to tien.
static string ancestorRoleLabel(int generation, const string& relationship) {
    if (generation == 1) {
        return relationship == "Cha" ? "Cha ruot" : "Me ruot";
    }

    if (generation == 2) {
        if (relationship == "Cha cua Cha") return "Ong noi (cha cua cha)";
        if (relationship == "Me cua Cha") return "Ba noi (me cua cha)";
        if (relationship == "Cha cua Me") return "Ong ngoai (cha cua me)";
        if (relationship == "Me cua Me") return "Ba ngoai (me cua me)";
    }

    return "To tien theo nhanh: " + relationship;
}

// Tra cuu cha, me, ong ba va cac the he to tien cua thanh vien theo tung the he.
void findParents(const Person* target) {
    cout << "\n--- TRA CUU CHA/ME VA TO TIEN ---\n";
    if (target == nullptr) {
        cout << "[Thong bao] Khong co thanh vien de tra cuu.\n";
        return;
    }

    cout << "Thanh vien: " << target->hoTen << " (ID " << target->id << ")\n";

    vector<AncestorInfo> currentGeneration;

    // Dua cha ruot vao the he thu nhat.
    if (target->chaRuot != nullptr) {
        AncestorInfo father;
        father.person = target->chaRuot;
        father.relationship = "Cha";
        father.path.push_back(target);
        father.path.push_back(target->chaRuot);
        currentGeneration.push_back(father);
    }

    // Dua me ruot vao the he thu nhat.
    if (target->meRuot != nullptr) {
        AncestorInfo mother;
        mother.person = target->meRuot;
        mother.relationship = "Me";
        mother.path.push_back(target);
        mother.path.push_back(target->meRuot);
        currentGeneration.push_back(mother);
    }

    if (currentGeneration.empty()) {
        cout << "[Thong bao] Chua co thong tin cha ruot va me ruot.\n";
        return;
    }

    int generation = 1;
    while (!currentGeneration.empty()) {
        cout << "\n--- THE HE " << generation;
        if (generation == 1)
            cout << ": CHA VA ME ---\n";
        else if (generation == 2)
            cout << ": ONG VA BA ---\n";
        else
            cout << ": TO TIEN ---\n";

        // Hien thi rieng tung nguoi theo vi tri trong nhanh huyet thong.
        for (const AncestorInfo& ancestor : currentGeneration) {
            cout << "  " << ancestorRoleLabel(generation, ancestor.relationship) << ":\n";
            printPersonSummary(ancestor.person);
        }

        vector<AncestorInfo> nextGeneration;

        // Lay cha ruot va me ruot cua tung nguoi de tao danh sach to tien o the he tiep theo.
        for (const AncestorInfo& ancestor : currentGeneration) {
            appendAncestor(nextGeneration, ancestor, ancestor.person->chaRuot, "Cha");
            appendAncestor(nextGeneration, ancestor, ancestor.person->meRuot, "Me");
        }

        if (nextGeneration.empty()) {
            if (generation == 1) {
                cout << "\n[Thong bao] Chua co thong tin ong, ba va cac the he xa hon.\n";
            }
            break;
        }

        currentGeneration.swap(nextGeneration);
        generation++;
    }
}

// Liet ke danh sach vo/chong cua thanh vien.
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
    for (SpouseNode* s = target->vc; s != nullptr; s = s->next) {
        cout << "  " << count++ << ". ";
        if (s->p != nullptr) cout << s->p->hoTen;
        else cout << "Khong xac dinh";
        cout << '\n';
    }
}

// Tim anh, chi, em trong danh sach con cua nut cha duyet.
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

// Liet ke cac con truc tiep cua thanh vien.
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
