#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void calculateUsingServer(char *address, char *port, float startFrom, float calculateTo, float delta)
{
    // Structure for server address
    struct sockaddr_in servaddr;
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(address);
    servaddr.sin_port = htons(atoi(port));
    
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Argument buffer
    float currentArgument = startFrom;

    // Result buffer
    float result;

    // While argument in the proper range
    while(currentArgument <= calculateTo)
    {
        // Sending argument to the server
        sendto(sockfd, &currentArgument, sizeof(float), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

        // Recieving result from the server 
        recvfrom(sockfd, &result, sizeof(float), 0, NULL, NULL);
        printf("Received result: %f for argument %f \n", result, currentArgument);
        
        // Increasing argument by delta for the next step
        currentArgument += delta;
    } 
}

int main(int argc, char **argv)
{
    // If no console arguments provided
    if (argc != 3)
    {
        printf("Usage: client_udp <IP address> <port>\n");
        exit(1);
    }

    // Input data
    float startFrom, calculateTo, delta;
    
    printf("Lower bound: ");
    scanf ("%f", &startFrom);
    
    printf("Upper bound: ");
    scanf ("%f", &calculateTo);
    
    printf("Step: ");
    scanf ("%f", &delta);
    
    calculateUsingServer(argv[1], argv[2], startFrom, calculateTo, delta);
    
    return 0; 
}
