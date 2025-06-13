#include <stdio.h>
#include <stdlib.h>
void main(void) {
    printf("prologin = v \n\n\n\n\n\n");
}

#include <stdio.h>
#include <stdlib.h>

/* no override, overload(you develop oop some if you wanted to construction of overloading feature of C by C)*/

/****
void main(void){
_init();
}
****/

#define IF_DEF    "#ifdef"
#define END_IFDEF "#endif"

IF_DEF _A_ 
void main(void){ }
END_IFDEF

IF_DEF _B_
int main(int argc, char *argv[]){ }
END_IFDEF

