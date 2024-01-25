#include <stdio.h>
#include "udp_web_server.h"


/**
 * setup and handle connection
 */
void setup_udp_server_communication(){
    // init socket file descriptor
    int master_sock_udp_fd = 0;
    int sent_recv_bytes = 0;
    int addr_len = 0;
    int opt = 1;

    /**
     * client communication socket FD 
     */
    int comm_socket_fd = 0;
    /**
     * set of FD on which select() observes
     */
    fd_set readfds;
    /**
     * server and client info structure 
     */
    struct sockaddr_in server_addr, client_addr;

    /**
     * master socket creation 
     */
    if (master_sock_udp_fd = socket(AF_INET, SOCK_DGRAM, 0) == -1)
    {
        printf("socket creation failed\n");
        exit(1);
    }

    // set master socket to allow multiple connections
    if (setsockopt(master_sock_udp_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt) < 0) 
    {
        printf("UDP socket creation failed for multiple connections\n");
        exit(1);
    }

    /**
     * server infomation configure 
     */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);
    addr_len = sizeof(struct sockaddr);
    





}

/**
 * 
 */
static char* process_GET_request(char *URL, unsigned int *response_len) {

}

/**
 * 
 */
void string_space_trim(char *string) {

}
