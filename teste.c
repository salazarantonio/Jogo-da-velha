#include <stdio.h>

int i = 0, j = 0;

int main(void) {
    printf("   Col 0   Col 1   Col 2\n");
    printf("         |       |       \n");
 
    int i;
    for (i = 0; i < 3; i++) {
 
        if (i < 2)
            printf("   ------|-------|------\n");
    }

    return 0;
}