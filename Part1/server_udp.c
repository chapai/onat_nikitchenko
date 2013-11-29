#include <math.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

//just for false and true
#include <stdbool.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void startServer(char *address, char *port)
{
    int sockfd, n;
    // Structures for client and server address
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    // Buffer for recieved arguments
    float recievedArgument;
    
    // Creating UDB socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Itiating server address structure by zzeros
    bzero(&servaddr, sizeof(servaddr));
    
    // Socket type
    servaddr.sin_family = AF_INET;

    // Socket address (IPv4)
    servaddr.sin_addr.s_addr = inet_addr(address);

    // Socket port
    servaddr.sin_port = htons(atoi(port));

    // Binding socket on address
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    // Starting endless cycle
    while (true)
    {
        len = sizeof(cliaddr);  
        
        // Waiting for data
        n = recvfrom(sockfd, &recievedArgument, sizeof(float), 0, (struct sockaddr *)&cliaddr, &len);

        // If recieve error error
        if (n <= 0)
        {
            printf("42?\n");        
            exit(1);
        }
        
        printf("Received argument: %f \n", recievedArgument);
        
        // Calculating result
        float result = 2.0f * ((1.0f - cosf(2.0f * recievedArgument)) / 2.0f) - ((1.0f + cosf(2.0f * recievedArgument)) / 2.0f);
        
        printf("Sending back: %f \n", result);
        
        // Sending result to the client
        sendto(sockfd, &result, sizeof(float), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    }
}

int main(int argc, char **argv)
{
    // If no console arguments provided
    if (argc != 3)
    {
        printf("Usage: server_udp <IP address> <port>\n");
        exit(1);
    }

    printf("\nListening for incoming connections on %s:%s...\n\n", argv[1], argv[2]);
    startServer(argv[1], argv[2]);
}
