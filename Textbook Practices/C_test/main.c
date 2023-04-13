#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int val;
    char name[10];
} Symbol;

Symbol table[20];
char str[20];

int main()
{
//    for (int i = 0; i < 20; i++) {
//        printf("val: %d, name: %s, strlen: %d\n", table[i].val, table[i].name, strlen(table[i].name));
//    }
    printf("str: %s, strlen: %d\n", str, strlen(str));
    strcpy(str, "abcde");
    printf("str: %s, strlen: %d\n", str, strlen(str));
    strcpy(str, "(");
    printf("str: %s, strlen: %d\n", str, strlen(str));

    return 0;
}
