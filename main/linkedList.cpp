#include "linkedList.h"
#include <iostream>

using namespace std;

// ==================== DANH SACH VO / CHONG ====================
SpouseNode* createSpouse(const string& ten) {
    SpouseNode* p = new SpouseNode;
    p->ten = ten;
    p->next = nullptr;
    return p;
}

void addSpouse(SpouseNode*& head, const string& ten) {
    if (ten.empty()) return;

    SpouseNode* p = createSpouse(ten);
    if (head == nullptr) {
        head = p;
        return;
    }

    SpouseNode* cur = head;
    while (cur->next != nullptr)
        cur = cur->next;
    cur->next = p;
}

SpouseNode* findSpouse(SpouseNode* head, const string& ten) {
    SpouseNode* cur = head;
    while (cur != nullptr) {
        if (cur->ten == ten)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

bool removeSpouse(SpouseNode*& head, const string& ten) {
    SpouseNode* prev = nullptr;
    SpouseNode* cur = head;

    while (cur != nullptr && cur->ten != ten) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == nullptr) return false;

    if (prev == nullptr)
        head = cur->next;
    else
        prev->next = cur->next;

    delete cur;
    return true;
}

bool renameSpouse(SpouseNode* head,
                  const string& oldName,
                  const string& newName) {
    if (newName.empty()) return false;
    SpouseNode* p = findSpouse(head, oldName);
    if (p == nullptr) return false;

    p->ten = newName;
    return true;
}

void printSpouses(SpouseNode* head) {
    if (head == nullptr) {
        cout << "Khong co";
        return;
    }

    SpouseNode* cur = head;
    while (cur != nullptr) {
        cout << cur->ten;
        if (cur->next != nullptr) cout << ", ";
        cur = cur->next;
    }
}

void clearSpouses(SpouseNode*& head) {
    while (head != nullptr) {
        SpouseNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ==================== DANH SACH CON ====================
ChildNode* createChild(Person* person) {
    if (person == nullptr) return nullptr;

    ChildNode* p = new ChildNode;
    p->p = person;
    p->next = nullptr;
    return p;
}

void addChild(ChildNode*& head, Person* person) {
    if (person == nullptr || findChild(head, person) != nullptr)
        return;

    ChildNode* p = createChild(person);
    if (p == nullptr) return;

    if (head == nullptr) {
        head = p;
        return;
    }

    ChildNode* cur = head;
    while (cur->next != nullptr)
        cur = cur->next;
    cur->next = p;
}

ChildNode* findChild(ChildNode* head, Person* person) {
    ChildNode* cur = head;
    while (cur != nullptr) {
        if (cur->p == person)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

bool removeChild(ChildNode*& head, Person* person) {
    ChildNode* prev = nullptr;
    ChildNode* cur = head;

    while (cur != nullptr && cur->p != person) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == nullptr) return false;

    if (prev == nullptr)
        head = cur->next;
    else
        prev->next = cur->next;

    // Chi xoa node danh sach; Person do cay gia pha quan ly.
    delete cur;
    return true;
}

void traverseChildren(ChildNode* head, void (*visit)(Person*)) {
    if (visit == nullptr) return;

    ChildNode* cur = head;
    while (cur != nullptr) {
        visit(cur->p);
        cur = cur->next;
    }
}

int countChildren(ChildNode* head) {
    int count = 0;
    for (ChildNode* cur = head; cur != nullptr; cur = cur->next)
        ++count;
    return count;
}

void clearChildren(ChildNode*& head) {
    while (head != nullptr) {
        ChildNode* tmp = head;
        head = head->next;
        // Khong delete tmp->p vi Person* thuoc quyen quan ly cua Tree.
        delete tmp;
    }
}
