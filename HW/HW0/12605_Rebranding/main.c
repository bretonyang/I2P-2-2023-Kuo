#include <stdio.h>
#include <stdlib.h>


int len_orig_name, num_designer;
char orig_name[200005];

int index_of_char[26];
char map[27];


int main()
{
    // setup
    for (int i = 0; i < 26; i++) {
        index_of_char[i] = i;
        map[i] = 'a' + i;
    }
    map[26] = '\0';

    scanf("%d%d", &len_orig_name, &num_designer);
    scanf("%s", orig_name);

    char x, y;
    for (int m = 0; m < num_designer; m++) {
        scanf(" %c %c", &x, &y);
        char tmp = map[index_of_char[x - 'a']];
        int idx_tmp = index_of_char[x - 'a'];
        map[index_of_char[x - 'a']] = map[index_of_char[y - 'a']];
        map[index_of_char[y - 'a']] = tmp;
        index_of_char[x - 'a'] = index_of_char[y - 'a'];
        index_of_char[y - 'a'] = idx_tmp;
    }

//    printf("index of char: ");
//    for (int i = 0; i < 26; i++) {
//        printf("%d ", index_of_char[i]);
//    }
//    printf("\nmap: %s\n", map);

    for (int i = 0; i < len_orig_name; i++) {
        orig_name[i] = map[orig_name[i] - 'a'];
    }

    printf("%s\n", orig_name);

    return 0;
}


/**

a b c d e f g h i j k

b a
c   b
  d   a
        g   e
      f   a
    b
________________________
c d b f g a e

abacabadaba
cdcbcdcfcdc


*/
