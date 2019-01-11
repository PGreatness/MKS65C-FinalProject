#include "pipe.h"

int server_work(int *to_client) {
    int WKP;
    if ((WKP = mkfifo("WKP", 0644)) == -1) {
        printf("%s", strerror(errno));
    }
}

int client_work(int *to_server) {

}
