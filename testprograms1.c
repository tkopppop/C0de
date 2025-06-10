#include <stdio.h>
char global_a;
char global_b;

int super(){
	global_a = (char) 1;
	global_b = 'A';
}
void init(){
	super();
}
void super1()
{
	printf("-super1\n");
}

int main(void ) {
	init();
	super1();
	printf("%x %c\n", global_a, global_b);
}
