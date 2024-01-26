#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <errno.h>

#define SERVER_PORT 2000
#define BUFFER_LENGHT 1024
#define MAX_CLIENT_SUPPORTED 32

char data_buffer[BUFFER_LENGHT];
int monitored_fd_set[MAX_CLIENT_SUPPORTED];

typedef struct student_{
    char name[32];
    unsigned int roll_no;
    char hobby[32];
    char dept[32];
} student_t;

// dummy student data
student_t student[5] = {
    {"John", 10101010, "Game", "CSE"},
    {"Michale", 10101010, "Game", "E&E"},
    {"Alex", 10101010, "Game", "Marketing"},
    {"David", 10101010, "Game", "Medical"},
    {"Messi", 10101010, "Game", "Physyical"},
};

void setup_udp_server_communication();
static char* process_GET_request(char *URL, unsigned int *response_len);
void string_space_trim(char *string);
/* initialize the monitor fd_set */
void intitiaze_monitor_fd_set(int* monitor_fds);
/* insert socket FD to monitor set */
void add_to_monitored_fd_set(int* monitor_fds, int skt_fd);
/* remove socket FD from monitor set */
void remove_from_monitored_fd_set(int* monitor_fds, int skt_fd);
/* re-init the readfds before invoking select() */
void re_init_readfds(int* monitor_fds, fd_set *fd_set_ptr);
/* get the max FD in monitor set */
int get_max_fd(int* monitor_fds);
