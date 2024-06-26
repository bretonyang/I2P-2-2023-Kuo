#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "codeGen.h"

int sbcount = 0;
Symbol table[TBLSIZE];

/* Helper functions */

void initTable(void) {
    printf("MOV r0 [0]\n");
    printf("MOV r1 [4]\n");
    printf("MOV r2 [8]\n");
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getMemoryPosition(const char *str) {
    for (int i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return 4 * i;

    error(NOTFOUND);
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    error(NOTFOUND);
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

/* Parsing functions */

/** factor := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN */
BTNode *factor(void) {
    BTNode *node = NULL;

    if (match(INT)) { // factor := INT
        node = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) { // factor := ID
        node = makeNode(ID, getLexeme());
        advance();
    } else if (match(INCDEC)) { // factor := INCDEC ID
        node = makeNode(INCDEC, getLexeme());
        advance();
        node->left = NULL;
        if (match(ID)) {
            node->right = makeNode(ID, getLexeme());
            advance();
        } else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) { // factor := LPAREN assign_expr RPAREN
        advance();
        node = assign_expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else {
        error(NOTNUMID);
    }
    return node;
}

/** unary_expr := ADDSUB unary_expr | factor */
BTNode *unary_expr(void) {
    BTNode *node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = makeNode(INT, "0");
        node->right = unary_expr();
    } else {
        node = factor();
    }
    return node;
}

/** muldiv_expr := unary_expr muldiv_expr_tail */
BTNode *muldiv_expr(void) {
    BTNode *node = unary_expr();
    return muldiv_expr_tail(node);
}

/** muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL */
BTNode *muldiv_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    } else {
        return left;
    }
}

/** addsub_expr := muldiv_expr addsub_expr_tail */
BTNode *addsub_expr(void) {
    BTNode *node = muldiv_expr();
    return addsub_expr_tail(node);
}

/** addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL */
BTNode *addsub_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    } else {
        return left;
    }
}

/** and_expr := addsub_expr and_expr_tail */
BTNode *and_expr(void) {
    BTNode *node = addsub_expr();
    return and_expr_tail(node);
}

/** and_expr_tail := AND addsub_expr and_expr_tail | NiL */
BTNode *and_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(AND)) {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    } else {
        return left;
    }
}

/** xor_expr := and_expr xor_expr_tail */
BTNode *xor_expr(void) {
    BTNode *node = and_expr();
    return xor_expr_tail(node);
}

/** xor_expr_tail := XOR and_expr xor_expr_tail | NiL */
BTNode *xor_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(XOR)) {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    } else {
        return left;
    }
}

/** or_expr := xor_expr or_expr_tail */
BTNode *or_expr(void) {
    BTNode *node = xor_expr();
    return or_expr_tail(node);
}

/** or_expr_tail := OR xor_expr or_expr_tail | NiL */
BTNode *or_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(OR)) {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    } else {
        return left;
    }
}

/** assign_expr := ID ASSIGN assign_expr | ID ADDSUB_ASSIGN assign_expr | or_expr */
BTNode *assign_expr(void) {
    BTNode *node = NULL, *left = NULL;
    left = or_expr(); // If it's an assignment, this is only ID node, else or_expr node
    if (left->data == ID && match(ASSIGN)) { // assign_expr := ID ASSIGN assign_expr
        node = makeNode(ASSIGN, getLexeme());
        advance();
        node->left = left;
        node->right = assign_expr();
    } else if (left->data == ID && match(ADDSUB_ASSIGN)) { // assign_expr := ID ADDSUB_ASSIGN assign_expr
        node = makeNode(ADDSUB_ASSIGN, getLexeme());
        advance();
        node->left = left;
        node->right = assign_expr();
    } else { // assign_expr := or_expr
        node = left;
    }
    return node;
}

/** statement := ENDFILE | END | assign_expr END */
void statement(void) {
    BTNode *node = NULL;

    if (match(ENDFILE)) { // statement := ENDFILE
        printf("MOV r0 [0]\n");
        printf("MOV r1 [4]\n");
        printf("MOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) { // statement := END
//        printf(">> ");
        advance();
    } else { // statement := assign_expr END
        node = assign_expr();
        if (match(END)) {
//            printf("%d\n", evaluateTree(node));
//            printf("Prefix traversal: ");
//            printPrefix(node);
//            printf("\n");
            evaluateTree(node);
            freeTree(node);

//            printf(">> ");
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}
