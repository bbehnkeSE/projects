#include "pong.h"

/*
*	socklib.c
*
*	This file contains functions used lots when writing internet
*	client/server programs.  The two main functions here are:
*
*	make_server_socket( portnum )	returns a server socket
*					or -1 if error
*
*	connect_to_server(char *hostname, int portnum)
*					returns a connected socket
*					or -1 if error
*/ 

int make_server_socket( int portnum )
{
        // Create the socket
        printf("Creating socket...\t");
        fflush(stdout);
        int sock;
        if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
        {
                printf("Unable to make socket.\n");
                return -1;
        }
        printf("Done.\n");

        // Define server address
        printf("Defining address...\t");
        fflush(stdout);
        struct sockaddr_in address;
        address.sin_family      = AF_INET;
        address.sin_port        = htons(portnum);
        address.sin_addr.s_addr = INADDR_ANY;
        printf("Done.\n");

        // Bind the socket
        printf("Binding socket...\t");
        fflush(stdout);
        if(bind(sock, (struct sockaddr*)&address, sizeof(address)) != 0)
        {
                printf("Unable to bind socket.\n");
                return -1;
        }
        printf("Done.\n");

        // Listen on socket
        printf("Listen on socket...\t");
        fflush(stdout);
        if(listen(sock, 1) != 0)
        {
                printf("Unable to listen on sock.\n");
                return -1;
        }
        printf("Done.\n");

        return sock;
}

int connect_to_server( char *hostname, int portnum )
{
        // Create the socket
        printf("Creating socket...\t");
        fflush(stdout);
        int sock;
        if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
        {
                printf("Unable to make socket.\n");
                return -1;
        }
        printf("Done.\n");

        // Get host info
        printf("Getting host info...\t");
        fflush(stdout);
        struct hostent *host;
        if((host = gethostbyname(hostname)) == NULL)
        {
                printf("Unable to get host.\n");
                return -1;
        }
        printf("Done.\n");

        // Specify an address
        printf("Defining address...\t");
        fflush(stdout);
        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port   = htons(portnum);
        memcpy(&(address.sin_addr.s_addr), host->h_addr, 4);
        //address.sin_addr.s_addr = *(uint32_t*)(host->h_addr);
        printf("Done.\n");

        // Connect to server
        printf("Connecting to server...\t");
        fflush(stdout);
        if(connect(sock, (struct sockaddr*)&address, sizeof(address)) != 0) 
        {
                printf("Unable to connect.\n");
                return -1;
        }
        printf("Done.\n");

        return sock;
}
