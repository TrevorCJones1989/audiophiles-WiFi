#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>

#define SENDPORT 12345
#define SEND_IP "192.168.0.187"
#define BUFLEN 1024

int fd_in;
int sample_rate = 48000;
struct sockaddr_in si_other;
int s, slen=sizeof(si_other);
char buf[BUFLEN * 2];
int num = 0;

FILE *fp;

void diep(char *s)
{
perror(s);
exit(1);
}
void doSend(char* toSend)
{
		printf("Sending packet %d\n", num);
		sprintf(buf, "This is packet %d\n", num++);
		//times 2 because a short is two characters
		int sentBytes = sendto(s, toSend, BUFLEN * 2, 0, (struct sockaddr *) &si_other, slen);
		if (sentBytes ==-1) {
			diep("sendto()");
		}

}
static int open_audio_device (char *name, int mode) {
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

void process_input (void) {
	int bufferSize = 1024;

  	short buffer[BUFLEN];
	int l, i, level;
 
	//read a block of audio samples with proper error checking
  	if ((l = read (fd_in, buffer, sizeof (buffer))) == -1) {
      		perror ("Audio read");
      		exit (-1);		/* Or return an error code */
    	}

	//we are using mono 16bit. Stereo needs to be interleaved, more difficult
  	l = l / 2;

	//checking levels stuff
	level = 0;
  	for (i = 0; i < l; i++) {
       		int v = buffer[i];

      		if (v < 0)
			v = -v;		/* abs */

      		if (v > level)
			level = v;
    	}
	
  	level = (level + 1) / 1024;
	
	//save to file
	int index;
	int charBuffIndex = 0;
	char temp[BUFLEN * 2];
	for(index = 0; index < BUFLEN * 2; index += 2){
		//fprintf(fp, "%i\n", buffer[charBuffIndex]);
		short tempshort = buffer[charBuffIndex++];
		//short tempshort = 7192;
		//add the last 8 bits
		temp[index] = tempshort & 0xFF;
		//move the first 8 bits into the last 8 bits spot
		tempshort = tempshort >> 8;
		//save the next value
		temp[index + 1] = tempshort & 0xFF;
	}


	doSend(temp);

	int iindex;
	for(iindex = 0; iindex < BUFLEN; iindex++){
		printf("%i,", buffer[iindex]);
	}
	printf("\n"); 
	//exit(0);
	//end save to file
	

	//linear scale, real world(dBD) is log
  	for (i = 0; i < level; i++)
    		printf ("*");
  	for (i = level; i < 32; i++)
    		printf (".");
  	printf ("\r");
  	fflush (stdout);
}



void prepareudpsender(){
	printf("UDP Sender is starting.\n");

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
		diep("socket");
	}

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(SENDPORT);

	if (inet_aton(SEND_IP, &si_other.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}


}
void closeudpsender(void)
{
	close(s);

	return;
}


void main()
{
	prepareudpsender();
	fp = fopen("oss_data1.txt", "w");
	if(fp == NULL){
		puts("Cannot open test file.");
		fclose(fp);
		exit(-1);
	}

	char *name_in = "/dev/dsp";
	
   	fd_in = open_audio_device (name_in, O_RDONLY);

	int index;
	for(index = 0; index < 400; index++){
		process_input();
	}
    		
	printf("\n");
	fclose(fp);
	closeudpsender();
  	exit (0);


}

