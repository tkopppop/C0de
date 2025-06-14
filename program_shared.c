/*
  // program_so.c
*/
#include <stdio.h>

int add(int a, int b, int c) {
    return a+b+c;
}

/*
  // program_shared.c 
*/
#include <stdio.h>

int add(int a, int b, int c);

int main(void) {

add(10, 20, 30);
printf("so is shared object\n");

}
/*
gcc -fPIC -c program_so.c
gcc -shared -o program_so.so program_so.o
gcc program_shared.c -L. -lprogram_so -o program_shared
  
export LD_LIBRARY_PATH=.
./program_shared
*/
