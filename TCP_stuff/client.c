#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 



int calculate(float **result, float startFrom, float calculateTo, float delta)
{

    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    memset(recvBuff, '0',sizeof(recvBuff));
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
    
    write(sockfd, &startFrom, sizeof( float )); 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;


	float bufferX = startFrom;
	int iterationCounter = 0;

	size_t vectorSize = ceilf((calculateTo - startFrom)/delta); 
	*result = malloc(vectorSize * sizeof(float) );


	//printf("%i\n", sizeof(result));
	//printf("Start from %e \n", startFrom);
	//printf("calculate to %e \n", calculateTo);
	//printf("delta %e \n", delta);
	//printf("bufferX %e \n", bufferX);
	//printf("vectorSize %i \n", vectorSize);

	while(bufferX <= calculateTo)
	{
		(*result)[iterationCounter] = 2 * ((1 - cos(2 * bufferX ))/2) - ((1 + cos(2 * bufferX)) / 2);
		iterationCounter++;
		bufferX += delta;
	}
}

int main(int argc, char *argv[])
{

    float startFrom, calculateTo, delta;

	printf("Введите нижнюю границу диапазона:");
	scanf ("%e", &startFrom);

	printf("Верхнюю нижнюю границу диапазона:");
	scanf ("%e", &calculateTo);
	
	printf("Введите шаг рассчёта:");
	scanf ("%e", &delta);

	float * resultArray;
	
	calculate(&resultArray, startFrom, calculateTo, delta);
	return 0;
}
