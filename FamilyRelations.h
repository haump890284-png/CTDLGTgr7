#ifndef FAMILY_RELATIONS_H
#define FAMILY_RELATIONS_H

#include "DataStructures.h"
#include <string>

using namespace std;

void printPersonSummary(PersonNode* p);
void viewAncestor(PersonNode* root);
void findParents(PersonNode* root, const string& targetName);
void showSpouses(PersonNode* root, const string& targetName);
void findSiblings(PersonNode* root, const string& targetName);
void showChildren(PersonNode* root, const string& targetName);

#endif