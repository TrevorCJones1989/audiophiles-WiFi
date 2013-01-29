#include "audiostream.h"
#include <string>
#include <QDebug>
AudioStream::AudioStream(int fileM){
	QThread::setTerminationEnabled(true);
	fileMode = fileM;
	//Open hardware audio device for reading or writing.	
	fileDescriptor = open_audio_device(strToCharPtr("/dev/dsp"), fileMode);
	fileDescriptorMixer = open_mixer(strToCharPtr("/dev/mixer"), fileMode);
	if (fileMode == O_RDONLY){
		//Opening socket
		socketInformation = prepareSendSocket(SOUND_PORT, strToCharPtr(MULTICAST_GROUP));
	}
	else if (fileMode == O_WRONLY){
		socketInformation = prepareReceiveSocket(SOUND_PORT);
		
	}
	else{
		qDebug()<< "broken thread";
		return;
	}
	
}
AudioStream::~AudioStream(){
	close(fileDescriptorMixer);
	close(fileDescriptor);
	close(socketInformation->socket);
	}

void AudioStream::run(){
	if (fileMode ==  O_RDONLY){
		audioread_and_networksend(socketInformation, fileDescriptor);
	}
	else if(fileMode == O_WRONLY){
		networklisten_and_audiowrite(socketInformation, fileDescriptor);
	}
}

char * AudioStream::strToCharPtr(std::string s){
	std::string car = s;
	return (char*)car.c_str();
}
bool AudioStream::isReading(){
	if (fileMode == O_RDONLY){
		return true;
	}
	else{
		return false;
	}
}

bool AudioStream::isWriting(){
	if (fileMode == O_WRONLY){
		return true;
	}
	else{
		return false;
	}
}
void AudioStream::setVolume(int vol){
	//If writing change volume otherwise do nothing
	if (fileMode == O_WRONLY){
		changeVolume(fileDescriptorMixer, vol);
	}
}
void AudioStream::setBass(int vol){
	//If writing change volume otherwise do nothing
	//Unavailable based on Sound Card
	int f;
	if (fileMode == O_WRONLY){
		f =changeBass(fileDescriptorMixer, vol);
	}
}
void AudioStream::setTreble(int vol){
	//If writing change volume otherwise do nothing
	//Unavailable based on Sound Card
	int f;
	if (fileMode == O_WRONLY){
		f =changeTreble(fileDescriptorMixer, vol);
	}
}
// place your code here
