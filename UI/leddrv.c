#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "leddrv.h"
//#include <linux/delay.h>
/*			LUDR	Use an array to map!!
	0		3210	Physical Light Layout
     2	   3
	1
*/
#define LED0_MASK 0x01
#define LED1_MASK 0x02
#define LED2_MASK 0x04
#define LED3_MASK 0x08

int LEDMAP[4] = {LED_BIT_0, LED_BIT_1, LED_BIT_2, LED_BIT_3};

int ledval;
int fd_LED;

//BUTTONS     R D U L
int MAP[4] = {3,1,0,2};
//INDEX       0 1 2 3
//PhysLights  3 2 1 0


int LEDDrv_init(){
	fd_LED = open("/dev/GPIO-Control", 0);
	int p;
	for (p=0; p<4; p++){
		ioctl(fd_LED, LED_OFF, p);	
	}
return 0;
}

void LEDDrv_cleanup(){
	//turn them all off
	int p;
	for (p=0; p<4; p++){
		ioctl(fd_LED, LED_OFF, p);	
	}
	close(fd_LED);
}
int LEDDrv_setState(int mask){
	ledval = mask;
	int p;
	if (mask == -1){ //Special command to turn off all LEDs
		for (p=0; p<4; p++){
			ioctl(fd_LED, LED_OFF, p);	
		}
		return 0;
	}
	//End

	int i;
	for (i=0; i<4; i++){
		//turn off if 0
		if (((ledval & (1<<LEDMAP[i])) >> LEDMAP[i]) == 0){
			ioctl(fd_LED, LED_OFF, LEDMAP[i]);
		}
		//turn on if 1
		else{
			ioctl(fd_LED, LED_ON, LEDMAP[i]);
		}
	}
	return 0;
}

/*
BitMasks
	Store mulitple binary conditions in a single value
	Bitwise Operators	
		| OR	- Sets bits
		& AND	- Clear bits
		~ NOT	- inverting
		^ XOR	- selectively invert
	Example:
		Name	bit	Mask
		LED0	0	0x01	000...01
		LED1	1	0x02	000...10
		LED2	2	0x04	000..100
		LED3	3	0x08	000.1000
	Example cont:
		int ledval = (1<<LED1);
		LEDDrv_setState(ledval);
		*Switch states from LED1 to LED0*
		ledval |= (1<<LED0);
		LEDDrv_setState(ledval);
	Example cont: turn off all but LED2
		ledval &= (1<<LED2)
	Example cont: leave everything and turn off LED2
		ledval &= ~(1<<LED2)
	Example cont: Check if LED1 on
		if (ledval & (1<<LED1)){printf("yep");}

	ioctl(fd, <on?>, <led#>);
		{0 1}  {0 1 2 3}
		Returns 0 for success.
*/
