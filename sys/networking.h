#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#ifndef NETWORKING_H
#define NETWORKING_H

#define BUFFER_SIZE 50
#define PORT "9001"
#define TEST_IP "127.0.0.1"
#define ROWS 6
#define COLS 7

void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server);
int doX(char **board);
int doO(char **board);
void print(char  *board[ROWS]);
int checkHorizontal(char *board[ROWS]);
int checkVertical(char *board[ROWS]);
int checkDiagonalR(char *board[ROWS]);
int checkDiagonalL(char *board[ROWS]);
int connected(char *board[ROWS]);



#endif
