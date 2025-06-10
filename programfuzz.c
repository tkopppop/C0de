#include <stdio.h>

int main(void) {
char a = (char) 0, b = (char) 0;
int flag = 1;
printf("fuzzer 1.0\n");
for (a = (char) 0; a <= 'Z'; a++)
{
	if (flag == 1) {
		printf("%c %c ", a, b);
		printf("%c %c ", b, a);
		flag = 0;
		continue;
	}
	
	if (flag == 0) {
		for (b = (char) 0; b < 'z'; b++)
		{
			printf("%c %c ", a, b);
			printf("%c %c ", b, a);
		}
		flag = 1;
		
	}
}
}

