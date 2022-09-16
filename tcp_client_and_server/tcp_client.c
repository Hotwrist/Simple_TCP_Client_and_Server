// Author: Odey John Ebinyi
// Date: 02nd, April 2022
// Description: This is a TCP(Transport Control Protocol) client program written in the C language.
//		It connects to a server hosted locally. By so doing, it sends a message and receives a
//		response from the server. And lastly, the connection is closed gracefully.

#include "../sock_header.h"

#define NUM_CMDLINE_ARG 3
#define MSG_SIZE 4096

int main(int argc, char *argv[]) 
{
    if (argc < NUM_CMDLINE_ARG) 
    {
        fprintf(stderr, "usage: tcp_client hostname port\n");
        return 1;
    }

    printf("Configuring server address...\n");
    
    struct addrinfo info;
    
    memset(&info, 0, sizeof(info));
    info.ai_socktype = SOCK_STREAM;
    
    struct addrinfo *server_address;
    
    if (getaddrinfo(argv[1], argv[2], &info, &server_address))
    {
        fprintf(stderr, "ERROR: getaddrinfo() failed to obtain address - (%d)\n", GET_SOCKET_ERRNO());
        return 1;
    }


    printf("Remote server address is: ");
    char address_buf[100];
    char service_buf[100];
    
    getnameinfo(server_address->ai_addr, server_address->ai_addrlen, address_buf, sizeof(address_buf), service_buf, sizeof(service_buf), NI_NUMERICHOST);
    printf("%s %s\n", address_buf, service_buf);

    printf("Creating socket...\n");
    
    SOCKET client_sock;
    client_sock = socket(server_address->ai_family, server_address->ai_socktype, server_address->ai_protocol);
    
    if (!IS_VALID_SOCKET(client_sock)) 
    {
        fprintf(stderr, "ERROR: socket() failed - (%d)\n", GET_SOCKET_ERRNO());
        return 1;
    }


    // Client connecting to server.	
    printf("Connecting...\n");
    if (connect(client_sock, server_address->ai_addr, server_address->ai_addrlen)) 
    {
        fprintf(stderr, "ERROR: connect() failed - (%d)\n", GET_SOCKET_ERRNO());
        return 1;
    }
    
    // free the memory address for the server, since we have connected to the server.
    freeaddrinfo(server_address);

    printf("Connected.\n");
    
    char msg_buf[MSG_SIZE];
    char recv_buf[MSG_SIZE];
    
    printf("Enter message to send: ");
    fgets(msg_buf, MSG_SIZE, stdin);
    
    int bytes_sent = send(client_sock, msg_buf, strlen(msg_buf), 0);
    printf("Sent %d bytes to server.\n", bytes_sent);
    
    int bytes_recv = recv(client_sock, recv_buf, 4096, 0);
    printf("Received %d bytes from server.\n", bytes_recv);
    printf("Response from server: %.*s", bytes_recv, recv_buf);
   
    printf("Closing socket...\n");
    CLOSE_SOCKET(client_sock);

    printf("Connection Terminated.\n");
    
    return 0;
}

