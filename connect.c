#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define rows 6
#define cols 7


void print(char  *board[rows]){
  for(int r = 0; r < rows; r++){
    for (int c = 0; c <cols; c++){
      printf(" %c ",board[r][c]);
    }
    printf("\n");
  }
  printf("\n 1  2  3  4  5  6  7 \n");
}
int main(int argx, char *argv[]){
  char  *board[rows]; 
    for (int i=0; i<rows; i++) 
      board[i] = (char *)malloc(cols * sizeof(char));
  for(int r = 0; r < rows; r++){
    for (int c = 0; c <cols; c++){
      board[r][c]= '_';
    }
  }
  print(board);
}
