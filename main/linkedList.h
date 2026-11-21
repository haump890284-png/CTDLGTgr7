#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Tree.h"
#include <string>

// ==================== DANH SACH VO / CHONG ====================
SpouseNode* createSpouse(const std::string& ten);
void addSpouse(SpouseNode*& head, const std::string& ten);
SpouseNode* findSpouse(SpouseNode* head, const std::string& ten);
bool removeSpouse(SpouseNode*& head, const std::string& ten);
bool renameSpouse(SpouseNode* head,
                  const std::string& oldName,
                  const std::string& newName);
void printSpouses(SpouseNode* head);
void clearSpouses(SpouseNode*& head);

// ==================== DANH SACH CON ====================
ChildNode* createChild(Person* person);
void addChild(ChildNode*& head, Person* person);
ChildNode* findChild(ChildNode* head, Person* person);
bool removeChild(ChildNode*& head, Person* person);
void traverseChildren(ChildNode* head, void (*visit)(Person*));
int countChildren(ChildNode* head);

// Chi giai phong cac node lien ket ChildNode, khong xoa Person*.
void clearChildren(ChildNode*& head);

#endif
