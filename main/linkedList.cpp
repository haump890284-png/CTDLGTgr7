#include "LinkedList.h"
#include <iostream>

// Tao mot node phoi ngau va luu dia chi Person duoc truyen vao.
SpouseNode* createSpouse(Person* person) {
    if (person == nullptr) {
        return nullptr;
    }

    SpouseNode* node = new SpouseNode;
    node->p = person;
    node->next = nullptr;
    return node;
}

// Them mot Person vao cuoi danh sach vo/chong.
void addSpouse(SpouseNode*& head, Person* person) {
    SpouseNode* node = createSpouse(person);
    if (node == nullptr) {
        return;
    }

    if (head == nullptr) {
        head = node;
        return;
    }

    SpouseNode* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = node;
}

// Tim node phoi ngau bang cach so sanh dia chi Person*.
SpouseNode* findSpouse(SpouseNode* head, Person* person) {
    SpouseNode* temp = head;
    while (temp != nullptr) {
        if (temp->p == person) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Xoa khoi danh sach node dang tro den dung Person* duoc yeu cau.
bool removeSpouse(SpouseNode*& head, Person* person) {
    SpouseNode* prev = nullptr;
    SpouseNode* cur = head;

    while (cur != nullptr && cur->p != person) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == nullptr) {
        return false;
    }

    if (prev == nullptr) {
        head = cur->next;
    } else {
        prev->next = cur->next;
    }

    delete cur;
    return true;
}

// Doi ten cua dung nguoi phoi ngau duoc xac dinh bang Person*.
bool renameSpouse(SpouseNode* head, Person* person, const std::string& newName) {
    SpouseNode* node = findSpouse(head, person);
    if (node == nullptr || node->p == nullptr) {
        return false;
    }

    node->p->hoTen = newName;
    return true;
}

// In ten cac nguoi phoi ngau tu thong tin Person::hoTen.
void printSpouses(SpouseNode* head) {
    if (head == nullptr) {
        std::cout << "Khong co";
        return;
    }

    SpouseNode* temp = head;
    while (temp != nullptr) {
        if (temp->p != nullptr) {
            std::cout << temp->p->hoTen;
        } else {
            std::cout << "Khong xac dinh";
        }

        if (temp->next != nullptr) {
            std::cout << ", ";
        }
        temp = temp->next;
    }
}

// Giai phong cac node SpouseNode, khong xoa doi tuong Person duoc tro toi.
void clearSpouses(SpouseNode*& head) {
    while (head != nullptr) {
        SpouseNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Tao mot node lien ket de luu dia chi Person la con.
ChildNode* createChild(Person* person) {
    ChildNode* node = new ChildNode;
    node->p = person;
    node->next = nullptr;
    return node;
}

// Them mot Person vao cuoi danh sach cac con.
void addChild(ChildNode*& head, Person* person) {
    ChildNode* node = createChild(person);
    if (head == nullptr) {
        head = node;
        return;
    }

    ChildNode* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = node;
}

// Tim node con dua tren dia chi Person*.
ChildNode* findChild(ChildNode* head, Person* person) {
    ChildNode* temp = head;
    while (temp != nullptr) {
        if (temp->p == person) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Xoa khoi danh sach node dang tro den Person* duoc yeu cau.
bool removeChild(ChildNode*& head, Person* person) {
    ChildNode* prev = nullptr;
    ChildNode* cur = head;

    while (cur != nullptr && cur->p != person) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == nullptr) {
        return false;
    }

    if (prev == nullptr) {
        head = cur->next;
    } else {
        prev->next = cur->next;
    }

    delete cur;
    return true;
}

// Duyet lan luot cac Person trong danh sach con va goi ham visit.
void traverseChildren(ChildNode* head, void (*visit)(Person*)) {
    ChildNode* temp = head;
    while (temp != nullptr) {
        if (visit != nullptr) {
            visit(temp->p);
        }
        temp = temp->next;
    }
}

// Dem so node lien ket trong danh sach cac con.
int countChildren(ChildNode* head) {
    int count = 0;
    ChildNode* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Giai phong cac node ChildNode, khong xoa doi tuong Person duoc tro toi.
void clearChildren(ChildNode*& head) {
    while (head != nullptr) {
        ChildNode* temp = head;
        head = head->next;
        delete temp;
    }
}
