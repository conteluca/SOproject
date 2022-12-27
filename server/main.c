#include "server.h"

void parseInput(char buff[1024], int i);

int main() {
    internetServer server;
    int channel, client;

    /* Create socket. */
    channel = socket(AF_INET, SOCK_STREAM, 0);
    printError(channel, "opening stream socket");

    /* Bind socket using wildcards.*/
    server.sin_family = PF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Give the socket FD the local server ADDR (which is LEN bytes long).  */
    int fd = bind(channel, (genericServer *) &server, sizeof server);
    printError(fd, "binding stream socket");
    printf("Socket port #%d\n", ntohs(server.sin_port));

    /* Start accepting connections. */
    listen(channel, MAX_CLIENT);
    int n = 0;
    do {
        client = accept(channel, (genericServer *) 0, (socklen_t *) 0);
        acceptError(client);

        char buff[MAX_STRING];
        n++;

        readFromChannel(client, buff, MAX_STRING);
       // toSTDOUT(buff,MAX_STRING);
        parseInput(buff,MAX_STRING);


        close(client);

    } while (client > 0);

    return 0;
}

void parseInput(char *buff, int len) {
    int operation,value;
    operation = atoi(&buff[0]);
    value = atoi(buff+2);
    char msg[MAX_STRING];
    memset(msg,0,MAX_STRING);
    sprintf(msg,"%d:%d\n",operation,value);
    write(1,msg, MAX_STRING);
}
