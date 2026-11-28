#include "LinkedList.h"
#include <iostream>

SpouseNode* createSpouse(const std::string& ten) {
    SpouseNode* node = new SpouseNode;
    node->ten = ten;
    node->next = nullptr;
    return node;
}

void addSpouse(SpouseNode*& head, const std::string& ten) {
    SpouseNode* node = createSpouse(ten);
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

SpouseNode* findSpouse(SpouseNode* head, const std::string& ten) {
    SpouseNode* temp = head;
    while (temp != nullptr) {
        if (temp->ten == ten) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

bool removeSpouse(SpouseNode*& head, const std::string& ten) {
    SpouseNode* prev = nullptr;
    SpouseNode* cur = head;
    while (cur != nullptr && cur->ten != ten) {
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

bool renameSpouse(SpouseNode* head,
                  const std::string& oldName,
                  const std::string& newName) {
    SpouseNode* node = findSpouse(head, oldName);
    if (node == nullptr) {
        return false;
    }
    node->ten = newName;
    return true;
}

void printSpouses(SpouseNode* head) {
    if (head == nullptr) {
        std::cout << "Khong co";
        return;
    }
    SpouseNode* temp = head;
    while (temp != nullptr) {
        std::cout << temp->ten;
        if (temp->next != nullptr) {
            std::cout << ", ";
        }
        temp = temp->next;
    }
}

void clearSpouses(SpouseNode*& head) {
    while (head != nullptr) {
        SpouseNode* temp = head;
        head = head->next;
        delete temp;
    }
}

ChildNode* createChild(Person* person) {
    ChildNode* node = new ChildNode;
    node->p = person;
    node->next = nullptr;
    return node;
}

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

void traverseChildren(ChildNode* head, void (*visit)(Person*)) {
    ChildNode* temp = head;
    while (temp != nullptr) {
        visit(temp->p);
        temp = temp->next;
    }
}

int countChildren(ChildNode* head) {
    int count = 0;
    ChildNode* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

void clearChildren(ChildNode*& head) {
    while (head != nullptr) {
        ChildNode* temp = head;
        head = head->next;
        delete temp;
    }
}
