#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <string.h>
#include <sstream>

class wifi{
	private:

	public:
		void bring_interface_up();
		wifi();
		std::vector<std::string> get_aps();
		void connect_to_ap(std::string essid);

};

wifi::wifi(){

}

std::vector<std::string> wifi::get_aps(){
	int retry = 0;
	std::vector<std::string> essids;
	std::string new_line = "No scan results";
	while(new_line.find("No scan results") != std::string::npos || retry == 5){
		FILE *file = popen("iwlist wlan0 scan", "r");
		char buffer[100000];
		std::string line;
		fscanf(file, "%s", buffer);
		while( fgets(buffer, 1000, file)){
			line.append(buffer);
		}
		pclose(file);
		if(line.find("No scan results") == std::string::npos){
			do{
				new_line = line.substr(0, line.find("\n"));
				line = line.substr(line.find("\n")+2);
				if(new_line.find("ESSID:") != std::string::npos){
					int length = new_line.length();
					std::string essid = new_line.substr(new_line.find("\"")+1);	
					essids.push_back(essid.erase(essid.length()-1));	
				}
			}while(line.size() > 0 || new_line.find("No scan results") != std::string::npos);
		}
		else{
			retry++;
		}
	}
	return essids;
} 

void wifi::connect_to_ap(std::string essid){
	char buf[100];
	sprintf(buf, "iwconfig wlan0 essid %s\n", essid.c_str());
	FILE *file = popen(buf, "r"); 	
	FILE *dhcp_file = popen("udhcpc -i wlan0", "r");
	char buffer[100000];
	std::string line;
	fscanf(dhcp_file, "%s", buffer);
	while( fgets(buffer, 1000, dhcp_file)){
		line.append(buffer);
	}	
	pclose(file);
}

void wifi::bring_interface_up(){
	FILE *file = popen("ifconfig wlan0 up", "r");
	char buffer[100000];
	std::string line;
	fscanf(file, "%s", buffer);
	while( fgets(buffer, 1000, file)){
		line.append(buffer);
	}
	pclose(file);
}
