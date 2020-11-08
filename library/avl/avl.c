#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int value;
    struct AVLNode* leftChild;
    struct AVLNode* rightChild;
    int height;
} AVLNode;

struct AVLTree {
    struct AVLNode* root;
};

enum Direction {
    left,
    right,
    none
};

int getHeight(AVLNode* node)
{
    return node == NULL ? 0 : node->height;
}

int getBalanceFactor(AVLNode* node)
{
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

void updateHeight(AVLNode* node)
{
    int heightLeft = (node->leftChild == NULL ? 0 : getHeight(node->leftChild));
    int heightRight = (node->rightChild == NULL ? 0 : getHeight(node->rightChild));
    node->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}

struct AVLNode* rotateRight(AVLNode* root)
{
    struct AVLNode* pivot = root->leftChild;
    root->leftChild = pivot->rightChild;
    pivot->rightChild = root;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

struct AVLNode* rotateLeft(AVLNode* root)
{
    struct AVLNode* pivot = root->rightChild;
    root->rightChild = pivot->leftChild;
    pivot->leftChild = root;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

AVLNode* balance(AVLNode* node)
{
    if (node == NULL) {
        return node;
    }
    if (node->leftChild != NULL) {
        node->leftChild = balance(node->leftChild);
        updateHeight(node);
    }
    if (node->rightChild != NULL) {
        node->rightChild = balance(node->rightChild);
        updateHeight(node);
    }
    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->rightChild) < 0)
            node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    } else if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->leftChild) > 0)
            node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    } else {
        return node;
    }
}


AVLTree* createTree()
{
    AVLTree* newTree = (AVLTree*)malloc(sizeof(AVLTree));
    newTree->root = NULL;
    return newTree;
}

bool isLeaf(AVLNode* node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

void removeNodeRecursive(AVLNode* node)
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

void removeTree(AVLTree* tree)
{
    if (tree->root != NULL)
        removeNodeRecursive(tree->root);
    free(tree);
}

bool existsRecursive(AVLNode* node, int value)
{
    if (node->value == value) {
        return true;
    }
    if (node->value > value && node->leftChild != NULL) {
        return existsRecursive(node->leftChild, value);
    }
    if (node->value < value && node->rightChild != NULL) {
        return existsRecursive(node->rightChild, value);
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
    node->rightChild = NULL;
    node->leftChild = NULL;
    node->value = value;
    node->height = 1;
    return node;
}

bool addValueRecursive(AVLNode* node, int value)
{
    if (node->value == value) {
        return false;
    }
    if (node->value > value) {
        if (node->leftChild == NULL) {
            node->leftChild = createNode(value);
            return true;
        } else {
            return addValueRecursive(node->leftChild, value);
        }
    }
    if (node->value < value) {
        if (node->rightChild == NULL) {
            node->rightChild = createNode(value);
            return true;
        } else {
            return addValueRecursive(node->rightChild, value);
        }
    }
}

bool addValue(AVLTree* tree, int value)
{
    if (isEmpty(tree))
        tree->root = createNode(value);
    addValueRecursive(tree->root, value);
    tree->root = balance(tree->root);
    return true;
}

bool changeParent(AVLTree* tree, AVLNode* newNode, AVLNode* parent, enum Direction direction)
{
    if (direction == left) {
        parent->leftChild = newNode;
    }
    if (direction == right) {
        parent->rightChild = newNode;
    }
    if (direction == none) {
        tree->root = newNode;
    }
    return true;
}

AVLNode* findMinimum(AVLNode* node, AVLNode** parent)
{
    if (node->leftChild == NULL) {
        return node;
    }
    *parent = node;
    AVLNode* currentTreeNode = node->leftChild;
    while (currentTreeNode->leftChild != NULL) {
        *parent = currentTreeNode;
        currentTreeNode = currentTreeNode->leftChild;
    }
    return currentTreeNode;
}

bool removeRecursive(AVLTree* tree, AVLNode* node, int value, AVLNode* parent, enum Direction direction)
{
    if (node->value == value) {
        if (isLeaf(node)) {
            free(node);
            changeParent(tree, NULL, parent, direction);
            return true;
        }
        if (node->leftChild == NULL && node->rightChild != NULL) {
            changeParent(tree, node->rightChild, parent, direction);
            free(node);
            return true;
        }
        if (node->rightChild == NULL && node->leftChild != NULL) {
            changeParent(tree, node->leftChild, parent, direction);
            free(node);
            return true;
        }
        AVLNode* temporaryParent = NULL;
        AVLNode* nodeWithMinimumValue = findMinimum(node->rightChild, &temporaryParent);
        node->value = nodeWithMinimumValue->value;
        if (nodeWithMinimumValue == node->rightChild) {
            if (nodeWithMinimumValue->rightChild != NULL)
                changeParent(tree, nodeWithMinimumValue->rightChild, node, right);
            else
                changeParent(tree, NULL, node, right);
        } else {
            if (nodeWithMinimumValue->rightChild != NULL)
                changeParent(tree, nodeWithMinimumValue->rightChild, temporaryParent, left);
            else
                changeParent(tree, NULL, temporaryParent, left);
        }
        free(nodeWithMinimumValue);
        return true;
    }
    if (node->value > value && node->leftChild != NULL) {
        return removeRecursive(tree, node->leftChild, value, node, left);
    }
    if (node->value < value && node->rightChild != NULL) {
        return removeRecursive(tree, node->rightChild, value, node, right);
    }
    return false;
}

bool removeValue(AVLTree* tree, int value)
{
    if (isEmpty(tree)) {
        return false;
    }
    removeRecursive(tree, tree->root, value, NULL, none);
    tree->root = balance(tree->root);
    return true;
}

void printNodeRecursive(AVLNode* node)
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

void printTree(AVLTree* tree)
{
    printf("\n");
    printNodeRecursive(tree->root);
    printf("\n\n");
}
