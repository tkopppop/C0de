/*
  portress1.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int
main(int argc, char** argv)
{
  uint64_t i;
  uint64_t cnt;
  uint64_t oflag;

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

  for (i = 1; i <= cnt; i++) { /* initial i = 1 */
    if ((i % 2) != 0) {
      printf("###\n");
    } else if((i % 2) == 0) { /* hahahaha ha easy! */
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
