#ifndef SPBU_2020_C_HOMEWORKS_BST_H
#define SPBU_2020_C_HOMEWORKS_BST_H

#include <stdbool.h>

typedef struct BinarySearchTree BinarySearchTree;

BinarySearchTree *createTree();
void removeTree(BinarySearchTree *tree);
bool exists(BinarySearchTree *tree, int value);
bool addValue(BinarySearchTree *tree, int value);
bool removeValue(BinarySearchTree *tree, int value);
void printTree(BinarySearchTree *tree);

#endif //SPBU_2020_C_HOMEWORKS_BST_H
