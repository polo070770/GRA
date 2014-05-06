/****************************************************************************
** Meta object code from reading C++ file 'newcotxedialog.h'
**
** Created: Mon Mar 3 18:05:31 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "newcotxedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newcotxedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewCotxeDialog[] = {

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
      57,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     103,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NewCotxeDialog[] = {
    "NewCotxeDialog\0\0"
    "escala,x,z,xdirector,ydirector,zdirector\0"
    "Accepted(float,float,float,float,float,float)\0"
    "emitAccepted()\0"
};

void NewCotxeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewCotxeDialog *_t = static_cast<NewCotxeDialog *>(_o);
        switch (_id) {
        case 0: _t->Accepted((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6]))); break;
        case 1: _t->emitAccepted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NewCotxeDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewCotxeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewCotxeDialog,
      qt_meta_data_NewCotxeDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewCotxeDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewCotxeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewCotxeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewCotxeDialog))
        return static_cast<void*>(const_cast< NewCotxeDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewCotxeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void NewCotxeDialog::Accepted(float _t1, float _t2, float _t3, float _t4, float _t5, float _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
