/*
  select2.c (nested 2 stylying easy easy easy *** hahahaha but you? handsome!? beautiful mind??? pretty too much??? **
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

#include "types.h"


int main(int argc, char** argv)
{

  fd_set            readfds;
  struct timeval    timeout;

  s32 ret;
  s32 iter;

  for (iter = 0; iter < 2; iter++)
  {

    printf("waiting for you to type during 5 seconds...\n");

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeout.tv_sec = 5; 
    timeout.tv_usec = 500;

    ret = select(STDIN_FILENO+1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) { 

      perror("select");
      return 1;

    } else if(ret == 0) {

      printf("timeout! no input occurs.\n");

    } else {
      if (FD_ISSET(STDIN_FILENO, &readfds)) {
        char buffer[128];
       
        read(STDIN_FILENO, buffer, sizeof(buffer));
        printf("input detects: %s\n", buffer);
      }
    }

  }

  return 0;

}
