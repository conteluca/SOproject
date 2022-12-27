//
// Created by kali on 12/24/22.
//


#ifndef SOPROJECT_SERVER_H
#define SOPROJECT_SERVER_H

#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <asm-generic/errno.h>
#include <string.h>

#define ERROR (-1)
#define SERVER_PORT 8080
#define MAX_STRING 1024
#define MAX_CLIENT 5000


/* Structure describing an Internet socket address.  */
typedef struct sockaddr_in internetServer;
/* Structure describing an Internet socket address.  */
typedef struct sockaddr_un unixServer;
/* Structure describing a generic socket address.  */
typedef struct sockaddr genericServer;

void printError(int err, char *msg);
void acceptError(int fd);
void readFromChannel(int channel, char *buff, int len);
void toSTDOUT(char *buff, int len);

#endif //SOPROJECT_SERVER_H

/*
Protocol Family
  SOCK_STREAM : TCP
  SOCK_DGRAM : UDP
  AF_INET : Internet domain
  AF_UNIX : Unix file system
  AF_APPLETALK : Apple Computer Inc. Appletalk network
  AF_PUP : Xerox Corporation PUP internet
 */
