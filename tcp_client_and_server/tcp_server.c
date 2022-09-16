// Author: Odey John Ebinyi
// Date: 02nd, April 2022
// Description: This is a TCP(Transport Control Protocol) server program written in the C language.
//		It listens to connection from clients. By so doing, it receives a message and sends a
//		response to the client that connects successfully. And lastly, the connection is closed gracefully.

#include "../sock_header.h"
#include <ctype.h>

int main() 
{
    printf("Configuring local address.on port 8080..\n");
    
    struct addrinfo info;
    memset(&info, 0, sizeof(info));
    info.ai_family = AF_INET;
    info.ai_socktype = SOCK_STREAM;
    info.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &info, &bind_address);


    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family,
            bind_address->ai_socktype, bind_address->ai_protocol);
    if (!IS_VALID_SOCKET(socket_listen)) 
    {
        fprintf(stderr, "ERROR: socket() failed - (%d)\n", GET_SOCKET_ERRNO());
        return 1;
    }


    printf("Binding socket to local address...\n");
    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) 
    {
        fprintf(stderr, "ERROR: bind() failed - (%d)\n", GET_SOCKET_ERRNO());
        return 1;
    }

    freeaddrinfo(bind_address);


    printf("Listening...\n");
    if (listen(socket_listen, 10) < 0)
    {
        fprintf(stderr, "listen() failed. (%d)\n", GET_SOCKET_ERRNO());
        return 1;
    }

    printf("Waiting for connections...\n");


    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    SOCKET socket_client = accept(socket_listen, (struct sockaddr*) &client_address, &client_len);
     
    if (!IS_VALID_SOCKET(socket_client)) 
    {
       fprintf(stderr, "accept() failed. (%d)\n", GET_SOCKET_ERRNO());
               return 1;
    }
     
    printf("Reading request...\n");
    char req[4096];
    int bytes_recv = recv(socket_client, req, 4096, 0);
    printf("Received bytes: %d.\n", bytes_recv);
    printf("Message: %.*s", bytes_recv, req);
     
    printf("Sending response...\n");
    char resp_buf[4096] = "Hello, i got your message!.\n";
    int bytes_sent = send(socket_client, resp_buf, strlen(resp_buf), 0);
    printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(resp_buf));
     
	
    printf("Closing listening socket...\n");
    CLOSE_SOCKET(socket_listen);

    printf("Connection Terminated.\n");

    return 0;
}
