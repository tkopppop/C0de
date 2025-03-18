/*
  webserver_select_study.C [ai c -> c -> C -> copycat -> flaming -> noname_web_server.select.c
  author: programmer KJ
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
#include "debug.h"

#define PORT            8080
#define BUF_SIZE        1024
#define MAX_CLIENTS     10


static void handle_client(int client_sock)
{
    
  const char* res = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: 60\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "<html><body>Hello web server using select api.</body></html>";
  char buf[BUF_SIZE];

  s32 bytes_read;

  bytes_read = read(client_sock, buf, sizeof(buf) - 1);
  if (bytes_read <= 0) {
    close(client_sock);
    return;
  }
  
  buf[bytes_read] = '\0';
  
  printf("received request: \n%s\n", buf);
    
  write(client_sock, res, strlen(res));
  close(client_sock);

}


static int init_server(int* server_sock, struct sockaddr_in* server_addr)
{

  *server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (*server_sock == -1) PFATAL("socket create failed"); 

  server_addr->sin_family = AF_INET;
  server_addr->sin_addr.s_addr = INADDR_ANY;
  server_addr->sin_port = htons(PORT);

  if (bind(*server_sock, (struct sockaddr*)server_addr, sizeof(*server_addr)) == -1) {
    close(*server_sock);
    PFATAL("socket binding failed");
  }

  if (listen(*server_sock, MAX_CLIENTS) == -1) {
    close(*server_sock);
    PFATAL("socket listen failed"); 
  }

  return 0;

}


int main(int argc, char** argv)
{

  s32 max_fd;
  s32 fd;
  s32 server_sock;
  s32 client_sock;
  
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  
  socklen_t addr_len;
  
  fd_set read_fds;
  fd_set master_fds;

  if (init_server(&server_sock, &server_addr) == -1) PFATAL("server creation failed");

  FD_ZERO(&master_fds);
  FD_SET(server_sock, &master_fds);
  max_fd = server_sock;

  printf("listen server port:%d\n", PORT);

  while (1) {

    read_fds = master_fds;

    if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) PFATAL("select");

    for (fd = 0; fd <= max_fd; fd++) {
        if (FD_ISSET(fd, &read_fds)) {
            if (fd == server_sock) {
                client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);
                if (client_sock == -1) {
                    perror("b-a-d-a-c-t-i-n-g: client socket accept failed");
                    continue;
                }
                FD_SET(client_sock, &master_fds);
                if (client_sock > max_fd) max_fd = client_sock;
                printf("new connection: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            } else {
            handle_client(fd);
            FD_CLR(fd, &master_fds);
            }
        }
    }

  }

  close(server_sock);

  return 0;

}

/*
  // ] EOC
*/
