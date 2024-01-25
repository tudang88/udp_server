#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#define TRUE 1
#define FALSE 0
struct AcceptedSocket
{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};

struct AcceptedSocket *acceptIncommingSocket(int serverSocketFD);
int createTCPIpv4Socket();
int createUDPIpv4Socket();
struct sockaddr_in *createIPv4Address(char *ip, int port);

void receiveAndPrintIncomingData(int socketFD);
void startAcceptingIncomingConnection(int serverSocketFD);
void acceptNewConnectionAndPrint(int serverSocketFD);
void receiveIncommingDataInSeparateThread(struct AcceptedSocket *pSocket);
void sendMessageToOtherClients(char *buffer, int socketFD);
void receiveMessageInSeparateThreadClientSide(int socketFD);
void receiveMessageAndPrint(int socketFD);