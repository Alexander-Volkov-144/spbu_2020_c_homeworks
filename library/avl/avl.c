#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode AVLNode;

typedef struct BinaryTreeNode {
    int value;
    struct AVLNode* leftChild;
    struct AVLNode* rightChild;
} BinaryTreeNode;

struct AVLNode{
    BinaryTreeNode BTNode;
    int height;
};

struct AVLTree {
    AVLNode* root;
};

enum Direction {
    left,
    right,
    none
};

AVLTree* createTree()
{
    AVLTree* newTree = (AVLTree*)malloc(sizeof(AVLTree));
    newTree->root = NULL;
    return newTree;
}

void removeNodeRecursive(AVLNode* node)
{
    if (node->BTNode.leftChild == NULL && node->BTNode.rightChild == NULL) {
        free(node);
        return;
    }
    if (node->BTNode.leftChild != NULL && node->BTNode.rightChild == NULL) {
        removeNodeRecursive(node->BTNode.leftChild);
        free(node);
        return;
    }
    if (node->BTNode.leftChild == NULL && node->BTNode.rightChild != NULL) {
        removeNodeRecursive(node->BTNode.rightChild);
        free(node);
        return;
    }
    removeNodeRecursive(node->BTNode.leftChild);
    removeNodeRecursive(node->BTNode.rightChild);
    free(node);
}

void removeTree(AVLTree* tree)
{
    removeNodeRecursive(tree->root);
    free(tree);
}

bool existsRecursive(AVLNode* node, int value)
{
    if (node->BTNode.value == value) {
        return true;
    }
    if (value < node->BTNode.value && node->BTNode.leftChild != NULL) {
        return existsRecursive(node->BTNode.leftChild, value);
    }
    if (value > node->BTNode.value && node->BTNode.rightChild != NULL) {
        return existsRecursive(node->BTNode.rightChild, value);
    }
    return false;
}

bool isEmpty(AVLTree* tree)
{
    return (tree->root == NULL);
}

bool exists(AVLTree* tree, int value)
{
    if (isEmpty(tree)) {
        return false;
    }
    return existsRecursive(tree->root, value);
}

AVLNode* createNode(int value)
{
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->BTNode.rightChild = NULL;
    node->BTNode.leftChild = NULL;
    node->BTNode.value = value;
    return node;
}

bool addValueRecursive(AVLNode* node, int value)
{
    if (node->BTNode.value == value) {
        return false;
    }
    if (value < node->BTNode.value) {
        if (node->BTNode.leftChild == NULL) {
            node->BTNode.leftChild = createNode(value);
            return true;
        } else {
            return addValueRecursive(node->BTNode.leftChild, value);
        }
    }
    if (value > node->BTNode.value) {
        if (node->BTNode.rightChild == NULL) {
            node->BTNode.rightChild = createNode(value);
            return true;
        } else {
            return addValueRecursive(node->BTNode.rightChild, value);
        }
    }
}

bool addValue(AVLTree* tree, int value)
{
    if (isEmpty(tree)) {
        tree->root = createNode(value);
    }
    return addValueRecursive(tree->root, value);
}

bool isLeaf(AVLNode* node)
{
    return node->BTNode.leftChild == NULL && node->BTNode.rightChild == NULL;
}

bool changeParent(enum Direction d, AVLNode* parent, AVLTree* tree, AVLNode* newNode)
{
    if (d == left) {
        parent->BTNode.leftChild = newNode;
    }
    if (d == right) {
        parent->BTNode.rightChild = newNode;
    }
    if (d == none) {
        tree->root = newNode;
    }
    return true;
}

int findAndDeleteMinimum(AVLNode* node, AVLTree* tree)
{
    struct AVLNode* parent = node;
    AVLNode* currentTreeNode = node->BTNode.rightChild;
    while (currentTreeNode->BTNode.leftChild != NULL) {
        parent = currentTreeNode;
        currentTreeNode = currentTreeNode->BTNode.leftChild;
    }
    int value = currentTreeNode->BTNode.value;
    changeParent(left, parent, tree, NULL);
    free(currentTreeNode);
    return value;
}

bool removeRecursive(AVLTree* tree, AVLNode* node, int value, AVLNode* parent, enum Direction d)
{
    if (node->BTNode.value == value) {
        if (isLeaf(node)) {
            free(node);
            changeParent(d, parent, tree, NULL);
            return true;
        }
        if (node->BTNode.leftChild == NULL && node->BTNode.rightChild != NULL) {
            changeParent(d, parent, tree, node->BTNode.rightChild);
            free(node);
            return true;
        }
        if (node->BTNode.rightChild == NULL && node->BTNode.leftChild != NULL) {
            changeParent(d, parent, tree, node->BTNode.leftChild);
            free(node);
            return true;
        }
        node->BTNode.value = findAndDeleteMinimum(node, tree);
    }
    if (node->BTNode.value > value && node->BTNode.leftChild != NULL) {
        return removeRecursive(tree, node->BTNode.leftChild, value, node, left);
    }
    if (node->BTNode.value < value && node->BTNode.rightChild != NULL) {
        return removeRecursive(tree, node->BTNode.rightChild, value, node, right);
    }
    return false;
}

bool removeValue(AVLTree* tree, int value)
{
    if (isEmpty(tree)) {
        return false;
    }
    return removeRecursive(tree, tree->root, value, NULL, none);
}

void printNodeRecursive(AVLNode* node)
{
    if (node == NULL) {
        printf("null ");
    } else {
        printf("(%d ", node->BTNode.value);
        printNodeRecursive(node->BTNode.leftChild);
        printNodeRecursive(node->BTNode.rightChild);
        printf(")");
    }
}

void printTree(AVLTree* tree)
{
    printf("\n");
    printNodeRecursive(tree->root);
    printf("\n\n");
}
