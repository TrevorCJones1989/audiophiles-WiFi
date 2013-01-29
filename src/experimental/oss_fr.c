#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>

int fd_out;
int sample_rate = 48000;

/*
	This code will read the file "oss_data.txt"
	The file should be one integer per line
	every 1024 lines represents one sample of sound
	
	This put each segmment in an array
	and pass that array to the /dev/dsp device to play
	
	it is meant to demonstrate how to use oss
	this code in it's current form should not end up in the final project!
*/

FILE *fp;
static void write_file(void){
	int bufferSize = 1024;
	short buf[bufferSize];
	
	int temp;
	int index = 0;
	while(feof(fp) == 0){
		if(index >= bufferSize){
			//write the buffer
			if (write (fd_out, buf, sizeof (buf)) != sizeof (buf)) {
				perror ("Audio write");
				exit (-1);
    			}
			index = 0;
		} else {
			//read from file
			fscanf(fp, "%i\n", &temp);
			buf[index] = temp;
			index++;
		}

	}
	fclose(fp);
	
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

int main (int argc, char *argv[]) {
	fp = fopen("oss_data.txt", "r");
	if(fp == NULL){
		puts("Cannot open test file.");
		fclose(fp);
		exit(-1);
	}

	//Use /dev/dsp as the default device because the system administrator may select the device using the Bad xlink 'ossctl' program or some other methods
	char *name_out = "/dev/dsp";

	//It's recommended to provide some method for selecting some other device than the default. We use command line argument but in some cases an environment variable or some configuration file setting may be better.
	if (argc > 1)
		name_out = argv[1];

	//It's mandatory to use O_WRONLY in programs that do only playback. Other modes may cause increased resource (memory) usage in the driver. It may also prevent other applications from using the same device for recording at the same time.
	fd_out = open_audio_device (name_out, O_WRONLY);

	/*
	while (1)
		write_sinewave();*/

	write_file();

	exit (0);
}
