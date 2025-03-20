/*
  portress1.c by MM
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>


int
main(int argc, char** argv) 
{

  uint32_t i, cnt, oflag;

  printf("Programming.\n" \
         "_\n\n\n\n\n\n\n");

  /* input number 1~100 (bounds-checking exists) */
  scanf("%u", &cnt);
  
  if (cnt <= 1 || cnt > 100) {
    perror("out checking!");
    exit(EXIT_FAILURE);
  }
  
  --cnt;

  cnt = cnt * 2;

/*
  In a loop, initial i variable set by 1  
  And ### $$$ ### $$ ### <- print all requeted 
  BY user interact. SCANF!
*/

  for (i = 1; i <= cnt; i++) { /* if input is 10={1 .. 18} */
    if ((i % 2) != 0) { 
      printf("###\n");
    } else if ((i % 2) == 0) {
      printf("$$$\n");
      oflag = 1;
    }

    if ((oflag == 1) && (i == cnt)) goto exot;
    else oflag = 0;
  }
 
  goto outro;
 
exot:
  printf("###\n");

outro:
  return 1;

}

/* EoC */
