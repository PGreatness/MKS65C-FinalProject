#include <string.h>
#include <stdlib.h>
#include <stdio.h>

  char * BOARD[6];
  
  struct test
  {
    char * row_0;
    char * row_1;
    char * row_2;
    char * row_3;
    char * row_4;
    char * row_5;
  } Board;
  
  char ** fill(char * b[6]) {
    char *board[6];
    for (int i = 0; i < 6; i++) {
      char w[] = "teststring";
      board[i] = w;
    }
    printf("%s\n", board[1]);
    return board;
  }

  char * print() {
    char * str = malloc(6 * 10);
    int location = 0;
    for (int i =0; i < 6; i++) {
      for (int w = 0; w < 10; w++) {
        char * tmp = "a";
        printf("BOARD[i][w]: %c\n", BOARD[i][w]);
        strcpy(tmp, &BOARD[i][w]);
        str[location] = tmp;
      }
    }
    return str;
  }
int main() {
  printf("BOARD[i][w]: %c\n", BOARD[1][1]);
  char * thing = print();
  printf("This is thing: %s\n", thing);
  return 0;
}

