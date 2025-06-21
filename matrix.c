#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mangle_check() {
        int a = rand()%3;

        if (a == 0) {
                printf("%%");
        } else if (a == 1) {
                printf("-");
        } else {
                printf("+");
        }

}

int main() {
int i;
clock_t start = clock();

        srand(time(NULL));

        while (((double)(clock() - start) / CLOCKS_PER_SEC) < 5.0)
                {
                if ((i++ % 25) == 0) {
                        printf("\n");
                }

                for (int a = 0; a < 3; a++) {
                        mangle_check();
                }

                if(i > 5000) {
                        printf("\033[H");
                        i = 0;
                }
        }
}
