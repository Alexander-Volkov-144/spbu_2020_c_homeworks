#include "../library/avl/avl.h"
#include <stdio.h>

int main()
{
    AVLTree* tree = createTree();
    int x = 0;
    do {
        scanf("%d", &x);
        if (x != 0)
            addValue(tree, x);
    } while (x != 0);
    printAllElementsInAscendingOrder(tree);
    removeTree(tree);
}

