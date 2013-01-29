  #include <arpa/inet.h>
  #include <netinet/in.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <unistd.h>

  #define BUFLEN 1024
  #define NPACK 10
  #define PORT 12345

#include <fcntl.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>

int fd_out;
int sample_rate = 48000;
FILE *fp;

static int open_audio_device (char *name, int mode);



  void diep(char *s)
  {
    perror(s);
    exit(1);
  }

  void udplistener(void)
  {
		fp = fopen("oss_data2.txt", "a");
		if(fp == NULL){
			puts("Cannot open test file.");
			fclose(fp);
			exit(-1);
		}
    struct sockaddr_in si_me, si_other;
    int s, slen=sizeof(si_other);
    char buf[BUFLEN * 2];

    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
      diep("socket");

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me))==-1)
        diep("bind");


	//sound stuff
	char *name_out = "/dev/dsp";
	fd_out = open_audio_device (name_out, O_WRONLY);
	
    short tempshort[BUFLEN];

	//testcode
	int numStores = 95;
	short datastore[numStores * BUFLEN];
	int stores = 0;
	//testcode
	
	int buffers_cached_so_far = 0;
	int permaindex = 0;
	int k = 0;
    while(1 == 1) {
	int recvBytes = recvfrom(s, buf, BUFLEN * 2, 0, (struct sockaddr *) &si_other, &slen);
      if (recvBytes ==-1) {
        diep("recvfrom()");
	}

	int ii;
	int tempIndex = 0;
	for(ii = 0; ii < BUFLEN * 2; ii += 2){
	

		short tempest = buf[ii + 1];
		tempest = tempest << 8;
		tempshort[tempIndex++] = tempest | buf[ii];
		//fprintf(fp, "%i\n", tempshort[tempIndex-1]);
		//printf("%c %c %i\n", buf[ii], buf[ii + 1], tempshort[tempIndex]);
	}
			if (write (fd_out, tempshort, sizeof (tempshort)) != sizeof (tempshort)) {
						perror ("Audio write");
						exit (-1);
		    			}	

	
	int iindex;
	for(iindex = 0; iindex < BUFLEN; iindex++){
		printf("%i,", tempshort[iindex]);
	}
	printf("\n"); 
      printf("Received packet from %s:%d\n Data: %i %i %i\n\n", 
             inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), tempshort[0], tempshort[1], tempshort[2]);
    }

		fclose(fp);

close(s);
return;
}




//The open_audio_device opens the audio device and initializes it for the required mode.

static int open_audio_device (char *name, int mode) {
	int tmp, fd;

	if ((fd = open (name, mode, 0)) == -1) {
		perror (name);
		exit (-1);
    }

	//Setup the device. Note that it's important to set the sample format, number of channels and sample rate exactly in this order. Some devices depend on the order.

	//Set the sample format

	tmp = AFMT_S16_NE;		/* Native 16 bits */
	if (ioctl (fd, SNDCTL_DSP_SETFMT, &tmp) == -1) {
		perror ("SNDCTL_DSP_SETFMT");
		exit (-1);
    }

	if (tmp != AFMT_S16_NE) {
		fprintf (stderr, "The device doesn't support the 16 bit sample format.\n");
		exit (-1);
    }
	
	//Set the number of channels

	tmp = 1;
	if (ioctl (fd, SNDCTL_DSP_CHANNELS, &tmp) == -1) {
		perror ("SNDCTL_DSP_CHANNELS");
		exit (-1);
    }

	if (tmp != 1) {
		fprintf (stderr, "The device doesn't support mono mode.\n");
		exit (-1);
    }
	//Set the sample rate

	sample_rate = 48000;
	if (ioctl (fd, SNDCTL_DSP_SPEED, &sample_rate) == -1) {
		perror ("SNDCTL_DSP_SPEED");
		exit (-1);
    }
	
	//No need for error checking because we will automatically adjust the signal based on the actual sample rate. However most application must check the value of sample_rate and compare it to the requested rate.
	//Small differences between the rates (10% or less) are normal and the applications should usually tolerate them. However larger differences may cause annoying pitch problems (Mickey Mouse).
	
	return fd;
}
