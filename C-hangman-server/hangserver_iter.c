 /* Network server for hangman game */
 /* File: hangserver.c */

 #include <sys/types.h> //The sys/types. h header file defines a collection of typedef symbols and structures
 #include <sys/socket.h> //The <sys/socket. h> header defines macros to gain access to the data arrays in the ancillary data associated with a message header
 #include <netinet/in.h> //Defines the IN6ADDR_ANY_INIT macro. This macro must be constant at compile time and can be used to initialize a variable of type struct in6_addr to the IPv6 wildcard address. This variable is initialized by the system to contain the loopback IPv6 address
 #include <stdio.h> //has the information for all input, output related functions
 #include <syslog.h> //Syslog is a protocol and utility for capturing and logging system information
 #include <signal.h> //to specify how a program handles signals while it executes
 #include <errno.h> //defines macros for reporting and retrieving error conditions using the symbol errno
 #include <stdlib.h> //declares various utility functions for type conversions, memory allocation, algorithms, and other similar use cases
 #include <string.h> //used for string handling or manipulation but also used for various memory handling operations
 #include <unistd.h> //defines many symbols to represent configuration variables and implementation features provided
 #include <netdb.h> //definitions for network database operations
 #include "hangman.h" //Hangman script
#include <sys/wait.h> //declarations for waiting
#include "../DieWithMessage.c"
 


 extern time_t time ();

 # define NUM_OF_WORDS (sizeof (word) / sizeof (word [0]))
 # define MAXLEN 80 /* Maximum size in the world of Any string */
 /*# define HANGMAN_TCP_PORT 1066*/

 void func (int signum) //On receipt of SIGCHLD, the corresponding handler is activated, which in turn calls the wait() system call
 {
     wait(NULL);
 }


 int main()
 {
 	int sock, fd, client_len, r, process_id;
 	struct addrinfo hints, *server;
 	struct sockaddr client;
 	
 	/*configuring the host*/
 	
 	printf("Configuring the host.....,\n");
 	memset(&hints, 0, sizeof(struct addrinfo) );
 	
 	hints.ai_family = AF_INET;
 	hints.ai_socktype = SOCK_STREAM;
 	
 	r=getaddrinfo(0, "8080", &hints, &server);
 	
 	if(r!=0)
 	{
         DieWithSystemMessage("failed");
 		exit(1);
 	} 	
 	puts("host configured,\n");

 	srand ((int) time ((long *) 0)); /* randomize the seed */
 	
 	/*create the socket for the server*/
 	
 	printf("assign a socket");

 	sock = socket (server->ai_family, server->ai_socktype,server->ai_protocol);//0 or IPPROTO_TCP
 	if (sock ==-1) { //This error checking is the code Stevens wraps in his Socket Function etc
        DieWithSystemMessage("Error creating server socket");
 		exit (1);
 	}
 	puts("Server socket created");

 	

 	if (bind(sock, server->ai_addr,server->ai_addrlen) <0) {
        DieWithSystemMessage("binding socket");
	 	exit (2);
 	}
	puts("Server socket is listening for incoming requests from Clients");
	puts("Lets play hangman!");
 	listen (sock, 5);

 	while (1) {
 		client_len = sizeof (client);
 		/*accept function*/
 		puts("accepting new connection");
 		if ((fd = accept (sock,  &client, &client_len)) <0) {
            DieWithSystemMessage("accepting connection");
 			exit (3);
 		}
 		else {
 		
 		}
 		
 		process_id = fork();
 		
 		if(process_id == 0)
 		{
 			// Child process
 			printf("Created child process %d \n", getpid());
 			close(sock);
 			play_hangman (fd, fd);
 			exit(0);
 			
 			close (fd);
 		}
         else
        {
             signal(SIGCHLD, func);
             while(1);
        }
 	}
 }
