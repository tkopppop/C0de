/*
  portress1.c by MM
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int
main(int argc, char** argv) 
{

  uint64_t i, cnt, oflag;


  printf("Programming.\n" \
         "_\n\n\n\n\n\n\n");

  printf("input: <number 2~100?>???");
  scanf("%lu", &cnt);
  
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
  for (i = 1; i <= cnt; i++) { 
    if ((i % 2) != 0) {
      printf("###\n");
    } else if ((i % 2) == 0) {
      printf("$$$\n");
      oflag = 1;
    }

    if ((oflag == 1) && (i == cnt)) goto end_on;
    else oflag = 0;
  }
 
end_stage1:  
  goto outro1;
 
end_on:
  printf("###\n");

outro1:
  return 1;

}

/* EoC */
