#include "networking.h"

void process(char *s, int p);
char * append(const char *s, char c);
void subserver(int from_client, int person);
char* concat(const char *s1, const char *s2);
char  *board[ROWS]; 

void fill() {
  for (int i=0; i<ROWS; i++) 
    board[i] = (char *)malloc((COLS) * sizeof(char));
  for(int r = 0; r < ROWS; r++){
    for (int c = 0; c <COLS; c++){
      board[r][c]= '_';
    }
  }
}

int main() {
    fill();
  int listen_socket;
  int f;
  listen_socket = server_setup();
  char buf[BUFFER_SIZE];

  printf("%s\n", *board);
  int player = 1; // 1 is X, 0 is O
  int num = 0;
  int numplayers[2], servers[2];
  int i = 0;
while (i < 2) {

    numplayers[i] = server_connect(listen_socket);
    read(numplayers[i], buf, sizeof(buf));
    memset(buf, 0, BUFFER_SIZE);
    servers[i] = fork();

    if (!servers[i]) {
      close(numplayers[i]);
      return 0;
    }
    i++;
  }
  printf("Server is no longer accepting players.\n");
  // shutdown(listen_socket, SHUT_RD);
  for (int i =0; i < 2; i++) {
    snprintf(buf, sizeof(buf), "You are player %i!", i + 1); // show board, tell that you are player X or O, ask for input
    write(numplayers[i], buf, sizeof(buf));
  }
  memset(buf, 0, sizeof(buf));
  while(1) {
    for (int a = 0; a < 2; a++) {
      read(numplayers[a], buf, sizeof(buf));
      char * s = buf;
      if (atoi(s) > COLS || atoi(s) - 1 < 0) {
        char * tmp = strcpy(s, "Invalid number, try again");
        print(board);
        write(numplayers[num], tmp, 50);
      }else{
      if (a == 0) {
        int num = atoi(s) - 1;
        char * tmp = board[num];
        for(int r = 5; r >= 0; r--){
          if(board[r][num] == '_'){
            board[r][num] = 'X';
            break;
          }
        }
        print(board);
        int finished = connected(board);
        printf("Got here\n");
        if (finished) {
          char * rite = "Player X has won the game!";
          write(numplayers[0], rite, 50);
          write(numplayers[1], rite, 50);
          return 0;
        }
      }else{
        int num = atoi(s) - 1;
        char * tmp = board[num];
        for (int r = 5; r >= 0; r--) {
          if (board[r][num] == '_') {
            board[r][num] = 'O';
            break;
          }
        }
        print(board);
        int finished = connected(board);
        printf("Got here\n");
        if (finished) {
          char * rite = "Player O has won the game!";
          write(numplayers[1], rite, 50);
          write(numplayers[0], rite, 50);
          return 0;
        }
      }
      
      char * hello[ROWS];
      for (int i=0; i<ROWS; i++) 
        hello[i] = (char *)malloc((COLS) * sizeof(char));
      for(int r = 0; r < ROWS; r++){
        for (int c = 0; c <COLS; c++){
          printf("Hell, wanker\n");
          hello[r][c] = board[r][c];
        }
      }
      char * send = "\n\t";
      for (int z = 0; z < 6; z++) {
        send = concat(send, hello[z]);
        send = append(send, '\n');
        send = append(send, '\t');
        printf("Hell, this sucks\n");
      }
      send = concat(send, "1234567\n");
      printf("THis is send:\n%s\n", send);

      write(numplayers[a], send, 300);
      //close(numplayers[a]);
      printf("Boss level\n");
      // memset(buf, 0, sizeof(buf));
    }
    }
  }
  return 0;
}

// void subserver(int client_socket, int who) {
//   char buffer[BUFFER_SIZE];
//   // int shared_file = open("share", O_CREAT | 0644);
//   // char game[65];
//   // if (read(shared_file, game, sizeof(game)) == -1) {
//   //   printf("File just created\n");
//   // }else{
//   //   printf("Got here");
//   //   freopen("share", "w", stdout);
//   //   print(board);
//   //   freopen("/dev/tty", "w", stdout); /*for gcc, ubuntu*/  
//   // }
//   for (int i = 0; i < 2; i++) {
//     /* Code to send board across */
//     write(numplayers[i], buffer, sizeof(buffer));
//   }
//   while (read(client_socket, buffer, sizeof(buffer))) {

//     printf("[subserver %d] received: [%s]\n", getpid(), buffer);
//     process(buffer, who);
//     who = !who;
//     char * hello = "";
//     for (int i = 6; i > 0; i--) {
//     for (int w = 0; w < 7; w++) {
//       char tmp = board[w][i];
//       hello = append(hello, tmp);
//       hello = append(hello, ' ');
//     }
//     hello = append(hello, ' ');
//     hello = append(hello, ' ');
//     hello = append(hello, (i + '0'));
//     hello = append(hello, '\n');
//   }
//   hello = append(hello, '\n');
//   printf("This is hello:\n%s\nsizeof(hello):%ld\n", hello, sizeof(hello));
//   //hello = concat(hello, buffer);
//   //printf("Now hello is this:\n%s\n", hello);
//   write(client_socket, hello, sizeof(hello));
//   free(hello);
//   }//end read loop
//   close(client_socket);
//   exit(0);
// }

char *append(const char *orig, char c)
{
    int sz = strlen(orig);
    char *str = malloc(sz + 2);
    strcpy(str, orig);
    str[sz] = c;
    str[sz + 1] = '\0';
    return str;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void process(char * s, int per) {
  if (atoi(s) > COLS || atoi(s) - 1 < 0) {
      char * tmp = strcpy(s, "Invalid number, try again");
      print(board);
      return;
    }
  if (per == 1) { // meaning that the person is X
    int num = atoi(s) - 1;
    char * tmp = board[num];
    for(int r = 5; r >= 0; r--){
      if(board[r][num] == '_'){
        board[r][num] = 'X';
        break;
      }
    }
    print(board);
    // s = print_board(board);
    //printf("This is s: %s\n", s);
    int finished = connected(board);
    printf("Got here");
    if (finished) {
      strcpy(s, "Player X has won the game!\n");
      per = 3;
      return;
    }
  }else{
    int num = atoi(s) + 1;
    char * tmp = board[num];
    for(int r = 5; r >= 0; r--){
      if(board[r][num] == '_'){
        board[r][num] = 'O';
        break;
      }
    }
    print(board);
    int finished = connected(board);
    if (finished) {
      strcpy(s, "Player O has won the game!\n");
      per = 3;
      return;
    }
  }

}
