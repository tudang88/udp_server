#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <errno.h>

#define SERVER_PORT 2000
#define BUFFER_LENGHT 1024
char data_buffer[BUFFER_LENGHT];
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