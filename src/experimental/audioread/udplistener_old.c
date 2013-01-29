#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "udplistener.h"

#define LISTENPORT 12345
#define MAXRETURN 50

void udplistener(void){
	printf("UDP Listener is starting.\n");

	//buffer to hold messages
	char message[MSGMAXLEN];

	//address
	struct sockaddr_in sin;
	unsigned int sin_len;
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(LISTENPORT);

	//create the socket for UDP
	int socket_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//bind the socket to the port
	bind(socket_descriptor, (struct sockaddr*) &sin, sizeof(sin));

	int stop = 0;
	while(stop == 0){
		//get the data
		//change the sin address to be the address of the client
		sin_len = sizeof(sin);
		int bytesRx = recvfrom(socket_descriptor, message, MSGMAXLEN, 0,
						(struct sockaddr *) &sin, &sin_len);
		//make it null terminated so the string functions work
		message[bytesRx] = 0;
		//printf("Message received (%d bytes): \n\n'%s'\n", bytesRx, message);
		//extract the value from the message
		char msgTemp[MSGMAXLEN];
		//copy the message
		strcpy(msgTemp, message);

		printf("%s\n", msgTemp);

	}
	close(socket_descriptor);
	return;
}

