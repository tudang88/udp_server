#include "socket_utils.h"

// Utils function
int createTCPIpv4Socket() { return socket(AF_INET, SOCK_STREAM, 0); }
int createUDPIpv4Socket() { return socket(AF_INET, SOCK_DGRAM, 0); }
struct sockaddr_in *createIPv4Address(char *ip, int port)
{
    // we need to allocate memory on heap to assure that the memory for this function is under
    // control of the caller, no be occupied by other function in the stack
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in)); // sockaddr_in -> address for IP_v4
    // char *ip = "142.250.188.46";                                      // test with www.google.com address
    // before assign to the port, we need to rearrange the number to the righ format of TCP port, that why we use htons() to convert
    address->sin_port = htons(port); // notice the port under 1000 usually are reserved, for example 80: http, 443:https
    address->sin_family = AF_INET;
    // convert string ip to correct format required by address field
    if (strlen(ip) == 0)
    {
        // alocate local host
        address->sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        // convert presentation form to network form if ip is not null
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    }
    return address;
}

/**
 * accept the socket
 *
 */
struct AcceptedSocket *acceptIncommingSocket(int serverSocketFD)
{
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, (struct sockaddr *)&clientAddress, (unsigned int *)&clientAddressSize);

    struct AcceptedSocket *acceptedSocket = malloc(sizeof(struct AcceptedSocket));
    acceptedSocket->address = clientAddress;
    acceptedSocket->acceptedSocketFD = clientSocketFD;
    acceptedSocket->acceptedSuccessfully = clientSocketFD > 0;

    if (!acceptedSocket->acceptedSuccessfully)
    {
        acceptedSocket->error = clientSocketFD; // client Socket FD will be an error number if accepting failure
    }

    return acceptedSocket;
}

// array for saving accepted sockets
struct AcceptedSocket acceptedSockets[10];
int acceptedSocketsCount = 0;
/**
 * accept incomming connection in separate thread
 */
void startAcceptingIncomingConnection(int serverSocketFD)
{
    pthread_t id; // declare a threadId
    pthread_create(&id, NULL, (void *)&acceptNewConnectionAndPrint, serverSocketFD);
}

/**
 * accept new connection and listen
 */

void acceptNewConnectionAndPrint(int serverSocketFD)
{
    while (TRUE)
    {
        // step 5: accept -> to get the client FileDescriptor but it will block the listening
        struct AcceptedSocket *acceptedSocket = acceptIncommingSocket(serverSocketFD);
        // save all incomming client
        acceptedSockets[acceptedSocketsCount++] = *acceptedSocket;
        // we need to separate thread for each incomming connection to handle the message simutineously
        receiveIncommingDataInSeparateThread(acceptedSocket);
    }
}

/**
 * receive incomming data for each connection in a separate thread
 */
void receiveIncommingDataInSeparateThread(struct AcceptedSocket *pSocket)
{
    pthread_t id;
    pthread_create(&id, NULL, (void *)&receiveAndPrintIncomingData, pSocket->acceptedSocketFD);
}

/**
 * receive and print incomming data
 */
void receiveAndPrintIncomingData(int socketFD)
{
    char buffer[1024];

    while (TRUE)
    {
        memset(buffer, 0, sizeof(buffer));

        ssize_t amountReceive = recv(socketFD, buffer, 1024, 0);
        if (amountReceive > 0)
        {
            printf("message from client: %d \n", socketFD);
            printf("%s\n", buffer);
            sendMessageToOtherClients(buffer, socketFD);
        }

        if (amountReceive < 0)
            break;
    }
    // close socket after finish
    close(socketFD);
}

/**
 * broadcast to all accepted client the incomming message
 */
void sendMessageToOtherClients(char *buffer, int socketFD)
{
    for (int i = 0; i < acceptedSocketsCount; i++)
    {
        // don't send message to the incomming client itself
        if (acceptedSockets[i].acceptedSocketFD != socketFD)
        {
            // send here
            // char *message = "ClientId";
            // // sprintf(message, "ClientId %d:", socketFD);
            // strcat(message, buffer);
            size_t amountWasSent = send(acceptedSockets[i].acceptedSocketFD, buffer, strlen(buffer), 0);
        }
    }
}

/**
 * use for client receiving message only
 */
void receiveMessageInSeparateThreadClientSide(int socketFD)
{
    pthread_t id;
    pthread_create(&id, NULL, (void *)&receiveMessageAndPrint, socketFD);
}
/**
 * receive message in client side
 */
void receiveMessageAndPrint(int socketFD)
{

    char buffer[1024];

    while (TRUE)
    {
        // reset buffer
        memset(buffer, 0, sizeof(buffer));
        size_t receivedAmount = recv(socketFD, buffer, 1024, 0);
        // print out result
        if (receivedAmount > 0)
        {
            printf("%s", buffer);
        }
        if (receivedAmount == 0)
            break;
    }
}
