#include <stdlib.h>
#include <stdio.h>
#ifdef TURBOC_2_01
#include <conio.h>
#elseif LINUX
#include <unistd.h>
#endif

int main2();
int main3();
int main4();
int main5();

int main(){
main2();
main3();
main4();
main5();
}
int main2() { }
int main3() { }
int main4() { }
int main5() { }

// EOC EOF EOT
