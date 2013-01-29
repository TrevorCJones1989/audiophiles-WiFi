/********************************************************************************
** Form generated from reading UI file 'audiophileswindow.ui'
**
** Created: Fri Dec 2 08:55:08 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOPHILESWINDOW_H
#define UI_AUDIOPHILESWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tabWifi;
    QGridLayout *gridLayout_4;
    QLabel *lblTxtCurrentNetwork;
    QLabel *lblTxtCurrentIP;
    QPushButton *btnWifiRefresh;
    QPushButton *btnConnectWifi;
    QPushButton *btnDisconnectWifi;
    QLabel *lblTxtAvailableNetworks;
    QComboBox *cmbWifi;
    QLabel *lblNetwork;
    QLabel *lblIP;
    QWidget *tabConnections;
    QGridLayout *gridLayout_3;
    QLabel *lblTxtReceive;
    QLabel *lblTxtSend;
    QCheckBox *chkReceiveTransmit;
    QCheckBox *chkSendTransmit;
    QWidget *tabEqualizer;
    QGridLayout *gridLayout_2;
    QSlider *slideBass;
    QSlider *slideMid;
    QSlider *slideTreble;
    QSlider *slideVolEq;
    QLabel *lblTxtTerble;
    QLabel *lblTxtMid;
    QLabel *lblTxtBass;
    QLabel *lblTxtVolEq;
    QLabel *lblVolEq;
    QLabel *lblBass;
    QLabel *lblMid;
    QLabel *lblTreble;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(365, 279);
        MainWindow->setStyleSheet(QString::fromUtf8("#centralwidget{\n"
"background:  gray;\n"
"}\n"
"#tabConnections{\n"
"background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FF9D73, stop: 1 #A63100);\n"
"}\n"
"#tabMixer{\n"
"background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FF9D73, stop: 1 #A63100);\n"
"}\n"
"#tabEqualizer{\n"
"background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FF9D73, stop: 1 #A63100);\n"
"}\n"
"#tabWifi{\n"
"background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FF9D73, stop: 1 #A63100);\n"
"}\n"
"QPushButton{\n"
"color:black;\n"
"background-color: #FF9D73;\n"
"}\n"
"QComboBox{\n"
"background: #FF9D73;\n"
"color: white;\n"
"}\n"
"QLabel{\n"
"color: white;\n"
"}\n"
"QCheckBox{\n"
"color: black;\n"
"background-color: #FF9D73;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMaximumSize(QSize(520, 16777215));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWifi = new QWidget();
        tabWifi->setObjectName(QString::fromUtf8("tabWifi"));
        gridLayout_4 = new QGridLayout(tabWifi);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lblTxtCurrentNetwork = new QLabel(tabWifi);
        lblTxtCurrentNetwork->setObjectName(QString::fromUtf8("lblTxtCurrentNetwork"));

        gridLayout_4->addWidget(lblTxtCurrentNetwork, 0, 0, 1, 1);

        lblTxtCurrentIP = new QLabel(tabWifi);
        lblTxtCurrentIP->setObjectName(QString::fromUtf8("lblTxtCurrentIP"));

        gridLayout_4->addWidget(lblTxtCurrentIP, 1, 0, 1, 1);

        btnWifiRefresh = new QPushButton(tabWifi);
        btnWifiRefresh->setObjectName(QString::fromUtf8("btnWifiRefresh"));

        gridLayout_4->addWidget(btnWifiRefresh, 2, 4, 1, 1);

        btnConnectWifi = new QPushButton(tabWifi);
        btnConnectWifi->setObjectName(QString::fromUtf8("btnConnectWifi"));

        gridLayout_4->addWidget(btnConnectWifi, 3, 4, 1, 1);

        btnDisconnectWifi = new QPushButton(tabWifi);
        btnDisconnectWifi->setObjectName(QString::fromUtf8("btnDisconnectWifi"));

        gridLayout_4->addWidget(btnDisconnectWifi, 4, 4, 1, 1);

        lblTxtAvailableNetworks = new QLabel(tabWifi);
        lblTxtAvailableNetworks->setObjectName(QString::fromUtf8("lblTxtAvailableNetworks"));

        gridLayout_4->addWidget(lblTxtAvailableNetworks, 2, 0, 1, 1);

        cmbWifi = new QComboBox(tabWifi);
        cmbWifi->setObjectName(QString::fromUtf8("cmbWifi"));

        gridLayout_4->addWidget(cmbWifi, 3, 0, 1, 2);

        lblNetwork = new QLabel(tabWifi);
        lblNetwork->setObjectName(QString::fromUtf8("lblNetwork"));

        gridLayout_4->addWidget(lblNetwork, 0, 2, 1, 1);

        lblIP = new QLabel(tabWifi);
        lblIP->setObjectName(QString::fromUtf8("lblIP"));

        gridLayout_4->addWidget(lblIP, 1, 2, 1, 1);

        tabWidget->addTab(tabWifi, QString());
        tabConnections = new QWidget();
        tabConnections->setObjectName(QString::fromUtf8("tabConnections"));
        gridLayout_3 = new QGridLayout(tabConnections);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lblTxtReceive = new QLabel(tabConnections);
        lblTxtReceive->setObjectName(QString::fromUtf8("lblTxtReceive"));

        gridLayout_3->addWidget(lblTxtReceive, 0, 0, 1, 1);

        lblTxtSend = new QLabel(tabConnections);
        lblTxtSend->setObjectName(QString::fromUtf8("lblTxtSend"));

        gridLayout_3->addWidget(lblTxtSend, 2, 0, 1, 1);

        chkReceiveTransmit = new QCheckBox(tabConnections);
        chkReceiveTransmit->setObjectName(QString::fromUtf8("chkReceiveTransmit"));

        gridLayout_3->addWidget(chkReceiveTransmit, 0, 1, 1, 1);

        chkSendTransmit = new QCheckBox(tabConnections);
        chkSendTransmit->setObjectName(QString::fromUtf8("chkSendTransmit"));

        gridLayout_3->addWidget(chkSendTransmit, 2, 1, 1, 1);

        tabWidget->addTab(tabConnections, QString());
        tabEqualizer = new QWidget();
        tabEqualizer->setObjectName(QString::fromUtf8("tabEqualizer"));
        gridLayout_2 = new QGridLayout(tabEqualizer);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        slideBass = new QSlider(tabEqualizer);
        slideBass->setObjectName(QString::fromUtf8("slideBass"));
        slideBass->setMaximum(100);
        slideBass->setSingleStep(10);
        slideBass->setValue(50);
        slideBass->setOrientation(Qt::Vertical);
        slideBass->setTickPosition(QSlider::TicksAbove);
        slideBass->setTickInterval(10);

        gridLayout_2->addWidget(slideBass, 1, 3, 1, 1);

        slideMid = new QSlider(tabEqualizer);
        slideMid->setObjectName(QString::fromUtf8("slideMid"));
        slideMid->setCursor(QCursor(Qt::ArrowCursor));
        slideMid->setMaximum(100);
        slideMid->setSingleStep(10);
        slideMid->setValue(50);
        slideMid->setOrientation(Qt::Vertical);
        slideMid->setTickPosition(QSlider::TicksAbove);
        slideMid->setTickInterval(10);

        gridLayout_2->addWidget(slideMid, 1, 4, 1, 1);

        slideTreble = new QSlider(tabEqualizer);
        slideTreble->setObjectName(QString::fromUtf8("slideTreble"));
        slideTreble->setMaximum(100);
        slideTreble->setSingleStep(10);
        slideTreble->setValue(50);
        slideTreble->setOrientation(Qt::Vertical);
        slideTreble->setTickPosition(QSlider::TicksAbove);
        slideTreble->setTickInterval(10);

        gridLayout_2->addWidget(slideTreble, 1, 5, 1, 1);

        slideVolEq = new QSlider(tabEqualizer);
        slideVolEq->setObjectName(QString::fromUtf8("slideVolEq"));
        slideVolEq->setMaximum(100);
        slideVolEq->setSingleStep(10);
        slideVolEq->setValue(100);
        slideVolEq->setSliderPosition(100);
        slideVolEq->setOrientation(Qt::Vertical);
        slideVolEq->setTickPosition(QSlider::TicksAbove);
        slideVolEq->setTickInterval(10);

        gridLayout_2->addWidget(slideVolEq, 1, 1, 1, 1);

        lblTxtTerble = new QLabel(tabEqualizer);
        lblTxtTerble->setObjectName(QString::fromUtf8("lblTxtTerble"));

        gridLayout_2->addWidget(lblTxtTerble, 0, 5, 1, 1);

        lblTxtMid = new QLabel(tabEqualizer);
        lblTxtMid->setObjectName(QString::fromUtf8("lblTxtMid"));

        gridLayout_2->addWidget(lblTxtMid, 0, 4, 1, 1);

        lblTxtBass = new QLabel(tabEqualizer);
        lblTxtBass->setObjectName(QString::fromUtf8("lblTxtBass"));

        gridLayout_2->addWidget(lblTxtBass, 0, 3, 1, 1);

        lblTxtVolEq = new QLabel(tabEqualizer);
        lblTxtVolEq->setObjectName(QString::fromUtf8("lblTxtVolEq"));

        gridLayout_2->addWidget(lblTxtVolEq, 0, 1, 1, 1);

        lblVolEq = new QLabel(tabEqualizer);
        lblVolEq->setObjectName(QString::fromUtf8("lblVolEq"));

        gridLayout_2->addWidget(lblVolEq, 2, 1, 1, 1);

        lblBass = new QLabel(tabEqualizer);
        lblBass->setObjectName(QString::fromUtf8("lblBass"));

        gridLayout_2->addWidget(lblBass, 2, 3, 1, 1);

        lblMid = new QLabel(tabEqualizer);
        lblMid->setObjectName(QString::fromUtf8("lblMid"));

        gridLayout_2->addWidget(lblMid, 2, 4, 1, 1);

        lblTreble = new QLabel(tabEqualizer);
        lblTreble->setObjectName(QString::fromUtf8("lblTreble"));

        gridLayout_2->addWidget(lblTreble, 2, 5, 1, 1);

        tabWidget->addTab(tabEqualizer, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 365, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Audiophiles", 0, QApplication::UnicodeUTF8));
        lblTxtCurrentNetwork->setText(QApplication::translate("MainWindow", "Network:", 0, QApplication::UnicodeUTF8));
        lblTxtCurrentIP->setText(QApplication::translate("MainWindow", "Your IP:", 0, QApplication::UnicodeUTF8));
        btnWifiRefresh->setText(QApplication::translate("MainWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        btnConnectWifi->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        btnDisconnectWifi->setText(QApplication::translate("MainWindow", "Disconnect", 0, QApplication::UnicodeUTF8));
        lblTxtAvailableNetworks->setText(QApplication::translate("MainWindow", "Networks:", 0, QApplication::UnicodeUTF8));
        lblNetwork->setText(QApplication::translate("MainWindow", "None", 0, QApplication::UnicodeUTF8));
        lblIP->setText(QApplication::translate("MainWindow", "0.0.0.0", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabWifi), QApplication::translate("MainWindow", "Wifi", 0, QApplication::UnicodeUTF8));
        lblTxtReceive->setText(QApplication::translate("MainWindow", "Receive:", 0, QApplication::UnicodeUTF8));
        lblTxtSend->setText(QApplication::translate("MainWindow", "Broadcast Audio:", 0, QApplication::UnicodeUTF8));
        chkReceiveTransmit->setText(QApplication::translate("MainWindow", "Receive", 0, QApplication::UnicodeUTF8));
        chkSendTransmit->setText(QApplication::translate("MainWindow", "Transmit", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabConnections), QApplication::translate("MainWindow", "Connections", 0, QApplication::UnicodeUTF8));
        lblTxtTerble->setText(QApplication::translate("MainWindow", "Treble", 0, QApplication::UnicodeUTF8));
        lblTxtMid->setText(QApplication::translate("MainWindow", "Mid", 0, QApplication::UnicodeUTF8));
        lblTxtBass->setText(QApplication::translate("MainWindow", "Bass", 0, QApplication::UnicodeUTF8));
        lblTxtVolEq->setText(QApplication::translate("MainWindow", "Volume", 0, QApplication::UnicodeUTF8));
        lblVolEq->setText(QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8));
        lblBass->setText(QApplication::translate("MainWindow", "50", 0, QApplication::UnicodeUTF8));
        lblMid->setText(QApplication::translate("MainWindow", "50", 0, QApplication::UnicodeUTF8));
        lblTreble->setText(QApplication::translate("MainWindow", "50", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabEqualizer), QApplication::translate("MainWindow", "Equalizer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOPHILESWINDOW_H
