#include <stdio.h>
#include <stdlib.h>


/// NOTE: don't forget to use the intermediate_idx_in_map array in the mapping loop

int main()
{
    char name[200005];
    int len_name, num_designer;

    char orig_alpha_to_new_alpha_map[26];
    int orig_alpha_to_intermediate_idx_in_map[26];

    for (int i = 0; i < 26; i++) {
        orig_alpha_to_new_alpha_map[i] = 'a' + i;
        orig_alpha_to_intermediate_idx_in_map[i] = i;
    }

    scanf("%d%d", &len_name, &num_designer);
    scanf("%s", name);

    // do mapping
    for (int i = 0; i < num_designer; i++) {
        char x, y;
        scanf(" %c %c", &x, &y);

        char tmp = orig_alpha_to_new_alpha_map[orig_alpha_to_intermediate_idx_in_map[x - 'a']];
        orig_alpha_to_new_alpha_map[orig_alpha_to_intermediate_idx_in_map[x - 'a']] = orig_alpha_to_new_alpha_map[orig_alpha_to_intermediate_idx_in_map[y - 'a']];
        orig_alpha_to_new_alpha_map[orig_alpha_to_intermediate_idx_in_map[y - 'a']] = tmp;

        int tmp_idx = orig_alpha_to_intermediate_idx_in_map[x - 'a'];
        orig_alpha_to_intermediate_idx_in_map[x - 'a'] = orig_alpha_to_intermediate_idx_in_map[y - 'a'];
        orig_alpha_to_intermediate_idx_in_map[y - 'a'] = tmp_idx;
    }

    // print result
    for (int i = 0; i < len_name; i++) {
        printf("%c", orig_alpha_to_new_alpha_map[name[i] - 'a']);
    }
    printf("\n");

    return 0;
}

/**

a b c d e f

b a
  c a
d     b

*/
