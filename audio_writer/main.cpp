#include "wifi.h"



int main(){
	wifi w;
//	w.bring_interface_up();
	//wait a few seconds before initiating scan;
//	sleep(10);
//	w.get_aps();
	w.connect_to_ap("Smooth_Criminals_Internet");
	return 0;
}
