#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <QMainWindow>
#include "buttonthread.h"
#include "audiostream.h"
extern "C"{
#include "leddrv.h"
#include "buttondrv.h"
}

//Namespace
namespace Ui {
	class MainWindow;
}
//Constructor:
class MainWindowImpl : public QMainWindow
{
	Q_OBJECT
//Non slot public function
public:
	explicit MainWindowImpl(QWidget *parent = 0);
	//LED Functionality
	void wifiStrength();
	~MainWindowImpl();
public slots:
	//Slots
		//Wifi Tab
	void connectWifi();
	void disconnectWifi();
	void cmbWifiRefresh();
		//Equalizer Tab
	void getSVEQValue(int SVMEQ);
	void getSBassValue(int SBass);
	void getSMidValue(int SMid);
	void getSTrebleValue(int SBass);
		//Connections Tab
	void chkTransReceive(int in);
	void chkTransSend(int in);
		//Button Functionality
	void setButtons(int btnMask);
private:
    Ui::MainWindow *ui;
    ButtonThread *thread;
    int EQToggle;
    AudioStream *ASthread;
 };
#endif



