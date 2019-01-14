#include "networking.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );
  system("clear");
  printf("\n\n\n\n\n\n\tWelcome to Connect Duo!\n\nEnter your name: ");
  while (1) {
    fgets(buffer, sizeof(buffer), stdin);
    system("clear");
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    if (read(server_socket, buffer, 300) == 0) {
      char * shtdwn = "Server shutdown, guess I should sleep too...";
      printf("\n\nWoops: %s\n", shtdwn);
      exit(1);
    };
    printf("Action heeded: [%s]\n\n", buffer);
    printf("Make a Move!\nEnter a column: ");
  }
}
