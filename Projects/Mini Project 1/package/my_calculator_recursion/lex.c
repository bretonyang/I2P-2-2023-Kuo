#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"

static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];

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
