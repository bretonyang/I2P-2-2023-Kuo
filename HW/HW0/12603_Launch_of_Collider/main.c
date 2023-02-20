#include <stdio.h>
#include <stdlib.h>

/// BUG: There is a potential bug where answer RL might not be next to
/// each other!!!

/// See OJ practice for correct version.

int main()
{
    int num_particles; // 200,000
    char* direc_arr; // 200,000
    int* coor_arr; // 200,000

    scanf("%d", &num_particles);
    direc_arr = (char*)malloc(sizeof(char) * num_particles);
    coor_arr = (int*)malloc(sizeof(int) * num_particles);

    for (int i = 0; i < num_particles; i++) {
        scanf(" %c", direc_arr + i);
    }
    for (int i = 0; i < num_particles; i++) {
        scanf("%d", coor_arr + i);
    }

    // SOLVE
    int ans_R = -1;
    int ans_L = -1;
    int min_dist;
    for (int i = 0; i < num_particles - 1; i++) {
        if (direc_arr[i] == 'R' && direc_arr[i + 1] == 'L') {
            // bingo
            if (ans_R == -1 || coor_arr[i + 1] - coor_arr[i] < min_dist) {
                ans_R = coor_arr[i];
                ans_L = coor_arr[i + 1];
                min_dist = ans_L - ans_R;
            }

            // update faster
            i++;
        }
    }

    if (ans_R == -1) {
        printf("-1\n");
    }
    else {
        printf("%d\n", min_dist / 2);
    }

    free(direc_arr);
    free(coor_arr);

    return 0;
}


/**

 1. All points along a straight line.
 2. no 2 or more particles at same point.
 3. X_i is:
    -> even
    -> coordinate of the i-th particle
    -> i-th particle's position in the collider

 ideas:

 1. only collides if: RL
 2. RL will be next to each other (since sorted)


 steps:
 1. search for the smallest RL pair integers




*/
