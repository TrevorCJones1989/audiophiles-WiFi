CONFIG += warn_on debug app_bundle qt
SOURCES = mainwindowimpl.cpp main.cpp buttonthread.cpp audiostream.cpp
TARGET =
DEPENDPATH = .
INCLUDEPATH = .
TEMPLATE = app
QT += gui core
HEADERS += mainwindowimpl.h \
 wifi.h \
 buttonthread.h \
 buttondrv.h \
 leddrv.h \
 audiostream.h \
 watconstants.h \
 watworkers.h
FORMS += audiophileswindow.ui
