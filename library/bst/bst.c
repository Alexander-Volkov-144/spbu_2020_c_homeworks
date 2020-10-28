#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTreeNode {
    int value;
    struct BinaryTreeNode* leftChild;
    struct BinaryTreeNode* rightChild;
} BinaryTreeNode;

struct BinarySearchTree {
    struct BinaryTreeNode* root;
};

enum Direction { left,right,none };

BinarySearchTree* createTree()
{
    BinarySearchTree* newTree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    newTree->root = NULL;
    return newTree;
}

void removeNodeRecursive(BinaryTreeNode* node)
{
    if (node->leftChild == NULL && node->rightChild == NULL) {
        free(node);
        return;
    }
    if (node->leftChild != NULL && node->rightChild == NULL) {
        removeNodeRecursive(node->leftChild);
        free(node);
        return;
    }
    if (node->leftChild == NULL && node->rightChild != NULL) {
        removeNodeRecursive(node->rightChild);
        free(node);
        return;
    }
    removeNodeRecursive(node->leftChild);
    removeNodeRecursive(node->rightChild);
    free(node);
}

void removeTree(BinarySearchTree* tree)
{
    removeNodeRecursive(tree->root);
    free(tree);
}

bool existsRecursive(BinaryTreeNode* node, int value)
{
    if (node->value == value) {
        return true;
    }
    if (value < node->value && node->leftChild != NULL) {
        return existsRecursive(node->leftChild, value);
    }
    if (value > node->value && node->rightChild != NULL) {
        return existsRecursive(node->rightChild, value);
    }
    return false;
}

bool isEmpty(BinarySearchTree* tree)
{
    return (tree->root == NULL);
}

bool exists(BinarySearchTree* tree, int value)
{
    if (isEmpty(tree)) {
        return false;
    }
    return existsRecursive(tree->root, value);
}

BinaryTreeNode* createNode(int value)
{
    BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    node->rightChild = NULL;
    node->leftChild = NULL;
    node->value = value;
    return node;
}

bool addValueRecursive(BinaryTreeNode* node, int value)
{
    if (node->value == value) {
        return false;
    }
    if (value < node->value) {
        if (node->leftChild == NULL) {
            node->leftChild = createNode(value);
            return true;
        } else {
            return addValueRecursive(node->leftChild, value);
        }
    }
    if (value > node->value) {
        if (node->rightChild == NULL) {
            node->rightChild = createNode(value);
            return true;
        } else {
            return addValueRecursive(node->rightChild, value);
        }
    }
}

bool addValue(BinarySearchTree* tree, int value)
{
    if (isEmpty(tree)) {
        tree->root = createNode(value);
    }
    return addValueRecursive(tree->root, value);
}

bool isLeaf(BinaryTreeNode* node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

bool changeParent(enum Direction d, BinaryTreeNode* parent, BinarySearchTree* tree, BinaryTreeNode* newNode)
{
    if (d == left) {
        parent->leftChild = newNode;
    }
    if (d == right) {
        parent->rightChild = newNode;
    }
    if (d == none) {
        tree->root = newNode;
    }
    return true;
}

int findAndDeleteMinimum(BinaryTreeNode* node, BinarySearchTree* tree)
{
    struct BinaryTreeNode* parent = node;
    BinaryTreeNode* currentTreeNode = node->rightChild;
    while (currentTreeNode->leftChild != NULL) {
        parent = currentTreeNode;
        currentTreeNode = currentTreeNode->leftChild;
    }
    int value = currentTreeNode->value;
    changeParent(left, parent, tree, NULL);
    free(currentTreeNode);
    return value;
}

bool removeRecursive(BinarySearchTree* tree, BinaryTreeNode* node, int value, BinaryTreeNode* parent, enum Direction d)
{
    if (node->value == value) {
        if (isLeaf(node)) {
            free(node);
            changeParent(d, parent, tree, NULL);
            return true;
        }
        if (node->leftChild == NULL && node->rightChild != NULL) {
            changeParent(d, parent, tree, node->rightChild);
            free(node);
            return true;
        }
        if (node->rightChild == NULL && node->leftChild != NULL) {
            changeParent(d, parent, tree, node->leftChild);
            free(node);
            return true;
        }
        node->value = findAndDeleteMinimum(node, tree);
    }
    if (node->value > value && node->leftChild != NULL) {
        return removeRecursive(tree, node->leftChild, value, node, left);
    }
    if (node->value < value && node->rightChild != NULL) {
        return removeRecursive(tree, node->rightChild, value, node, right);
    }
    return false;
}

bool removeValue(BinarySearchTree* tree, int value)
{
    if (isEmpty(tree)) {
        return false;
    }
    return removeRecursive(tree, tree->root, value, NULL, none);
}

void printNodeRecursive(BinaryTreeNode* node)
{
    if (node == NULL) {
        printf("null ");
    } else {
        printf("(%d ", node->value);
        printNodeRecursive(node->leftChild);
        printNodeRecursive(node->rightChild);
        printf(")");
    }
}

void printTree(BinarySearchTree* tree)
{
    printf("\n");
    printNodeRecursive(tree->root);
    printf("\n\n");
}
