/* Network server for hangman game */
/* File: hangserver.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "hangman.h"
#include "../DieWithUserMessage.c"


extern time_t time();

# define NUM_OF_WORDS (sizeof (word) / sizeof (word [0]))
# define MAXLEN 80 /* Maximum size in the world of Any string */

/*# define HANGMAN_TCP_PORT 1066*/

int main() {
    int sock, fd, client_len, r, process_id;
    struct addrinfo hints, *server;
    struct sockaddr client;

    /*configuring the host*/

    printf("Configuring the host.....,\n");
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    r = getaddrinfo(0, "8080", &hints, &server);

    if (r != 0) {
        perror("failed");
        exit(1);
    }
    puts("host configured,\n");

    srand((int) time((long *) 0)); /* randomize the seed */

    /*create the socket for the server*/

    printf("assign a socket");

    sock = socket(server->ai_family, server->ai_socktype, server->ai_protocol);//0 or IPPROTO_TCP
    if (sock == -1) { //This error checking is the code Stevens wraps in his Socket Function etc
        perror("Erro creating server socket");
        exit(1);
    }
    puts("Server socket created");


    if (bind(sock, server->ai_addr, server->ai_addrlen) < 0) {
        perror("binding socket");
        exit(2);
    }
    puts("Server socket is listening for incoming requests from Clients");
    puts("Lets play hangman!");
    listen(sock, 5);

    while (1) {
        client_len = sizeof(client);
        /*accept function*/
        puts("accepting new connection");
        if ((fd = accept(sock, &client, &client_len)) < 0) {
            perror("accepting connection");
            exit(3);
        } else {

        }

        process_id = fork();

        if (process_id == 0) {
            // Child process
            printf("Created child process %d \n", getpid());
            close(sock);
            play_hangman(fd, fd);
            exit(0);

            close(fd);
        }
    }
}

int setup_socket(char* portNum) {
    struct addrinfo hints, server;
    struct sockaddr client;
}
