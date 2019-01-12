// #include "networking.h"

// void process(char *s);
// void subserver(int from_client);
// char * print();
// char * BOARD[7];

// int main() {

//   int listen_socket;
//   int f;
//   listen_socket = server_setup();

//   printf("%s\n", *BOARD);
//   while (1) {

//     int client_socket = server_connect(listen_socket);
//     f = fork();
//     if (f == 0)
//       subserver(client_socket);
//     else
//       close(client_socket);
//   }
// }

// void subserver(int client_socket) {
//   char buffer[BUFFER_SIZE];

//   while (read(client_socket, buffer, sizeof(buffer))) {

//     printf("[subserver %d] received: [%s]\n", getpid(), buffer);
//     process(buffer);
//     write(client_socket, buffer, sizeof(buffer));
//   }//end read loop
//   close(client_socket);
//   exit(0);
// }

// void process(char * s) {
//   s = print();
//   printf("This is thing: %s\n", s);

// }

// char * print() {
//   char * ret = "";
//   for (int i = 0; i < 6; i++) {
//     char * row = "";
//     for (int w =0; w < 7; w++) {
//       strcat(row, &BOARD[i][w]);
//     }
//     strcat(ret, row);
//   }
//   printf("Ret: %s\n", ret);
//   return ret;
// }

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

  char * BOARD[6];
  void fill() {
    for (int i = 0; i < 6; i++) {
      char w[] = "hello";
      BOARD[i] = w;
    }
    printf("%s\n", BOARD[1]);
  }
  // char *print() {
  //   char ret[36];
  //   for (int i = 0; i < 6; i++) {
  //     char * row = "";
  //     for (int w =0; w < 7; w++) {
  //       if (row == "") {
  //         printf("sizeof(BOARD[i]): %ld\n", sizeof(BOARD[i]));
  //         char tmp[sizeof(BOARD[i])];
  //         row = tmp;
  //       }else{
  //         printf("row: %s board: %s\n", row, BOARD[i]);
  //         char * tmp = BOARD[i];
  //         strcat(row, tmp);
  //       }
  //     }
  //     strcat(ret, row);
  //   }
  //   printf("Ret: %s\n", ret);
  //   char * retStr = malloc(sizeof(char) * 36);
  //   retStr = ret;
  //   return retStr;
  // }

  char * print() {
    char str[6  * 5];
    int location = 0;
    for (int i =0; i < 6; i++) {
      for (int w = 0; w < 5; w++) {
        char tmp = malloc(sizeof(BOARD[i][w]));
        strcpy(tmp, BOARD[i][w]);
        str[location] = tmp;
        free(&tmp);
      }
    }
    return str;
  }

int main() {
  fill();
  char * thing = print();
  printf("This is thing: %s\n", thing);
  return 0;
}

