#define _GNU_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
struct dirent **namelist;
int n, i;
i = 0;

/* alphasort, versionsort(GNU extension) */
n = scandir(argv[1], &namelist, NULL, alphasort);

while (i != n) {
        printf("%s\n", namelist[i]->d_name);
        free(namelist[i]);
        i++;
}
free(namelist);
}
