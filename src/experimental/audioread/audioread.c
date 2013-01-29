#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include <mcheck.h>

#include "udplistener.h"


int main(){

	//create udp listener thread
	pthread_t listen_id;
	pthread_create(&listen_id, NULL, (void *) &udplistener, NULL);

	//wait for the thread
	pthread_join(listen_id, NULL);

	return 0;
}




