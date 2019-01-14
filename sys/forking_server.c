#include "networking.h"

void process(char *s, int p);
char * append(const char *s, char c);
void subserver(int from_client, int person);
char* concat(const char *s1, const char *s2);
  char  *board[ROWS]; 
  void fill() {
    for (int i=0; i<ROWS; i++) 
    board[i] = (char *)malloc((COLS + 1) * sizeof(char));
  for(int r = 0; r < ROWS; r++){
    for (int c = 0; c <COLS + 1; c++){
      board[r][c]= '_';
    }
    board[r][COLS + 1] = '\0';
  }}
int main() {
  fill();
  int listen_socket;
  int f;
  listen_socket = server_setup();

  printf("%s\n", *board);
  int player = 1; // 1 is X, 0 is O
  while (1) {

    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0) {
      subserver(client_socket, player);
    }else
      close(client_socket);
  }
}

void subserver(int client_socket, int who) {
  char buffer[BUFFER_SIZE];
  // int shared_file = open("share", O_CREAT | 0644);
  // char game[65];
  // if (read(shared_file, game, sizeof(game)) == -1) {
  //   printf("File just created\n");
  // }else{
  //   printf("Got here");
  //   freopen("share", "w", stdout);
  //   print(board);
  //   freopen("/dev/tty", "w", stdout); /*for gcc, ubuntu*/  
  // }
  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer, who);
    who = !who;
    char * hello = "";
    for (int i = COLS; i > 0; i--) {
    for (int w = 0; w < ROWS; w++) {
      char tmp = board[w][i];
      hello = append(hello, tmp);
      hello = append(hello, ' ');
    }
    hello = append(hello, ' ');
    hello = append(hello, ' ');
    hello = append(hello, (i + '0'));
    hello = append(hello, '\n');
  }
  hello = append(hello, '\n');
  printf("This is hello:\n%s\nsizeof(hello):%ld\n", hello, sizeof(hello));
  //hello = concat(hello, buffer);
  //printf("Now hello is this:\n%s\n", hello);
  write(client_socket, hello, sizeof(hello));
  free(hello);
  }//end read loop
  close(client_socket);
  exit(0);
}

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
  // char buf[65];
  // int shared_file = open("share", 0644);
  // if (read(shared_file, buf, sizeof(buf)) == -1) {
  //   printf("Error %d: %s\n", errno, strerror(errno));
  //   exit(1);
  // }
  // char curr[65];
  // int pb = open("board", O_CREAT | 0644);
  // freopen("board", "w", stdout);
  // print(board);
  // freopen("/dev/tty", "w", stdout); /*for gcc, ubuntu*/ 
  // read(pb, curr, sizeof(curr));
  // printf("Between %s and %s, they are %d\n", buf, curr, strcmp(buf, curr));
  // close(pb);
  if (atoi(s) > COLS || atoi(s) - 1 < 0) {
      char * tmp = strcpy(s, "Invalid number, try again");
      print(board);
      return;
    }
  if (!per) { // meaning that the person is X
    int num = atoi(s);
    char * tmp = board[num];
    for(int r = 5; r >= 0; r--){
      if(board[r][num] == '_'){
        board[r][num] = 'X';
        break;
      }
    }
    print(board);
    // s = print_board(board);
    printf("This is s: %s\n", s);
    int finished = connected(board);
    if (finished) {
      strcpy(s, "Player X has won the game!\n");
      per = 3;
      return;
    }
  }else{
    int num = atoi(s);
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
