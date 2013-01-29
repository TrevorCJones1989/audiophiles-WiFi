#ifndef __AUDIOSTREAM_H__
#define __AUDIOSTREAM_H__

#include <QThread>
#include <string>
extern "C"{
	#include "watworkers.h"
}
class AudioStream : public QThread
{
	Q_OBJECT
public:
	~AudioStream();
	AudioStream(int fileMode);
	void run();
	bool isReading();
	bool isWriting();
	void setVolume(int vol);
	void setBass(int vol);
	void setTreble(int vol);
signals:

private:
	int fileDescriptor;
	int fileDescriptorMixer;
	socketInfo  * socketInformation;
	char * strToCharPtr(std::string s);
	int fileMode;
};

#endif // __AUDIOSTREAM_H__
