/* Hangclient.c - Client for hangman server.  */

#include <stdio.h> //has the information for all input, output related functions
#include <sys/types.h> //The sys/types. h header file defines a collection of typedef symbols and structures
#include <sys/socket.h> //The <sys/socket. h> header defines macros to gain access to the data arrays in the ancillary data associated with a message header
#include <netinet/in.h> //Defines the IN6ADDR_ANY_INIT macro. This macro must be constant at compile time and can be used to initialize a variable of type struct in6_addr to the IPv6 wildcard address. This variable is initialized by the system to contain the loopback IPv6 address
#include <netdb.h> //definitions for network database operations
#include <stdlib.h> //declares various utility functions for type conversions, memory allocation, algorithms, and other similar use cases
#include <string.h> //used for string handling or manipulation but also used for various memory handling operations
#include <unistd.h> //defines many symbols to represent configuration variables and implementation features provided
#include <netdb.h> //definitions for network database operations
#include "../DieWithMessage.c"

# define LINESIZE 80


int main(int argc, char *argv[]) {
    struct addrinfo hints, *server; /* Server's address  assembled here */

    int sock, count, r;
    char i_line[LINESIZE];
    char o_line[LINESIZE];
    char *server_name;

    /* Get server name from the command line.  If none, use 'localhost'

    server_name = (argc = 1)?  argv [1]: "localhost";
    */
    /*configuring the server address*/

    printf("Configuring the server.....,\n");
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    r = getaddrinfo(0, "8080", &hints, &server);

    if (r != 0) {
        DieWithSystemMessage("failed");
        exit(1);
    }
    puts("server configured,\n");

    /* Create the socket */
    /*create the socket for the server*/

    printf("assign client socket");

    sock = socket(server->ai_family, server->ai_socktype, server->ai_protocol);//0 or IPPROTO_TCP
    if (sock == -1) { //This error checking is the code Stevens wraps in his Socket Function etc
        DieWithSystemMessage("Erro creating server socket");
        exit(1);
    }
    puts("Client socket created");
    /*............................ */



    /* Set up the server's socket address, then connect */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    r = getaddrinfo(0, "8080", &hints, &server);

    if (r != 0) {
        DieWithSystemMessage("failed");

        exit(1);
    }
    puts("connecting .....,\n");
    /*server.sin_port = htons (HANGMAN_TCP_PORT);*/

    r = connect(sock, server->ai_addr, server->ai_addrlen);
    freeaddrinfo(server);


    /*OK connected to the server.
Take a line from the server and show it, take a line and send the user input to the server.
Repeat until the server terminates the connection. */

    printf("Connected to server% s \ n", server_name);
    while ((count = read(sock, i_line, LINESIZE)) > 0) {
        write(1, i_line, count);
        count = read(0, o_line, LINESIZE);//0 = STDIN
        write(sock, o_line, count);
    };

}
