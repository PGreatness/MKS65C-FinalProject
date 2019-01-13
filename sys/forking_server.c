#include "networking.h"

void process(char *s, char * p);
void subserver(int from_client, char * person);
  char  *board[ROWS]; 
  void fill() {
    for (int i=0; i<ROWS; i++) 
    board[i] = (char *)malloc(COLS * sizeof(char));
  for(int r = 0; r < ROWS; r++){
    for (int c = 0; c <COLS; c++){
      board[r][c]= '_';
    }
  }}
int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();

  printf("%s\n", *board);
  char player[] = "X";
  while (1) {

    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0) {
      subserver(client_socket, player);
      player[0] = "O";
    }else
      close(client_socket);
  }
}

void subserver(int client_socket, char * who) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer, who);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s, char * per) {
  if (atoi(s) > COLS || atoi(s) < 1) {
      char * tmp = strcpy(s, "Invalid number, try again");
      print(board);
      return;
    }
  if (!strcmp(per, "X")) {
    int num = atoi(s);
    char * tmp = board[num];
    int index = strchr(tmp, '_');
    board[num][index] = 'X';
    int finished = connected(board);
    if (finished) {
      strcpy(s, "Player X has won the game!\n");
      strcpy(per, "W");
      return;
    }
  }else{
    int num = atoi(s);
    char * tmp = board[num];
    int index = strchr(tmp, '_');
    board[num][index] = 'O';
    int finished = connected(board);
    if (finished) {
      strcpy(s, "Player O has won the game!\n");
      strcpy(per, "W");
      return;
    }
  }

}
