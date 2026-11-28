#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Tree.h"

// Cac ham khoi tao va quan ly danh sach lien ket vo/chong bang Person*.
SpouseNode* createSpouse(Person* person);
void addSpouse(SpouseNode*& head, Person* person);
SpouseNode* findSpouse(SpouseNode* head, Person* person);
bool removeSpouse(SpouseNode*& head, Person* person);
bool renameSpouse(SpouseNode* head, Person* person, const std::string& newName);
void printSpouses(SpouseNode* head);
void clearSpouses(SpouseNode*& head);

// Cac ham khoi tao va quan ly danh sach lien ket cac con.
ChildNode* createChild(Person* person);
void addChild(ChildNode*& head, Person* person);
ChildNode* findChild(ChildNode* head, Person* person);
bool removeChild(ChildNode*& head, Person* person);
void traverseChildren(ChildNode* head, void (*visit)(Person*));
int countChildren(ChildNode* head);

// Chi giai phong cac node lien ket ChildNode, khong xoa cac Person*.
void clearChildren(ChildNode*& head);

#endif
