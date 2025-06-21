#include <stdio.h>
#include <stdlib.h>

int mangle_check() {
        int a = rand() % 3;

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

        srand(time(NULL));

        for (i = 0; i < 30000; i++) {
                if ((i % 25) == 0) {
                        printf("\n");
                }

                for (int a = 0; a < 3; a++) {
                        mangle_check();
                        usleep(120);
                }

                if((i % 2000) == 0)
                        printf("\033[H");
        }
}
