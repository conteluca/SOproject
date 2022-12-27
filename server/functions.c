#include "server.h"

void readFromChannel(int channel, char *buff, int len) {
    int i = 0;
    memset(buff, 0, len);

    while (i < len && read(channel, &buff[i], 1) > 0) {
        i++;
    }
}

void toSTDOUT(char *buff, int len) {
    int i = 0;
    while (i<len && buff[i] != '\0') {
        write(1, &buff[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

void printError(int err, char *msg) {
    if (err == ERROR) {
        perror(msg);
        exit(1);
    }
}

void acceptError(int fd) {
    // https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2l/index.html
    switch (fd) {
        case ENOBUFS:
            printError(fd,
                       "Lack of memory available to support the call.");
            break;
        case EPROTONOSUPPORT:
            printError(fd,
                       "Request for an unknown protocol.");
            break;
        case EPROTOTYPE:
            printError(fd,
                       "Request for an unsupported type of socket.");
            break;
        case ETIMEDOUT:
            printError(fd,
                       "No connection established in specified time. This happens when the destination host is down or when problems in the network result in lost transmissions.");
            break;
        case ECONNREFUSED:
            printError(fd,
                       "The host refused service. This happens when a server process is not present at the requested address.");
            break;
        case ENETDOWN | EHOSTDOWN:
            printError(fd,
                       "These errors are caused by status information delivered by the underlying communication interface.");
            break;
        case ENETUNREACH | EHOSTUNREACH:
            printError(fd,
                       "These operational errors can occur either because there is no route to the network or host, or because of status information returned by intermediate gateways or switching nodes. The status returned is not always sufficient to distinguish between a network that is down and a host that is down.");
            break;
        default:
            break;

    }


}
