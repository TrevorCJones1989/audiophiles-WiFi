#include "watworkers.h"

static int bufferLength = 1024;
static int sample_rate = 48000;


//listens for udp packets
//processes received packets and puts them on the packetQueue
void networklisten_and_audiowrite(struct socketInfo* recvSocket, int file_descriptor){
	//check that we have a socket

	if(recvSocket == NULL){
		return;
	}

	//used to determine when to end reading
	int endCondition = 0;
	char charBuffer[bufferLength * 2];
	while(endCondition == 0){
		//receive something over the network
		if(recvfrom(recvSocket->socket, charBuffer, bufferLength * 2, 0, (struct sockaddr *) &(recvSocket->si_other), &(recvSocket->slen)) == -1){
			perror ("Socket recv");
		      	exit (-1);		/* Or return an error code */
		}

		//we receive a character array, cast it to shorts(device understand shorts)
		short* buffer = (short*)charBuffer;

		#if defined DEBUG
		int i;
		for(i = 0; i < bufferLength; i++)
			printf("%i ", buffer[i]);
		printf("\n");
		#endif

		//write
		int bufferSize = sizeof(short) * bufferLength;
		if (write (file_descriptor, buffer, bufferSize) != bufferSize) {
			perror ("Audio write");
			exit (-1);
	    	}

		#if defined DEBUG
			#if defined ONESHOT
			return;
			#endif
		#endif

	}
	return;
}


void audioread_and_networksend(struct socketInfo* sendSocket, int file_descriptor){
	//check that we have a socket
	if(sendSocket == NULL){
		return;
	}

	int l;

	//used to determine when to end reading
	int endCondition = 0;
	short shortBuffer[bufferLength];
	while(endCondition == 0){
		//read a block of audio samples with proper error checking
	  	if ((l = read (file_descriptor, shortBuffer, sizeof (shortBuffer))) == -1) {
	      		perror ("Audio read");
	      		exit (-1);		/* Or return an error code */
	    	}

		#if defined DEBUG
		int i;
		for(i = 0; i < bufferLength; i++)
			printf("%i ", shortBuffer[i]);
		printf("\n");
		#endif

		//the device outputs shorts, cast it to characters to send
		char* buffer = (char*)shortBuffer;

		//send the packet
		if (sendto(sendSocket->socket, buffer, bufferLength * 2, 0, (struct sockaddr *) &(sendSocket->si_other), sendSocket->slen) ==-1) {
			perror ("Sending");
      			exit (-1);		/* Or return an error code */
		}

		#if defined DEBUG
			#if defined ONESHOT
			return;
			#endif
		#endif
	}
	return;
}

int open_mixer(char *name, int mode){
	int fd;
	if((fd = open (name, mode, 0)) == -1) {
		perror (name);
		exit (-1);
	}
	return fd;
}


int open_audio_device (char *name, int mode) {
	int tmp, fd;
	if((fd = open (name, mode, 0)) == -1) {
		perror (name);
		exit (-1);
	}
	//set the sample format
   	tmp = AFMT_S16_NE;		/* Native 16 bits */
  	if (ioctl (fd, SNDCTL_DSP_SETFMT, &tmp) == -1) {
      		perror ("SNDCTL_DSP_SETFMT");
      		exit (-1);
    	}

  	if (tmp != AFMT_S16_NE) {
		fprintf (stderr, "The device doesn't support the 16 bit sample format.\n");
      		exit (-1);
    	}

	//set the number of channels
   	tmp = 1;
  	if (ioctl (fd, SNDCTL_DSP_CHANNELS, &tmp) == -1) {
      		perror ("SNDCTL_DSP_CHANNELS");
      		exit (-1);
    	}

  	if (tmp != 1) {
		fprintf (stderr, "The device doesn't support mono mode.\n");
		exit (-1);
    	}

	//set the sample rate
  	sample_rate = 48000;
  	if (ioctl (fd, SNDCTL_DSP_SPEED, &sample_rate) == -1) {
      		perror ("SNDCTL_DSP_SPEED");
      		exit (-1);
    	}
  	return fd;
}

int changeVolume(int file_descriptor, int level){
	if(level > 100){
		level = 100;
	} else if(level < 0){
		level = 0;
	}

	//bitmask for left/right channel
	int newLevel = (level)|(level<<8);
	int p = ioctl(file_descriptor, MIXER_WRITE(SOUND_MIXER_VOLUME), &newLevel);
	return p;
}
int changeBass(int file_descriptor, int level){
	if(level > 100){
		level = 100;
	} else if(level < 0){
		level = 0;
	}
	//bitmask for left/right channel
	int newLevel = (level)|(level<<8);
	int p = ioctl(file_descriptor, MIXER_WRITE(SOUND_MIXER_BASS), &newLevel);
	return p;
}
int changeTreble(int file_descriptor, int level){
	if(level > 100){
		level = 100;
	} else if(level < 0){
		level = 0;
	}
	//bitmask for left/right channel
	int newLevel = (level)|(level<<8);
	int p = ioctl(file_descriptor, MIXER_WRITE(SOUND_MIXER_TREBLE), &newLevel);
	return p;
}



struct socketInfo* prepareReceiveSocket(int recvPort){
	//network setup
	struct sockaddr_in si_me, si_other;
	struct ip_mreq mreq;
	int s;
	unsigned int slen=sizeof(si_other);

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) {
		perror ("Socket recv");
	      	exit (-1);		/* Or return an error code */
	}

	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(recvPort);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me))==-1) {
		perror ("Socket bind");
	      	exit (-1);		/* Or return an error code */
	}

	/* use setsockopt() to request that the kernel join a multicast group */
	mreq.imr_multiaddr.s_addr=inet_addr(MULTICAST_GROUP);
	mreq.imr_interface.s_addr=htonl(INADDR_ANY);
	if (setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
		perror("setsockopt");
		exit(1);
	}

	//create the struct to return
	struct socketInfo* recvSocket = malloc(sizeof(socketInfo));
	recvSocket->socket = s;
	recvSocket->slen = slen;
	recvSocket->si_me = si_me;
	recvSocket->si_other = si_other;
	
	return recvSocket;
}

struct socketInfo* prepareSendSocket(int sendPort, char* ip_addr) {
	//network setup
	struct sockaddr_in si_other;
	int s, slen=sizeof(si_other);

	//prepare socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
		perror ("Socket send");
	      	exit (-1);		/* Or return an error code */
	}

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(sendPort);

	if (inet_aton(ip_addr, &si_other.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	//create the struct to return
	struct socketInfo* sendSocket = malloc(sizeof(socketInfo));
	sendSocket->socket = s;
	sendSocket->slen = slen;
	sendSocket->si_other = si_other;
	
	return sendSocket;

}
