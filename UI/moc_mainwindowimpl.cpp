/****************************************************************************
** Meta object code from reading C++ file 'mainwindowimpl.h'
**
** Created: Fri Dec 2 08:55:12 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindowimpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindowimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindowImpl[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      30,   15,   15,   15, 0x0a,
      47,   15,   15,   15, 0x0a,
      70,   64,   15,   15, 0x0a,
      94,   88,   15,   15, 0x0a,
     118,  113,   15,   15, 0x0a,
     136,   88,   15,   15, 0x0a,
     160,  157,   15,   15, 0x0a,
     181,  157,   15,   15, 0x0a,
     207,  199,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindowImpl[] = {
    "MainWindowImpl\0\0connectWifi()\0"
    "disconnectWifi()\0cmbWifiRefresh()\0"
    "SVMEQ\0getSVEQValue(int)\0SBass\0"
    "getSBassValue(int)\0SMid\0getSMidValue(int)\0"
    "getSTrebleValue(int)\0in\0chkTransReceive(int)\0"
    "chkTransSend(int)\0btnMask\0setButtons(int)\0"
};

const QMetaObject MainWindowImpl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindowImpl,
      qt_meta_data_MainWindowImpl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindowImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindowImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindowImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindowImpl))
        return static_cast<void*>(const_cast< MainWindowImpl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindowImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connectWifi(); break;
        case 1: disconnectWifi(); break;
        case 2: cmbWifiRefresh(); break;
        case 3: getSVEQValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: getSBassValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: getSMidValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: getSTrebleValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: chkTransReceive((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: chkTransSend((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setButtons((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
