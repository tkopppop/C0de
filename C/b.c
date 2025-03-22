/*
  FILENAME: loc60_koreaprint_interrupt_timer5
  KJ_timeout_error_koreaprints.C
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/select.h>

int 
check_out_commands(void)
{ 
  
    int32_t ret1;

    fd_set readfd; 

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    FD_ZERO(&readfd);
    FD_SET(STDIN_FILENO, &readfd);
    
    ret1 = select(STDIN_FILENO+1, &readfd, NULL, NULL, &timeout);
    if (ret1 > 0) {
        if (FD_ISSET(STDIN_FILENO, &readfd)) {
            printf("exit. press enter key!\n");
            exit(-1);
        }
    }

    sleep(1);
  
}

int 
main(int argc, char** argv)
{

    printf("game korea\n"); 

    for (int i = 0; i < 32; ++i) {
        printf("k\n");
        check_out_commands();
        printf("o\n");
        check_out_commands();
        printf("r\n");
        check_out_commands();
        printf("e\n"); 
        check_out_commands();
        printf("a\n");
        check_out_commands();
    }
    
    return(3); 
 
}

/* EOC */
/* EOF */
