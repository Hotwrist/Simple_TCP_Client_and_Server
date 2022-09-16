//******************************************************************************************
// Author: Odey John Ebinyi
// Date: 02nd April, 2022
// Description: Header file containing the required files needed by network programs
//		implemented in the C language. This is to be included in the implementation
//		files (i.e .c files) that need the functionalities
//******************************************************************************************  

// For windows platforms
#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#if !defined(IPV6_V6ONLY)
#define IPV6_V6ONLY 27
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
//*********************************************
//*********************************************
// For Linux and MacOS platforms
#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#endif
//********************************************

#if defined(_WIN32)
#define IS_VALID_SOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSE_SOCKET(s) closesocket(s)
#define GET_SOCKET_ERRNO() (WSAGetLastError())

#else
#define IS_VALID_SOCKET(s) ((s) >= 0) // On UNIX, returns a negative number on failure
#define CLOSE_SOCKET(s) close(s)
#define SOCKET int
#define GET_SOCKET_ERRNO() (errno)
#endif

#include <string.h>
#include <time.h>
#include <stdio.h>

// connect ====> returns same as bind()
// bind() ====> returns 0 on success & non-zero (-1) on failure
// listen() ====> returns 0 on success & non-zero (-1) on failure
// accept() ====> returns non-negative( i.e 0, 1, 2, ... n) on success & -1 on failure
// recv() ====> returns 0 or -1 if the connection is terminated by the client.
// select() ====> returns -1 on failure (check for < 0)



