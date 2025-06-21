#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH   50
#define HEIGHT  50

int main() {
char arr[] = "%++--";
time_t start_time;
int i, j;
char c;

        srand(time(NULL));
        start_time = time(NULL);

        while (difftime(time(NULL), start_time) < 5) {
                system("clear");
                for (i = 0; i < HEIGHT; i++) {
                    for (j = 0; j < WIDTH; j++) {
                        c = arr[rand() % 5];
                        printf("\033[1;37m%c\033[0m", c);
                    }
                 printf("\n");
                }
                usleep(100000); /* 100000(0.1 sec) */
        }

    return 0;
}
