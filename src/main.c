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

#include "watconstants.h"
#include "watworkers.h"

int main(int argc, char *argv[]){
	char watmode = 0;
	if (argc > 1){
    		watmode = *argv[1]; 
	}

	if(watmode == 0){
		printf("You need to specifiy what mode you want.\n");
	} else if(watmode == 'r'){ //read
		struct watArgs *wArgs = (struct watArgs*)malloc(sizeof(watArgs));

		//setup the file to read
		wArgs->file_descriptor = open_audio_device("/dev/dsp", O_RDONLY);
		//get the socket to send to the desired ip
		wArgs->socketInformation = prepareSendSocket(SOUND_PORT, SEND_IP);
		//start the read and send thread
		pthread_t audioread_networksend_id;
		pthread_create(&audioread_networksend_id, NULL, (void *) &audioread_and_networksend, (void *) wArgs);

		pthread_join(audioread_networksend_id, NULL);
		//close the file
		close(wArgs->file_descriptor);
		//close the socket
		close(wArgs->socketInformation->socket);
	} else if(watmode == 'w'){ //write
		struct watArgs *wArgs = malloc(sizeof(watArgs));
		//setup the file for write
		wArgs->file_descriptor = open_audio_device("/dev/dsp", O_WRONLY);
		//get the socket to listen on the sound part
		wArgs->socketInformation = prepareReceiveSocket(SOUND_PORT);
		//start the listen and write thread
		pthread_t networklisten_audiowrite_id;
		pthread_create(&networklisten_audiowrite_id, NULL, (void *) &networklisten_and_audiowrite, (void *) wArgs);

		/*
			sleep(5);
			pthread_cancel(networklisten_audiowrite_id);
		*/
		pthread_join(networklisten_audiowrite_id, NULL);
		//close the file
		close(wArgs->file_descriptor);
		//close the socket
		close(wArgs->socketInformation->socket);
	} else {
		printf("Don't understand mode %c \n", watmode);
	}

	return 0;
}
