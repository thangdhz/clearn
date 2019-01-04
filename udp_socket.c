#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXBUFLEN       14
#define MYPORT          41230

int sockfd;
struct sockaddr_in6 their_addr; /* connector's address information */
struct hostent *he;
int numbytes;
char buf[MAXBUFLEN] = {0x23, 0x02, 0x80, 0xD0, 0xB3, 0x00, 0x00, 0x05, 0x84, 0x02, 0x00, 0x00 , 0x25, 0x02};
int addr_len;			/* Address length for the network functions
                                                                 that require that      */
char addr_buf[128];

int main( int argv, char **argc) {
    int yes = 1;


    sockfd = socket(AF_INET6, SOCK_DGRAM, 0);
    their_addr.sin6_family = AF_INET6;      /* host byte order */
    their_addr.sin6_port = htons(MYPORT);  /* short, network byte order */
    if (inet_pton(AF_INET6, "fd00:aaaa::03", &their_addr.sin6_addr) != 1) {
        perror("inet_pton");
        exit(1);
    }
    connect(sockfd, (struct sockaddr *)&their_addr, sizeof(their_addr));
    if ((numbytes = sendto(sockfd, buf, MAXBUFLEN, 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
    {
        perror("sendto");
        exit(1);
    }

    return 0;
}
