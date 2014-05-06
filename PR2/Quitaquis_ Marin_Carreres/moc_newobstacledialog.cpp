/****************************************************************************
** Meta object code from reading C++ file 'newobstacledialog.h'
**
** Created: Mon Mar 3 18:05:32 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "newobstacledialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newobstacledialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewObstacleDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NewObstacleDialog[] = {
    "NewObstacleDialog\0\0nombre\0Accepted(int)\0"
    "emitAccepted()\0"
};

void NewObstacleDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewObstacleDialog *_t = static_cast<NewObstacleDialog *>(_o);
        switch (_id) {
        case 0: _t->Accepted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->emitAccepted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NewObstacleDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewObstacleDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewObstacleDialog,
      qt_meta_data_NewObstacleDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewObstacleDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewObstacleDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewObstacleDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewObstacleDialog))
        return static_cast<void*>(const_cast< NewObstacleDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewObstacleDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void NewObstacleDialog::Accepted(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
