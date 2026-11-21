#ifndef FAMILY_RELATIONS_H
#define FAMILY_RELATIONS_H

#include "Tree.h"

// Cac ham tra cuu quan he su dung truc tiep node Person trong Tree.h.
void printPersonSummary(const Person* p);
void viewAncestor(Person* root);
void findParents(const Person* target);
void showSpouses(const Person* target);
void findSiblings(const Person* target);
void showChildren(const Person* target);

#endif
