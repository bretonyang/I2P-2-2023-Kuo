#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeGen.h"

static int has_variable(BTNode *root) {
    if (root == NULL) return 0;
    if (root->data == ID) return 1;
    return has_variable(root->left) || has_variable(root->right);
}

/// NOTE: don't forget to set the values of children nodes before visiting them!!!
int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;
    int address;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme);
                printf("MOV r%d [%d]\n", root->val, getMemoryPosition(root->lexeme));
                break;
            case INT:
                retval = atoi(root->lexeme);
                printf("MOV r%d %d\n", root->val, retval);
                break;
            case ASSIGN:
                root->right->val = root->val;
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                printf("MOV [%d] r%d\n", getMemoryPosition(root->left->lexeme), root->right->val);
                break;
            case ADDSUB_ASSIGN:
                root->left->val = root->val;
                lv = evaluateTree(root->left);
                root->right->val = root->val + 1;
                rv = evaluateTree(root->right);
                address = getMemoryPosition(root->left->lexeme);
                if (strcmp(root->lexeme, "+=") == 0) {
                    printf("MOV r%d [%d]\n", root->left->val, address);
                    printf("ADD r%d r%d\n", root->left->val, root->right->val);
                    printf("MOV [%d] r%d\n", address, root->left->val);
                    retval = setval(root->left->lexeme, lv + rv);
                } else if (strcmp(root->lexeme, "-=") == 0) {
                    printf("MOV r%d [%d]\n", root->left->val, address);
                    printf("SUB r%d r%d\n", root->left->val, root->right->val);
                    printf("MOV [%d] r%d\n", address, root->left->val);
                    retval = setval(root->left->lexeme, lv - rv);
                }
                break;
            case INCDEC:
                root->right->val = root->val + 1;
                rv = evaluateTree(root->right);
                address = getMemoryPosition(root->right->lexeme);
                if (strcmp(root->lexeme, "++") == 0) {
                    printf("MOV r%d 1\n", root->val);
                    printf("MOV r%d [%d]\n", root->val + 1, address);
                    printf("ADD r%d r%d\n", root->val, root->val + 1);
                    printf("MOV [%d] r%d\n", address, root->val);
                    rv++;
                } else if (strcmp(root->lexeme, "--") == 0) {
                    // Note that our variable is in right, but we want it in left.
                    printf("MOV r%d 1\n", root->val + 1);
                    printf("MOV r%d [%d]\n", root->val, address);
                    printf("SUB r%d r%d\n", root->val, root->val + 1);
                    printf("MOV [%d] r%d\n", address, root->val);
                    rv--;
                }
                retval = setval(root->right->lexeme, rv);
                break;
            case ADDSUB:
            case MULDIV:
            case AND:
            case OR:
            case XOR:
                root->left->val = root->val;
                root->right->val = root->val + 1;
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    printf("ADD r%d r%d\n", root->left->val, root->right->val);
                    retval = lv + rv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    printf("SUB r%d r%d\n", root->left->val, root->right->val);
                    retval = lv - rv;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    printf("MUL r%d r%d\n", root->left->val, root->right->val);
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0) {
                        if (has_variable(root->right)) {
                            printf("DIV r%d r%d\n", root->left->val, root->right->val);
                            retval = 0;
                        } else {
                            error(DIVZERO);
                        }
                    } else {
                        printf("DIV r%d r%d\n", root->left->val, root->right->val);
                        retval = lv / rv;
                    }
                } else if (strcmp(root->lexeme,"&") == 0) {
                    printf("AND r%d r%d\n", root->left->val, root->right->val);
                    retval = lv & rv;
                } else if (strcmp(root->lexeme, "|") == 0) {
                    printf("OR r%d r%d\n", root->left->val, root->right->val);
                    retval = lv | rv;
                } else if (strcmp(root->lexeme, "^") == 0) {
                    printf("XOR r%d r%d\n", root->left->val, root->right->val);
                    retval = lv ^ rv;
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
