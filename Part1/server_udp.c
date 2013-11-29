#include <math.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

//just for false false and true
#include <stdbool.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void startServer(char *address, char *port)
{
    int sockfd, n;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    float recievedArgument;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(address);
    servaddr.sin_port = htons(atoi(port));
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    while (true)
    {
        len = sizeof(cliaddr);  
        
        n = recvfrom(sockfd, &recievedArgument, sizeof(float), 0, (struct sockaddr *)&cliaddr, &len);
        if (n <= 0)
        {
            printf("42?\n");        
            exit(1);
        }
        
        printf("Received argument: %f \n", recievedArgument);
        
        float result = 2.0f * ((1.0f - cosf(2.0f * recievedArgument)) / 2.0f) - ((1.0f + cosf(2.0f * recievedArgument)) / 2.0f);
        
        printf("Sending back: %f \n", result);
        
        sendto(sockfd, &result, sizeof(float), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: server_udp <IP address> <port>\n");
        exit(1);
    }

    printf("\nListening for incoming connections on %s:%s...\n\n", argv[1], argv[2]);
    startServer(argv[1], argv[2]);
}
