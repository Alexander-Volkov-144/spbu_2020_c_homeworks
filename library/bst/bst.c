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

enum Direction {
    left,
    right,
    none
};

BinarySearchTree* createTree()
{
    BinarySearchTree* newTree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    newTree->root = NULL;
    return newTree;
}

void removeNodeRecursive(BinaryTreeNode* node)
{
    if (NULL == node->leftChild && NULL == node->rightChild) {
        free(node);
        return;
    }
    if (NULL != node->leftChild && NULL == node->rightChild) {
        removeNodeRecursive(node->leftChild);
        free(node);
        return;
    }
    if (NULL == node->leftChild && NULL != node->rightChild) {
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
    if (NULL != tree->root)
        removeNodeRecursive(tree->root);
    free(tree);
}

bool existsRecursive(BinaryTreeNode* node, int value)
{
    if (value == node->value) {
        return true;
    }
    if (value < node->value && NULL != node->leftChild) {
        return existsRecursive(node->leftChild, value);
    }
    if (value > node->value && NULL != node->rightChild) {
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
        if (NULL == node->leftChild) {
            node->leftChild = createNode(value);
            return true;
        } else {
            return addValueRecursive(node->leftChild, value);
        }
    }
    if (value > node->value) {
        if (NULL == node->rightChild) {
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
    return NULL == node->leftChild && NULL == node->rightChild;
}

bool changeParent(BinarySearchTree* tree, BinaryTreeNode* newNode, BinaryTreeNode* parent, enum Direction direction)
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

BinaryTreeNode* findMinimum(BinaryTreeNode* node, BinaryTreeNode** parent)
{
    if (NULL == node->leftChild) {
        return node;
    }
    *parent = node;
    BinaryTreeNode* currentTreeNode = node->leftChild;
    while (NULL != currentTreeNode->leftChild) {
        *parent = currentTreeNode;
        currentTreeNode = currentTreeNode->leftChild;
    }
    return currentTreeNode;
}

bool removeRecursive(BinarySearchTree* tree, BinaryTreeNode* node, int value, BinaryTreeNode* parent, enum Direction direction)
{
    if (node->value == value) {
        if (isLeaf(node)) {
            free(node);
            changeParent(tree, NULL, parent, direction);
            return true;
        }
        if (NULL == node->leftChild && NULL != node->rightChild) {
            changeParent(tree, node->rightChild, parent, direction);
            free(node);
            return true;
        }
        if (NULL == node->rightChild && NULL != node->leftChild) {
            changeParent(tree, node->leftChild, parent, direction);
            free(node);
            return true;
        }
        BinaryTreeNode* temporaryParent = NULL;
        BinaryTreeNode* nodeWithMinimumValue = findMinimum(node->rightChild, &temporaryParent);
        node->value = nodeWithMinimumValue->value;
        if (nodeWithMinimumValue == node->rightChild) {
            if (NULL != nodeWithMinimumValue->rightChild)
                changeParent(tree, nodeWithMinimumValue->rightChild, node, right);
            else
                changeParent(tree, NULL, node, right);
        } else {
            if (NULL != nodeWithMinimumValue->rightChild)
                changeParent(tree, nodeWithMinimumValue->rightChild, temporaryParent, left);
            else
                changeParent(tree, NULL, temporaryParent, left);
        }
        free(nodeWithMinimumValue);
        return true;
    }
    if (node->value > value && NULL != node->leftChild) {
        return removeRecursive(tree, node->leftChild, value, node, left);
    }
    if (node->value < value && NULL != node->rightChild) {
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
    if (NULL == node) {
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
