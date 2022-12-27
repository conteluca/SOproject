#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define S_ADDR "127.0.0.1"
#define ERROR (-1)
#define RAND 5000
/* Structure describing an Internet socket address.  */
typedef struct sockaddr_in internetServer;
typedef struct sockaddr genericServer;

internetServer server;

void printError(int err, char *msg) {
    if (err == ERROR) {
        perror(msg);
        exit(1);
    }
}

void *consume(void *args) {

    unsigned tid = pthread_self();
    /* Create socket. */
    int channel = socket(AF_INET, SOCK_STREAM, 0);
    printError(channel, "opening stream socket");

    int con = connect(channel, (genericServer *) &server, sizeof server);
    printError(con, "connecting stream socket");

    char buff[1024];
    int value = rand() % RAND;
    sprintf(buff,"1:%d",value);
    int i=0;
    while (i<1024 && buff[i]!='\0'){
        write(channel,&buff[i],1);
//        write(1,&buff[i],1);
        i++;
    }
    memset(buff, 0, 1024);
    sprintf(buff,"%d consume %d on channel %d\n",tid,value,channel);
    write(1,buff,1024);
    close(channel);

    pthread_exit(NULL);

}

void *produce(void *args) {

    unsigned tid = pthread_self();
    /* Create socket. */
    int channel = socket(AF_INET, SOCK_STREAM, 0);
    printError(channel, "opening stream socket");

    int con = connect(channel, (genericServer *) &server, sizeof server);
    printError(con, "connecting stream socket");

    char buff[1024];
    int value = rand() % RAND;
    sprintf(buff,"0:%d",value);
    int i=0;
    while (i<1024 && buff[i]!='\0'){
        write(channel,&buff[i],1);
//        write(1,&buff[i],1);
        i++;
    }
    memset(buff, 0, 1024);
    sprintf(buff,"%d produce %d on channel %d\n",tid,value,channel);
    write(1,buff,1024);
    close(channel);

    pthread_exit(NULL);
}

int main() {
    int CLIENT = 5000;

    //assegno indirizzo server
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_aton(S_ADDR, &server.sin_addr);

    pthread_t consumer[CLIENT], producer[CLIENT]; //tid
    for (int i = 0; i < CLIENT; ++i) {
        pthread_create(&consumer[i], NULL, consume, NULL);
        pthread_create(&producer[i], NULL, produce, NULL);
    }
    for (int i = 0; i < CLIENT; ++i) {
        pthread_join(consumer[i], NULL);
        pthread_join(producer[i], NULL);
    }
    printf("client ended");

    return 0;
}

