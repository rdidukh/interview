#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

void die(const char *str, ...)
{
    char buffer[256];

    va_list args;
    va_start(args, str);
    snprintf(buffer, sizeof(buffer), str, args);
    va_end(args);
    perror(buffer);
    exit(EXIT_FAILURE);
}


int main(int argc, char*argv[])
{
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sockfd < 0) die("socket");

    struct sockaddr_un sa;
    
    memset(&sa, 0, sizeof(sa));
        
    sa.sun_family = AF_UNIX;
    strncpy(sa.sun_path, argv[1], sizeof(sa.sun_path));
    if(sa.sun_path[0] == '@') sa.sun_path[0] = 0;

    int slen = sendto(sockfd, argv[2], strlen(argv[2])+1, 0, (struct sockaddr*)&sa, sizeof(sa));

    if(slen < 0) die("sendto");

    close(sockfd);
}




