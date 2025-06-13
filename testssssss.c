#include <stdio.h>
int formatstringbug_bug2()
{
char buf[32]; /* bufferoverflow */
scanf("%s", &buf);
printf(buf); /* formatstringbugfsb. */
}
int main(void){
printf("hackit!\n");
formatstringbug_bug2();
}
