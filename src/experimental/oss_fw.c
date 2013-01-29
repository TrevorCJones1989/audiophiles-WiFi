#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>

/*
	This code will write to the file "oss_data.txt"
	It will take one sample of sound as 1024 pieces
	it will print each integer on a seperate line
	
	it will stop after 400 iterations (a few seconds)
	
	it is meant to demonstrate how to use oss
	this code in it's current form should not end up in the final project!
*/

int fd_in;
int sample_rate = 48000;

FILE *fp;
 
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

  	short buffer[bufferSize];
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
	for(index = 0; index < bufferSize; index++){
		fprintf(fp, "%i\n", buffer[index]);
	}
	//end save to file
	

	//linear scale, real world(dBD) is log
  	for (i = 0; i < level; i++)
    		printf ("*");
  	for (i = level; i < 32; i++)
    		printf (".");
  	printf ("\r");
  	fflush (stdout);
}

int main (int argc, char *argv[]) {

	fp = fopen("oss_data.txt", "w");
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
  	exit (0);
}
