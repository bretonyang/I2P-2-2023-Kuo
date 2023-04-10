#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _BTNode {
    char token;
    struct _BTNode *left, *right;
} BTNode;

char expr[300];
int pos;

BTNode* fa();
BTNode* ex();

BTNode* ex() { /// expression
    /// EXPR = FACTOR | EXPR OP FACTOR
    BTNode* root = NULL;
    BTNode* right = NULL;
    if (pos >= 0) {
        right = fa();
        if (pos >= 0) {
            char c = expr[pos];
            if (c == '&' || c == '|') {
                pos--;
                root = malloc(sizeof(BTNode));
                root->token = c;
                root->right = right;
                root->left = ex();
            }
            else { // e.g. A|(B&C), when parsing B and encounter (
                root = right;
            }
        }
        else { // e.g. (A|B), when parsing (A|B)
            root = right;
        }
    }
    return root;
}

BTNode* fa() { /// factor
    BTNode* root = NULL;
    if (pos >= 0) {
        char c = expr[pos--];
        if (c >= 'A' && c <= 'D') {
            root = malloc(sizeof(BTNode));
            root->token = c;
            root->left = NULL;
            root->right = NULL;
        }
        else if (c == ')') {
            root = ex();
            if (expr[pos--] != '(') {
                printf("wtf\n");
            }
        }
    }
    return root;
}

void print_infix(BTNode* root) {
    if (root == NULL) {
        return;
    }
    else if (root->token >= 'A' && root->token <= 'D') {
        printf("%c", root->token);
        return;
    }

    print_infix(root->left);
    printf("%c", root->token);
    if (root->right->token == '&' || root->right->token == '|') {
        printf("(");
        print_infix(root->right);
        printf(")");
    }
    else {
        print_infix(root->right);
    }
}

int main()
{
    scanf("%s", expr);
    pos = strlen(expr) - 1;
    BTNode* root = ex();
    print_infix(root);

    return 0;
}
