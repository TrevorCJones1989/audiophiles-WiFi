#include "buttonthread.h"
#include <QDebug>

extern "C" {
#include "buttondrv.h"
}

ButtonThread::ButtonThread()
{
	QThread::setTerminationEnabled(true);
	stopThreads = false;
}

void ButtonThread::run()
{
   if (ButtonDrv_init() != 0) {
       emit buttonsChanged(-1);
      return;
   }
    while (!stopThreads) {
    //while (true) {
        int btnMask;
        int ret = ButtonDrv_read(&btnMask);
        if (ret == 0) {
            emit buttonsChanged(btnMask);
        }
    }
    ButtonDrv_cleanup();
}
