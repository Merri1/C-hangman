//
// Created by merri on 23/04/23.
//

#ifndef TEAMA_SELECTSERVER_TCPCONNECTIONSETUP_H
#define TEAMA_SELECTSERVER_TCPCONNECTIONSETUP_H

#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include "./DieWithMessage.c"

int setup_socket(const char* portNum) {
    int sock, r;
    struct addrinfo hints, *server;

    // Zero out the memory location of addrinfo
    memset(&hints, 0, sizeof(struct addrinfo));

    // Set IPv4 address family and a stream socket type
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Convert human-readable address into addrinfo structure
    r = getaddrinfo(0, portNum, &hints, &server);

    // Check return status of the getaddrinfo function
    if (r != 0) {
        DieWithSystemMessage("Error: Failed at getaddrinfo()");
    }

    // create socket with family, type and protocol of the previously initialised server addrinfo
    sock = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

    // socket() returns -1 when unsuccessful so check for that
    if (sock == -1) {
        DieWithSystemMessage("Error creating server socket");
    }

    // If bind fails output error message
    if (bind(sock, server->ai_addr, server->ai_addrlen) < 0) {
        DieWithSystemMessage("Error when binding socket");
    }

    // output some status information
    puts("Server socket is listening for incoming requests from Clients");
    puts("Lets play hangman!");

    // Listen on tha
    listen(sock, 5);

    return sock;
}

int accept_connection(int serverSocket) {
    struct sockaddr client;
    int client_len, clientSocket;

    client_len = sizeof(client);
    puts("Accepting new connection");

    // Accept a request
    clientSocket = accept(serverSocket, &client, &client_len);

    // Check if accept() returned an error
    if (clientSocket < 0) {
        DieWithSystemMessage("Error when accepting a connection");
    }

    return clientSocket;
}
#endif //TEAMA_SELECTSERVER_TCPCONNECTIONSETUP_H
