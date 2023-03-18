#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void printInfix(Node *root) {
    if (root == NULL) {
        return;
    }

    printInfix(root->left);
    printf("%c", root->data);

    /// Print parentheses if right child of an OP is an EXPR
    /// Why: this is the case EXPR = EXPR OP FACTOR, where FACTOR = (EXPR)
    if (root->right != NULL && (root->right->data == '|' || root->right->data == '&')) {
        printf("(");
        printInfix(root->right);
        printf(")");
    }
    else {
        printInfix(root->right);
    }
}
