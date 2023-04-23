/*#ifndef HANGMAN_H*/
#define HANGMAN_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

extern time_t time();

int maxlives = 12;
char *word[] = {
#include "words"
};

# define NUM_OF_WORDS (sizeof (word) / sizeof (word [0]))
# define MAXLEN 80 /* Maximum size in the world of Any string */
/*# define HANGMAN_TCP_PORT 1066*/
void play_hangman(int sockfd) {
    // Game logic implementation here
}
int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        exit(1);
    }
    // Set up server address and port
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to any available network interface
    servaddr.sin_port = htons(1066); // Set the desired port number
    // Bind the socket to the server address and port
    if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
        perror("Error binding socket");
        close(sockfd);
        exit(1);
    }
    // Call the hangman game logic
    play_hangman(sockfd);
    // Close the socket
    close(sockfd);
    return 0;
}