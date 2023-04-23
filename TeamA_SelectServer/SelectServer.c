#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "hangman.h"
#include "../TCPConnectionSetup.h"

extern time_t time();

int setup_socket(const char *string);

int accept_connection(int socket);

# define NUM_OF_WORDS (sizeof (word) / sizeof (word [0]))
# define MAXLEN 80 /* Maximum size in the world of Any string */

int main() {
    struct timeval timeout;
    int serverSocket, process_id;

    // Create a TCP socket on localhost port 8080
    serverSocket = setup_socket("8080");

    // Set timeout value to 10 seconds - not used anymore
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Declare two file descriptor sets
    fd_set current_sockets, ready_sockets;

    while (1) {
        FD_ZERO(&current_sockets);
        FD_SET(serverSocket, &current_sockets);

        ready_sockets = current_sockets;

        if(select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0) {
            DieWithSystemMessage("Failure with select() function call.");
        }

        // Loop through the set of file descriptors
        for(int i = 0; i < FD_SETSIZE; i++) {
            // Check if any are ready for processing
            if(FD_ISSET(i, &ready_sockets)) {
                // If the socket is ready  a new connection is waiting
                if(i == serverSocket) {
                    // Accept new connection and add it to the list of current file descriptors
                    int clientSocket = accept_connection(serverSocket);
                    FD_SET(clientSocket, &current_sockets);
                } else {
                    // Other sockets that are ready are clients so continue playing the Hangman game
                    play_hangman(i, i);
                }
            }
        }
    }
}
