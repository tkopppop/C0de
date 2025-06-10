#include <stdio.h>
#include <stdlib.h>

int funcplusminus(int a1, int b2, int c3)
{
	return ((a1+b2)-c3);
}
int main(void) {
int a, b, c;
int retval1;
a = 1020;
b = 1020;
c = 1000;
retval1 = -1;

/*a + b - c;*/
retval1 = funcplusminus(a, b, c);
if (retval1 != -1) {
	printf("%d+%d-%d = %d\n", a, b, c, retval1);
}
}


