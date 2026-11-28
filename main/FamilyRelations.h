#ifndef FAMILY_RELATIONS_H
#define FAMILY_RELATIONS_H

#include "Tree.h"

// In thong tin tom tat cua mot thanh vien.
void printPersonSummary(const Person* p);

// Hien thi thong tin cu to va danh sach vo/chong.
void viewAncestor(const Person* root);

// Tra cuu cha, me, ong ba va cac the he to tien cua mot thanh vien.
void findParents(const Person* target);

// Hien thi danh sach vo/chong cua mot thanh vien.
void showSpouses(const Person* target);

// Tim danh sach anh, chi, em cua mot thanh vien.
void findSiblings(const Person* target);

// Hien thi danh sach con truc tiep cua mot thanh vien.
void showChildren(const Person* target);

#endif
