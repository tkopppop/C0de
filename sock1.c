#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {
struct sockaddr_in ca, sa, cas[100];
int csockfd, ssockfd, csockfds[100];
char recvbuf[129];
int cas_len;
cas_len = 0;
int i;
pid_t pid1;
int w, wstatus;
int opt;
char str_banner[32];
int datasent;

strcpy(str_banner, "helllo foo bar world!\n");
datasent = strlen(str_banner);
i = 0;
opt = 1;

ca.sin_family = AF_INET;
ca.sin_port = htons(4141);
ca.sin_addr.s_addr = inet_addr("127.0.0.1");
sa.sin_family = AF_INET;
sa.sin_port = htons(4141);
sa.sin_addr.s_addr = INADDR_ANY;

ssockfd = socket(PF_INET, SOCK_STREAM, 0);
setsockopt(ssockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

bind(ssockfd, (struct sockaddr *)&sa, sizeof(sa));
listen(ssockfd, 100);

pid1 = fork();

while(1) {
        if (pid1 == 0) {
                cas_len = sizeof(cas[i]);
                csockfds[i] = accept(ssockfd, (struct sockaddr *)&cas[i], &cas_len);
                if(csockfds[i] == -1)
                        break;
                write(csockfds[i], str_banner, datasent);
                close(csockfds[i]);
                i++;
        } else {
                csockfd = socket(PF_INET, SOCK_STREAM, 0);
                connect(csockfd, (struct sockaddr *)&ca, sizeof(ca));
                read(csockfd, recvbuf, 128);
                printf("%s\n", recvbuf);
                close(csockfd);

                do {
                        w = waitpid(pid1, &wstatus, WUNTRACED | WCONTINUED);
                } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));

                exit(EXIT_SUCCESS);
        }
}

}
