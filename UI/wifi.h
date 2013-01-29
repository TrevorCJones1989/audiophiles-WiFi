#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <string.h>
#include <sstream>
#include <sys/socket.h>
#include <netdb.h>

class wifi{
	private:
		bool interface_status;
	public:
		void bring_interface_up();
		wifi();
		std::vector<std::string> get_aps();
		void connect_to_ap(std::string essid);
		std::string get_ip();
		void disconnect_wifi();
};

wifi::wifi(){
	interface_status = false;
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


std::string wifi::get_ip(){
	char name[128];
	gethostname(name, sizeof(name));

	gethostbyname(name);
	hostent *ip = gethostbyname(name);
	char ip_addr[128];
	sprintf(ip_addr, "%c.%c.%c.%c\n", ip->h_addr[0], ip->h_addr[1], ip->h_addr[2], ip->h_addr[3]);
	return std::string(ip_addr);
}

void wifi::connect_to_ap(std::string essid){
	bring_interface_up();
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
	if(interface_status == false){
		FILE *file = popen("ifconfig wlan0 up", "r");
		char buffer[100000];
		std::string line;
		fscanf(file, "%s", buffer);
		while( fgets(buffer, 1000, file)){
			line.append(buffer);
		}
		pclose(file);
		interface_status = true;
	}
}

void wifi::disconnect_wifi(){
	FILE *file = popen("ifconfig wlan0 down", "r");
	char buffer[100000];
	std::string line;
	fscanf(file, "%s", buffer);
	while( fgets(buffer, 1000, file)){
		line.append(buffer);
	}
	pclose(file);
	interface_status = false;
}

