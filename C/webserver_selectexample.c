/*
  C0D3 take+ADN+align+sign: author: tf8 ###x90cx90c1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

#include "types.h"


#define PORT            8080
#define BUF_SIZE        1024
#define MAX_CLIENT      10


void handle_client(int csock)
{
    
  const char* res = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: 56\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "<html><body>Hello web server using select api.</body></html>";
  char buf[BUF_SIZE];

  s32 bytes_read;


  bytes_read = read(csock, buf, sizeof(buf) - 1);
  if (bytes_read <= 0) {
    close(csock);
    return;
  }
  
  buf[bytes_read] = '\0';
  
  printf("received request: \n%s\n", buf);
    
  write(csock, res, strlen(res));
  close(csock);

}


int init_server(int* ssock, struct sockaddr_in* saddr)
{

  *ssock = socket(AF_INET, SOCK_STREAM, 0);
  if (*ssock == -1) {
    perror("socket");
    return -1;
  }

  saddr->sin_family = AF_INET;
  saddr->sin_addr.s_addr = INADDR_ANY;
  saddr->sin_port = htons(PORT);

  if (bind(*ssock, (struct sockaddr*)saddr, sizeof(*saddr)) == -1) {
    perror("bind");
    close(*ssock);
    return -1;
  }

  if (listen(*ssock, MAX_CLIENT) == -1) {
    perror("listen");
    close(*ssock);
    return -1;
  }

  return 0;

}


int main(int argc, char** argv)
{

  s32 max_fd;
  s32 fd;
  s32 ssock;
  s32 csock;

  struct sockaddr_in saddr;
  struct sockaddr_in caddr;

  socklen_t addr_len;

  fd_set read_fds;
  fd_set master_fds;

 
  if (init_server(&ssock, &saddr) == -1) {
    exit(EXIT_FAILURE);
  }

  FD_ZERO(&master_fds);
  FD_SET(ssock, &master_fds);
  max_fd = ssock;

  printf("listen server port:%d\n", PORT);

  while (1) {

    read_fds = master_fds;

    if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select");
      exit(EXIT_FAILURE);
    }

    for (fd = 0; fd <= max_fd; fd++) {

      if (FD_ISSET(fd, &read_fds)) {
        if (fd == ssock) {
          csock = accept(ssock, (struct sockaddr*)&caddr, &addr_len);
          if (csock == -1) {
            perror("accept");
            continue;
          }
          FD_SET(csock, &master_fds);
          if (csock > max_fd) max_fd = csock;
          printf("new connection: %s:%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
        } else {
          handle_client(fd);
          FD_CLR(fd, &master_fds);
        }
      }

    }

  }

  close(ssock);

  return 0;

}
