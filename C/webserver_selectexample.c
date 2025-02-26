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
#define BUFFER_SIZE     1024
#define MAX_CLIENTS     10


void handle_client(int client_sock) {
    
  const char* response = "HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/html\r\n"
                         "Content-Length: 56\r\n"
                         "Connection: close\r\n"
                         "\r\n"
                         "<html><body><h1>Hello web server using select api.</h1></body></html>";
  char buffer[BUFFER_SIZE];

  s32 bytes_read;


  bytes_read = read(client_sock, buffer, sizeof(buffer) - 1);
  if (bytes_read <= 0) {
    close(client_sock);
    return;
  }
  
  buffer[bytes_read] = '\0';
  
  printf("received request: \n%s\n", buffer);
    
  write(client_sock, response, strlen(response));
  close(client_sock);

}


int main(int argc, char** argv) {
  s32 server_sock;
  s32 client_sock;
  s32 max_fd;
  s32 fd;
 
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_len;
  fd_set read_fds;
  fd_set master_fds;

  
  addr_len = sizeof(client_addr);

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    perror("bind");
    close(server_sock);
    exit(EXIT_FAILURE);
  }

  if (listen(server_sock, MAX_CLIENTS) == -1) {
    perror("listen");
    close(server_sock);
    exit(EXIT_FAILURE);
  }

  FD_ZERO(&master_fds);
  FD_SET(server_sock, &master_fds);
  max_fd = server_sock;

  printf("listen server port:%d\n", PORT);

  while (1) {

    read_fds = master_fds;

    if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select");
      exit(EXIT_FAILURE);
    }

    for (fd = 0; fd <= max_fd; fd++) {

      if (FD_ISSET(fd, &read_fds)) {
        if (fd == server_sock) {
          client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);
          if (client_sock == -1) {
            perror("accept");
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
