#include <stdio.h>
#include <stdlib.h>
#include "function.h"


BTNode* EXPR() {
    BTNode *node = NULL, *right_node = NULL;
    if (pos >= 0) {
        right_node = FACTOR();

        if (pos > 0) {
            char c = expr[pos];

            if (c == '|' || c == '&') { /// EXPR = EXPR OP FACTOR
                node = makeNode(c);
                node->right = right_node;
                pos--; // only change position in this case
                node->left = EXPR();
            }
            else { /// EXPR = FACTOR, e.g. A|(B&C) when parsing B
                node = right_node;
            }
        }
        else { /// EXPR = FACTOR, e.g. (A&B)
            node = right_node;
        }
    }
    return node;
}


BTNode* FACTOR() {
    BTNode* node = NULL;

    if (pos >= 0) {
        char c = expr[pos--];

        if (c >= 'A' && c <= 'D') { /// FACTOR = ID
            node = makeNode(c);
        }
        else if (c == ')') { /// FACTOR = (EXPR)
            node = EXPR();

            // not required in this pset, but included just for ref
            if (expr[pos--] != '(') {
                printf("WTF");
                freeTree(node);
                node = NULL;
            }
        }
    }

    return node;
}


BTNode* makeNode(char c) {
    BTNode* new_node = malloc(sizeof(BTNode));
    for (int i = 0; i < NUMSYM; i++) {
        if (sym[i] == c) {
            new_node->data = i;
        }
    }
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

