#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef NETWORK_PIPE_H
#define NETWORK_PIPE_H

int client_work(int *to_server);
int server_work(int *to_client);

#endif
