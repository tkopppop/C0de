#include <stdio.h>
#include <stdlib.h>

int main(void) {
int a = 30;
int b, c = a; b = c; a = b + c;
printf("%d %d %d\n", a, b, c);
}
