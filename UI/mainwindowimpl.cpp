#include "mainwindowimpl.h"
#include "wifi.h"
#include <vector>
#include "ui_audiophileswindow.h"
#include "buttonthread.h"
#include <QDebug>

extern "C"{
#include "leddrv.h"
#include "buttondrv.h"
}
wifi w;
//Constructor
MainWindowImpl::MainWindowImpl(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	EQToggle = 0;
	ui->setupUi(this);
	thread = new ButtonThread();
	
	//Add connections here
	QObject::connect(ui->btnConnectWifi, SIGNAL(clicked()), this, SLOT(connectWifi()));
	QObject::connect(ui->btnDisconnectWifi, SIGNAL(clicked()), this, SLOT(disconnectWifi()));
	//---------QObject::connect(ui->btnWifiRefresh, SIGNAL(clicked()), this, SLOT(cmbWifiRefresh()));
	
	//Equalizer Sliders
	QObject::connect(ui->slideVolEq, SIGNAL(valueChanged(int)), this, SLOT(getSVEQValue(int)));
	QObject::connect(ui->slideBass, SIGNAL(valueChanged(int)), this, SLOT(getSBassValue(int)));
	QObject::connect(ui->slideMid, SIGNAL(valueChanged(int)), this, SLOT(getSMidValue(int)));
	QObject::connect(ui->slideTreble, SIGNAL(valueChanged(int)), this, SLOT(getSTrebleValue(int)));
	
	//Devices
		//Transmit Check Boxes
	QObject::connect(ui->chkReceiveTransmit, SIGNAL(stateChanged(int)), this, SLOT(chkTransReceive(int)));
	QObject::connect(ui->chkSendTransmit, SIGNAL(stateChanged(int)), this, SLOT(chkTransSend(int)));
	
	//Physical Buttons for Volume
	QObject::connect(thread, SIGNAL(buttonsChanged(int)), this, SLOT(setButtons(int)));
	
	
	//Initializations
		//Init Wifi
		//------------cmbWifiRefresh();
		//Init LEDS
		LEDDrv_init();
		//Init Buttons
		//ButtonDrv_init();

	thread->start();

}
//Destructor
MainWindowImpl::~MainWindowImpl()
{
	thread->stopThreads = true;
	delete ui;
	LEDDrv_cleanup();
	//ButtonDrv_cleanup();
	if (thread) {
        thread->wait(1);
        thread->terminate();
        delete thread;
    }
}

//Functionality:

//===Wifi Tab
	//Connect to current value of cmbWifi
void MainWindowImpl::connectWifi(){
		//Get current value of cmbWifi
	QString current = ui->cmbWifi->currentText();
	
		//Connect to current Network
	w.connect_to_ap(current.toStdString());
		//Set current value of cmbWifi to lblNetwork
	ui->lblNetwork->setText(current);
	
	/*get IP and set to lblIP
	char* car = (char*)(w.get_ip().c_str());
	QString ip = car;
	ui->lblIP->setText(ip);*/
		
		//Show Wifi Strength
	wifiStrength();
}
	//Disconnect from current value in cmbWifi
void MainWindowImpl::disconnectWifi(){
		//Gets the text to disconnect from if needed
			//QString current = ui->lblNetwork->text();
		//Say disconnected
	ui->lblNetwork->setText("disconnected");
	ui->lblIP->setText("0.0.0.0");
		//Set Wifi Strength to 0
	LEDDrv_setState(0);
		//Disconnect
	w.disconnect_wifi();
}

	//Add Wifi connections to cmbWifi
	//Used to Refresh available wifi networks
void MainWindowImpl::cmbWifiRefresh(){
		//Remove all current networks displayed
	int cnt = ui->cmbWifi->count();
	for (int i=0; i<cnt; i++){
		ui->cmbWifi->removeItem(0);
	}
		//Add all new networks
	std::vector<std::string> list = w.get_aps();
	for(int i = 0; i < (signed)list.size(); i++){
		ui->cmbWifi->addItem(list[i].c_str());
	}
}
//===End Wifi Tab

//===Equalizer Tab
	//Volume Slider
void MainWindowImpl::getSVEQValue(int SVMEQ){
	QString val = "";
	val.setNum(SVMEQ);
	ui->lblVolEq->setText(val);
	if(ASthread){
		ASthread->setVolume(SVMEQ);
	}
}
	//Bass Slider
void MainWindowImpl::getSBassValue(int SBass){
	QString val = "";
	val.setNum(SBass);
	ui->lblBass->setText(val);
	/*if(ASthread){
		ASthread->setBass(SBass);
	}*/
}
	//Mid Slider
void MainWindowImpl::getSMidValue(int SMid){
	QString val = "";
	val.setNum(SMid);
	ui->lblMid->setText(val);
}	
	//Treble Slider
void MainWindowImpl::getSTrebleValue(int STreble){
	QString val = "";
	val.setNum(STreble);
	ui->lblTreble->setText(val);
	/*if(ASthread){
		ASthread->setTreble(STreble);
	}*/
}

//===End Equalizer Tab

//===Connections Tab

void MainWindowImpl::chkTransReceive(int in){
	//2 = on checked
	//0 = off unchecked
	if (in ==2){
		ui->chkSendTransmit->setChecked(false);
		ASthread = new AudioStream(O_WRONLY);
		ASthread->start();
		//Initial Volume
		QString vol = ui->lblVolEq->text();
		bool ok;
		int volTemp = vol.toInt(&ok,10);
		ASthread->setVolume(volTemp);
		//Run Receive Audio
	}
	else{
		if (ASthread) {
        	ASthread->wait(1);
        	ASthread->terminate();
        	while (!ASthread->isFinished()){}
        	delete ASthread;
       	}
		//Don't transmit
	}
}

void MainWindowImpl::chkTransSend(int in){
	//2 = on checked
	//0 = off unchecked
	if (in ==2){
		ui->chkReceiveTransmit->setChecked(false);
		ASthread = new AudioStream(O_RDONLY);
		ASthread->start();
		//Run Send Audio 
	}
	else{
		//Kill thread
		//Close Socket
		//Close file descriptor
		if (ASthread) {
        	ASthread->wait(1);
        	ASthread->terminate();
        	while (!ASthread->isFinished()){}
        	delete ASthread;
       	}
		//Don't transmit
	}
}
//==End Connections Tab

//LED Functionality
void MainWindowImpl::wifiStrength(){
	int wifiStr = 60;
	//int wifiStr = "VISH's function to get value outta 70";
	if (wifiStr <20){
		LEDDrv_setState(1);
	}
	else if(wifiStr>=20 && wifiStr <40){
		LEDDrv_setState(3);
	}
	else if (wifiStr>=40 && wifiStr <60){
		LEDDrv_setState(7);
	}
	else if (wifiStr >=60){
		LEDDrv_setState(15);
	}
	else{
		LEDDrv_setState(0);
	}
}

//Physical Buttons
void MainWindowImpl::setButtons(int btnMask)
{
    QString str = "";
    bool ok;
    int volNum, bassNum, midNum, trebleNum;
    if (btnMask == -1) {
    	//Problem initializing buttons
        str = "0";
    } else if (btnMask == 0) {
        str = "0";
    } else {
        if (btnMask & (1<<BTN_BIT_UP)){
        	if (EQToggle == 0){
        		str = ui->lblVolEq->text();
            	volNum = str.toInt(&ok,10);
            	if (volNum != 100){
            		volNum = volNum + 1; 
           		}         
            	//Change Volume +1
            	ui->slideVolEq->setSliderPosition(volNum);
            	getSVEQValue(volNum);
       		}
       		else if(EQToggle == 1){
       			str = ui->lblBass->text();
            	bassNum = str.toInt(&ok,10);
            	if (bassNum != 100){
            		bassNum = bassNum + 1; 
           		}         
            	//Change Bass +1
            	ui->slideBass->setSliderPosition(bassNum);
            	getSBassValue(bassNum);
      		}
   			else if(EQToggle == 2){
       			str = ui->lblMid->text();
            	midNum = str.toInt(&ok,10);
            	if (midNum != 100){
            		midNum = midNum + 1; 
           		}         
            	//Change Mid +1
            	ui->slideMid->setSliderPosition(midNum);
            	getSMidValue(midNum);
      		}
      		else if(EQToggle == 3){
       			str = ui->lblTreble->text();
            	trebleNum = str.toInt(&ok,10);
            	if (trebleNum != 100){
            		trebleNum = trebleNum + 1; 
           		}         
            	//Change Treble +1
            	ui->slideTreble->setSliderPosition(trebleNum);
            	getSTrebleValue(trebleNum);
      		}
            
        }
        if (btnMask & (1<<BTN_BIT_DOWN)){
        	if (EQToggle == 0){
        		str = ui->lblVolEq->text();
     	      	volNum = str.toInt(&ok,10);
           		if (volNum != 0){
            	volNum = volNum - 1;
           		}          
            	//Change Volume -1
            	ui->slideVolEq->setSliderPosition(volNum);
            	getSVEQValue(volNum);
       		}
       		else if(EQToggle == 1){
       			str = ui->lblBass->text();
     	      	bassNum = str.toInt(&ok,10);
           		if (bassNum != 0){
            	bassNum = bassNum - 1;
           		}          
            	//Change Bass -1
            	ui->slideBass->setSliderPosition(bassNum);
            	getSBassValue(bassNum);
      		}
   			else if(EQToggle == 2){
       			str = ui->lblMid->text();
     	      	midNum = str.toInt(&ok,10);
           		if (midNum != 0){
            	midNum = midNum - 1;
           		}          
            	//Change Mid -1
            	ui->slideMid->setSliderPosition(midNum);
            	getSMidValue(midNum);
      		}
      		else if(EQToggle == 3){
       			str = ui->lblTreble->text();
     	      	trebleNum = str.toInt(&ok,10);
           		if (trebleNum != 0){
            	trebleNum = trebleNum - 1;
           		}          
            	//Change Treble -1
            	ui->slideTreble->setSliderPosition(trebleNum);
            	getSTrebleValue(trebleNum);
      		}
            
        }
        if (btnMask & (1<<BTN_BIT_LEFT)){	
            if (EQToggle == 0){
            	EQToggle = 3;
           	}
           	else{
           		EQToggle = EQToggle - 1;
          	}
       	}
        if (btnMask & (1<<BTN_BIT_RIGHT)){
            if (EQToggle == 3){
            	EQToggle = 0;
           	}
           	else{
           		EQToggle = EQToggle + 1;
          	}
        }
    }
}


