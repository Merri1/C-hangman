#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

# define LINESIZE 80

int main(int argc, char *argv[]) {
    struct addrinfo hints, *server; /* Server's address  assembled here */
    int sock, count, r;
    char i_line[LINESIZE];
    char o_line[LINESIZE];
    char *server_name;

    /* Get server name from the command line. If none, use 'localhost' */
    server_name = (argc == 2)? argv[1]: "localhost";

    /* Configuring the server address */
    printf("Configuring the server...\n");
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM; // Use Datagram socket
    hints.ai_protocol = IPPROTO_UDP; // Use UDP protocol

    r = getaddrinfo(server_name, "8080", &hints, &server);

    if (r != 0) {
        perror("failed");
        exit(1);
    }
    puts("Server configured.");

    /* Create the socket */
    printf("Creating client socket...\n");
    sock = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    if (sock == -1) {
        perror("Error creating client socket");
        exit(1);
    }
    puts("Client socket created.");

    /* OK connected to the server.
       Take a line from the server and show it, take a line and send the user input to the server.
       Repeat until the server terminates the connection. */
    printf("Connected to server %s.\n", server_name);
    while (1) {
        count = recvfrom(sock, i_line, LINESIZE, 0, NULL, NULL); // Use recvfrom for UDP
        if (count > 0) {
            write(1, i_line, count);
        } else {
            break;
        }

        count = read(0, o_line, LINESIZE); // 0 = STDIN
        sendto(sock, o_line, count, 0, server->ai_addr, server->ai_addrlen); // Use sendto for UDP
    }

    return 0;
}

