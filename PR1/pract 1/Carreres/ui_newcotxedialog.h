/********************************************************************************
** Form generated from reading UI file 'newcotxedialog.ui'
**
** Created: Mon Mar 3 18:04:58 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCOTXEDIALOG_H
#define UI_NEWCOTXEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_NewCotxeDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label;
    QPlainTextEdit *escala;
    QPlainTextEdit *x;
    QPlainTextEdit *z;
    QPlainTextEdit *zdirector;
    QPlainTextEdit *xdirector;
    QPlainTextEdit *ydirector;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QDialog *NewCotxeDialog)
    {
        if (NewCotxeDialog->objectName().isEmpty())
            NewCotxeDialog->setObjectName(QString::fromUtf8("NewCotxeDialog"));
        NewCotxeDialog->resize(400, 273);
        buttonBox = new QDialogButtonBox(NewCotxeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_2 = new QLabel(NewCotxeDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 80, 21, 17));
        label_4 = new QLabel(NewCotxeDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 120, 21, 21));
        label = new QLabel(NewCotxeDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 51, 17));
        escala = new QPlainTextEdit(NewCotxeDialog);
        escala->setObjectName(QString::fromUtf8("escala"));
        escala->setGeometry(QRect(100, 24, 151, 31));
        escala->setFocusPolicy(Qt::WheelFocus);
        escala->setTabChangesFocus(true);
        escala->setPlainText(QString::fromUtf8(""));
        x = new QPlainTextEdit(NewCotxeDialog);
        x->setObjectName(QString::fromUtf8("x"));
        x->setGeometry(QRect(100, 64, 151, 31));
        x->setFocusPolicy(Qt::WheelFocus);
        x->setTabChangesFocus(true);
        x->setPlainText(QString::fromUtf8(""));
        z = new QPlainTextEdit(NewCotxeDialog);
        z->setObjectName(QString::fromUtf8("z"));
        z->setGeometry(QRect(100, 110, 151, 31));
        z->setFocusPolicy(Qt::WheelFocus);
        z->setTabChangesFocus(true);
        z->setPlainText(QString::fromUtf8(""));
        zdirector = new QPlainTextEdit(NewCotxeDialog);
        zdirector->setObjectName(QString::fromUtf8("zdirector"));
        zdirector->setGeometry(QRect(100, 240, 151, 31));
        zdirector->setFocusPolicy(Qt::WheelFocus);
        zdirector->setTabChangesFocus(true);
        zdirector->setPlainText(QString::fromUtf8(""));
        xdirector = new QPlainTextEdit(NewCotxeDialog);
        xdirector->setObjectName(QString::fromUtf8("xdirector"));
        xdirector->setGeometry(QRect(100, 154, 151, 31));
        xdirector->setFocusPolicy(Qt::WheelFocus);
        xdirector->setTabChangesFocus(true);
        xdirector->setPlainText(QString::fromUtf8(""));
        ydirector = new QPlainTextEdit(NewCotxeDialog);
        ydirector->setObjectName(QString::fromUtf8("ydirector"));
        ydirector->setGeometry(QRect(100, 194, 151, 31));
        ydirector->setFocusPolicy(Qt::WheelFocus);
        ydirector->setTabChangesFocus(true);
        ydirector->setPlainText(QString::fromUtf8(""));
        label_3 = new QLabel(NewCotxeDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 160, 81, 17));
        label_5 = new QLabel(NewCotxeDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 200, 81, 17));
        label_6 = new QLabel(NewCotxeDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 240, 81, 17));
        QWidget::setTabOrder(escala, x);
        QWidget::setTabOrder(x, z);
        QWidget::setTabOrder(z, xdirector);
        QWidget::setTabOrder(xdirector, ydirector);
        QWidget::setTabOrder(ydirector, zdirector);
        QWidget::setTabOrder(zdirector, buttonBox);

        retranslateUi(NewCotxeDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewCotxeDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewCotxeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewCotxeDialog);
    } // setupUi

    void retranslateUi(QDialog *NewCotxeDialog)
    {
        NewCotxeDialog->setWindowTitle(QApplication::translate("NewCotxeDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewCotxeDialog", "X", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewCotxeDialog", "Z", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewCotxeDialog", "ESCALA", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewCotxeDialog", "X DIRECTOR", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NewCotxeDialog", "Y DIRECTOR", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NewCotxeDialog", "Z DIRECTOR", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewCotxeDialog: public Ui_NewCotxeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCOTXEDIALOG_H
