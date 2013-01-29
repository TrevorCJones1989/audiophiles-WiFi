#ifndef WATWORKERS_H_
#define WATWORKERS_H_

#include "watconstants.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>
#include <sys/select.h>

//all the information about a socket
typedef struct socketInfo{
	int socket;
	unsigned int slen;
	struct sockaddr_in si_me;
	struct sockaddr_in si_other;
}socketInfo;

//listens for udp packets
//processes received packets and puts them on the packetQueue
void networklisten_and_audiowrite(struct socketInfo* recvSocket, int file_descriptor);

//retrieves packets from packetQueue
//processes them and sends them out
void audioread_and_networksend(struct socketInfo* recvSocket, int file_descriptor);

//opens a device for OSS audio
int open_audio_device (char *name, int mode);

//opens the mixer device
int open_mixer(char *name, int mode);

//creates a socket that can receive on the recvPort
struct socketInfo* prepareReceiveSocket(int recvPort);

//creates a socket that will send to ip_addr on sendPort
struct socketInfo* prepareSendSocket(int sendPort, char* ip_addr);

//Changes volume
int changeVolume(int file_descriptor, int level);
int changeBass(int file_descriptor, int level);
int changeTreble(int file_descriptor, int level);
#endif
