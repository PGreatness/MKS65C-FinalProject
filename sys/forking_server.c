#include "networking.h"

void process(char *s);
void subserver(int from_client);
char * print();
char BOARD[6][7];

int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();
  for (int i = 0; i < 6; i++) {
      for (int w = 0; w < 7; w++) {
          BOARD[i][w] = '-';
      }
  }
  printf("%s\n", *BOARD);
  while (1) {

    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0)
      subserver(client_socket);
    else
      close(client_socket);
  }
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  s = print();
  printf("This is thing: %s\n", s);

}

char * print() {
  char * ret = "";
  for (int i = 0; i < 6; i++) {
    char * row = "";
    for (int w =0; w < 7; w++) {
      strcat(row, &BOARD[i][w]);
    }
    strcat(ret, row);
  }
  printf("Ret: %s\n", ret);
  return ret;
}
