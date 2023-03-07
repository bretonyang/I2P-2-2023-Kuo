typedef struct _node
{
    int val;
    struct _node *next;
} node;

node *partition_linked_list(node *, int);

// Implement the above function in a `.c` file
// For more details, please refer to https://hackmd.io/@nevikw39/partial-judge
// You might start with the following codes:

/**
#include "function.h"

node *partition_linked_list(node *head, int pivot)
{
    // ...
}
*/
