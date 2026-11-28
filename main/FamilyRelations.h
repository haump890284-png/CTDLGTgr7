#ifndef FAMILY_RELATIONS_H
#define FAMILY_RELATIONS_H

#include "Tree.h"

void printPersonSummary(const Person* p);
void viewAncestor(const Person* root);
void findParents(const Person* target);
void showSpouses(const Person* target);
void findSiblings(const Person* target);
void showChildren(const Person* target);

#endif
