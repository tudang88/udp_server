#include <stdio.h>
#include "udp_web_server.h"
#include "socket_utils.h"

void
intitiaze_monitor_fd_set(int* monitor_fds)
{

    int i = 0;
    for(; i < MAX_CLIENT_SUPPORTED; i++)
        *(monitor_fds + i) = -1;
}

void 
add_to_monitored_fd_set(int* monitor_fds, int skt_fd)
{

    int i = 0;
    for(; i < MAX_CLIENT_SUPPORTED; i++){

        if(*(monitor_fds + i) != -1)
            continue;   
        *(monitor_fds + i) = skt_fd;
        break;
    }
}

void
remove_from_monitored_fd_set(int* monitor_fds, int skt_fd){

    int i = 0;
    for(; i < MAX_CLIENT_SUPPORTED; i++){

        if(*(monitor_fds + i) != skt_fd)
            continue;

        *(monitor_fds + i) = -1;
        break;
    }
}

void
re_init_readfds(int* monitor_fds, fd_set *fd_set_ptr){

    FD_ZERO(fd_set_ptr);
    int i = 0;
    for(; i < MAX_CLIENT_SUPPORTED; i++){
        if(*(monitor_fds + i) != -1){
            FD_SET(*(monitor_fds + i), fd_set_ptr);
        }
    }
}

int 
get_max_fd(int* monitor_fds){

    int i = 0;
    int max = -1;

    for(; i < MAX_CLIENT_SUPPORTED; i++){
        if(*(monitor_fds + i) > max)
            max = *(monitor_fds + i);
    }

    return max;
}

/**
 * setup and handle connection
 */
void setup_udp_server_communication()
{
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
    struct sockaddr_in *server_addr, *client_addr;

    /**
     * master socket creation
     */
    if (master_sock_udp_fd = createUDPIpv4Socket() == -1)
    {
        printf("socket creation failed\n");
        exit(1);
    }

    // set master socket to allow multiple connections
    if (setsockopt(master_sock_udp_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        printf("UDP socket creation failed for multiple connections\n");
        exit(1);
    }

    /**
     * server infomation configure
     */
    server_addr = createIPv4Address("", SERVER_PORT);
    addr_len = sizeof(struct sockaddr);

    /**
     * bind the server
     */
    if (bind(master_sock_udp_fd, (struct sockaddr *) server_addr, sizeof(struct sockaddr)) == -1) {
        printf("socket bind failed\n");
        exit(1);
    }

}

/**
 *
 */
static char *process_GET_request(char *URL, unsigned int *response_len)
{
}

/**
 *
 */
void string_space_trim(char *string)
{
}
