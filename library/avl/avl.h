#ifndef SPBU_2020_C_HOMEWORKS_AVL_H
#define SPBU_2020_C_HOMEWORKS_AVL_H

#include <stdbool.h>

typedef struct AVLTree AVLTree;

AVLTree *createTree();
void removeTree(AVLTree *tree);
bool exists(AVLTree *tree, int value);
bool addValue(AVLTree *tree, int value);
bool removeValue(AVLTree *tree, int value);
void printTree(AVLTree *tree);

#endif //SPBU_2020_C_HOMEWORKS_AVL_H
