#include "function.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, pivot;
    while (~scanf("%d%d", &n, &pivot))
    {
        node *head = malloc(sizeof(node)), *cur = head;
        while (n--)
        {
            scanf("%d", &(cur->val));
            if (n)
                cur = cur->next = malloc(sizeof(node));
            else
                cur->next = NULL;
        }
        head = partition_linked_list(head, pivot);
        for (cur = head; cur; cur = cur->next)
            printf("%d%c", cur->val, " \n"[!cur->next]);
        while (head)
        {
            node *tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    return 0;
}
