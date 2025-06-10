#include <stdio.h>
void printf_f(float argc);
int main(void)
{
	printf("tab style\n");
	printf("coding tab 2, 3, 4, 5, 6, 7,  8\n");
	printf("2 space or 1tab(4 spae or 8 space)\n");
	printf_f(30.2);
}

void printf_f(float argc)
{
printf("%.01f\n", argc);
}
