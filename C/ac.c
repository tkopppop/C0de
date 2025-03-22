/*
  FILENAME: loc62_fractal2_portres2.c
  (EnterKey pressing checks system)
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/select.h>

int 
check_out_command(void)
{ 

    int32_t ret1;

    fd_set readfds; 

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    ret1 = select(STDIN_FILENO+1, &readfds, NULL, NULL, &timeout);
    if (ret1 > 0) {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            printf("exit. press enter key!\n");
            exit(-1);
        }
    }

}

int 
main(int argc, char** argv)
{

    printf("game korea\n");

    for (int i = 0; i < 32; ++i) {
        printf("k\n");
        check_out_command();
        printf("o\n");
        check_out_command();
        printf("r\n");
        check_out_command();
        printf("e\n"); 
        check_out_command();
        printf("a\n");
        check_out_command();
    }
    
    return(3); 
 
}

/* EOC */
/* EOF */
