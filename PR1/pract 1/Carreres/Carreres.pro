#-------------------------------------------------
#
# Project created by QtCreator 2013-03-05T16:12:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Carreres
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    objecte.cpp \
    Common.cpp \
    cara.cpp \
    escena.cpp \
    cotxe.cpp \
    newcotxedialog.cpp \
    newobstacledialog.cpp \
    newterradialog.cpp \
    terra.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    objecte.h \
    Common.h \
    cara.h \
    vec.h \
    mat.h \
    escena.h \
    cotxe.h \
    newcotxedialog.h \
    newobstacledialog.h \
    newterradialog.h \
    readfile.h \
    terra.h

FORMS    += mainwindow.ui \
    newcotxedialog.ui \
    newterradialog.ui \
    newobstacledialog.ui

OTHER_FILES += \
    vshader11.glsl \
    fshader11.glsl \
    vshader1.glsl \
    fshader1.glsl
