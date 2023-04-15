#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 256
#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 0

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN, ADDSUB_ASSIGN,
    LPAREN, RPAREN,
    INCDEC,
    AND, OR, XOR
} TokenSet;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val; // current register index
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;


// The symbol table
extern Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
extern void initTable(void);

// Get the memory position for a variable.
extern int getMemoryPosition(const char *str);

// Get the value of a variable
extern int getval(char *str);

// Set the value of a variable
extern int setval(char *str, int val);

// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
extern void freeTree(BTNode *root);

extern BTNode *factor(void);
extern BTNode *unary_expr(void);
extern BTNode *muldiv_expr(void);
extern BTNode *muldiv_expr_tail(BTNode *left);
extern BTNode *addsub_expr(void);
extern BTNode *addsub_expr_tail(BTNode *left);
extern BTNode *and_expr(void);
extern BTNode *and_expr_tail(BTNode *left);
extern BTNode *xor_expr(void);
extern BTNode *xor_expr_tail(BTNode *left);
extern BTNode *or_expr(void);
extern BTNode *or_expr_tail(BTNode *left);
extern BTNode *assign_expr(void);
extern void statement(void);

// Print error message and exit the program
extern void err(ErrorType errorNum);

// Test if a token matches the current token
extern int match(TokenSet token);

// Get the next token
extern void advance(void);

// Get the lexeme of the current token
extern char *getLexeme(void);

// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);

static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];


int sbcount = 0;
Symbol table[TBLSIZE];

/** codeGen.c */

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

/** parser.c */

/* Helper functions */

void initTable(void) {
    // They're by default read in according to our algo
//    printf("MOV r0 [0]\n");
//    printf("MOV r1 [4]\n");
//    printf("MOV r2 [8]\n");
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
    left = or_expr();
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


/** lex.c */

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) { /// INT
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') { /// ADDSUB | INCDEC | ADDSUB_ASSIGN
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == '+' || c == '-') { // consecutive ++ or --
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        } else if (c == '=') { // consecutive += or -=
            lexeme[1] = c;
            lexeme[2] = '\0';
            return ADDSUB_ASSIGN;
        } else { // + or -
            ungetc(c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;
        }
    } else if (c == '*' || c == '/') { /// MULDIV
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '&') { /// AND
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    } else if (c == '|') { /// OR
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
    } else if (c == '^') { /// XOR
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    } else if (c == '\n') { /// END
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') { /// ASSIGN
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') { /// LPAREN
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') { /// RPAREN
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') { /// ID (starts w/ a-z,A-Z,_)
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) || c == '_') && i < MAXLEN) {
            lexeme[i] = c;
            i++;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}

/** main.c */

int main() {
//    freopen("input.txt", "w", stdout);
    initTable();
//    printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}
