#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define rows 6
#define cols 7

int doX(char **board){
  int r, c = 0;
  printf("Player X: ");
  while(1){
    if(1 != scanf("%d", &c) || c < 1 || c > 7){
      while(getchar() != '\n');
      printf("Column number out of bounds.Try again:");
    } 
    else { 
      break;
    }
  }
  c--;
  for(r = 5; r >= 0; r--){
    if(board[r][c] == '_'){
      board[r][c] = 'X';
      return 1;
    }
  }
  return 0;

}
int doO(char **board){
  int r, c = 0;
  printf("Player O: ");
  while(1){
    if(1 != scanf("%d", &c) || c < 1 || c > 7 ){
      while(getchar() != '\n');
      printf("Column number out of bounds.Try again:");
    } else { 
      break;
    }
  }
  c--;
  for(r = 5; r >= 0; r--){
    if(board[r][c] == '_'){
      board[r][c] = 'O';
      return 1;
    }
  }
  return 0;

}

void print(char  *board[rows]){
  for(int r = 0; r < rows; r++){
    for (int c = 0; c <cols; c++){
      printf(" %c ",board[r][c]);
    }
    printf("\n");
  }
  printf("---------------------");
  printf("\n 1  2  3  4  5  6  7 \n\n");
}
int checkHorizontal(char *board[rows]){
  int row, col;
  for(row = 0; row < rows; row++){
    for(col = 0; col < cols - 3; col++){
      if(board[row][col]!='_' && board[row][col] == board[row][col+1] &&  board[row][col] == board[row][col+2] &&  board[row][col] == board[row][col+3]){
	return 1;
      }
    }
  }
  return 0;

  
}
int checkVertical(char *board[rows]){
  int row, col;
  for(row = 0; row < rows-3; row++){
    for(col = 0; col < cols; col++){
      if(board[row][col]!='_' && board[row][col] == board[row+1][col] &&  board[row][col] == board[row+2][col] &&  board[row][col] == board[row+3][col]){
	return 1;
      }
    }
  }
  return 0;
}
int checkDiagonalR(char *board[rows]){
  int row, col;
  for(row = 0; row < rows-3; row++){
    for(col = 0; col < cols-3; col++){
      if(board[row][col]!='_' && board[row][col] == board[row+1][col+1] &&  board[row][col] == board[row+2][col+2] &&  board[row][col] == board[row+3][col+3]){
	return 1;
      }
    }
  }
  return 0;
}
int checkDiagonalL(char *board[rows]){
  int row, col;
  for(row = 5; row > rows-3; row--){
    for(col = 0; col < cols-3; col++){
      if(board[row][col]!='_' && board[row][col] == board[row-1][col+1] &&  board[row][col] == board[row-2][col+2] &&  board[row][col] == board[row-3][col+3]){
	return 1;
      }
    }
  }
  return 0;
}


int connected(char *board[rows]){
  return (checkHorizontal(board) || checkVertical(board) || checkDiagonalR(board)|| checkDiagonalL(board));
}

// int main(int argc, char *argv[]){
//   int finished = 0;
//   char  *board[rows]; 
//   for (int i=0; i<rows; i++) 
//     board[i] = (char *)malloc(cols * sizeof(char));
//   for(int r = 0; r < rows; r++){
//     for (int c = 0; c <cols; c++){
//       board[r][c]= '_';
//     }
//   }
//   while(!finished){
//     print(board);
//     while(!doX(board)){
//       print(board);   
//       printf("Column is full.\n");
//     }
//     print(board);
//     finished = connected(board);
//     if(finished){
//       printf("Player X has won the game!\n");
//       return 0;
//     }
//     while(!doO(board)){
//       print(board);   
//       printf("Column is full.\n");
//     }
//     finished = connected(board);
    
//   } 
//   print(board);
//   printf("Player O has won the game!\n");
//   return 0;

// }
