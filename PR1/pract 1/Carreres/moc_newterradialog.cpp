/****************************************************************************
** Meta object code from reading C++ file 'newterradialog.h'
**
** Created: Mon Mar 3 18:05:32 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "newterradialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newterradialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewTerraDialog[] = {

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
      39,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      67,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NewTerraDialog[] = {
    "NewTerraDialog\0\0amplaria,profunditat,y\0"
    "Accepted(float,float,float)\0emitAccepted()\0"
};

void NewTerraDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewTerraDialog *_t = static_cast<NewTerraDialog *>(_o);
        switch (_id) {
        case 0: _t->Accepted((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 1: _t->emitAccepted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NewTerraDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewTerraDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewTerraDialog,
      qt_meta_data_NewTerraDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewTerraDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewTerraDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewTerraDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewTerraDialog))
        return static_cast<void*>(const_cast< NewTerraDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewTerraDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void NewTerraDialog::Accepted(float _t1, float _t2, float _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
