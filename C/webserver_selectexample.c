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
#define MAX_CLIENTS     10


void handle_client(int c_sock)
{
    
  const char* res = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: 56\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "<html><body>Hello web server using select api.</body></html>";
  char buffer[BUF_SIZE];

  s32 bytes_read;


  bytes_read = read(c_sock, buffer, sizeof(buffer) - 1);
  if (bytes_read <= 0) {
    close(c_sock);
    return;
  }
  
  buffer[bytes_read] = '\0';
  
  printf("received request: \n%s\n", buffer);
    
  write(c_sock, res, strlen(res));
  close(c_sock);

}


int init_server(int* s_sock, struct sockaddr_in* s_addr)
{

  *s_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (*s_sock == -1) {
    perror("socket");
    return -1;
  }

  s_addr->sin_family = AF_INET;
  s_addr->sin_addr.s_addr = INADDR_ANY;
  s_addr->sin_port = htons(PORT);

  if (bind(*s_sock, (struct sockaddr*)s_addr, sizeof(*s_addr)) == -1) {
    perror("bind");
    close(*s_sock);
    return -1;
  }

  if (listen(*s_sock, MAX_CLIENTS) == -1) {
    perror("listen");
    close(*s_sock);
    return -1;
  }

  return 0;

}


int main(int argc, char** argv)
{

  s32 max_fd;
  s32 fd;
  s32 s_sock;
  s32 c_sock;

  struct sockaddr_in s_addr;
  struct sockaddr_in c_addr;

  socklen_t addr_len;

  fd_set read_fds;
  fd_set master_fds;

 
  if (init_server(&s_sock, &s_addr) == -1) {
    exit(EXIT_FAILURE);
  }

  FD_ZERO(&master_fds);
  FD_SET(s_sock, &master_fds);
  max_fd = s_sock;

  printf("listen server port:%d\n", PORT);

  while (1) {

    read_fds = master_fds;

    if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select");
      exit(EXIT_FAILURE);
    }

    for (fd = 0; fd <= max_fd; fd++) {

      if (FD_ISSET(fd, &read_fds)) {
        if (fd == s_sock) {
          c_sock = accept(s_sock, (struct sockaddr*)&c_addr, &addr_len);
          if (c_sock == -1) {
            perror("accept");
            continue;
          }
          FD_SET(c_sock, &master_fds);
          if (c_sock > max_fd) max_fd = c_sock;
          printf("new connection: %s:%d\n", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port));
        } else {
          handle_client(fd);
          FD_CLR(fd, &master_fds);
        }
      }

    }

  }

  close(s_sock);

  return 0;

}
