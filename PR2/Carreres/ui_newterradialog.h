/********************************************************************************
** Form generated from reading UI file 'newterradialog.ui'
**
** Created: Mon Mar 3 18:04:58 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWTERRADIALOG_H
#define UI_NEWTERRADIALOG_H

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

class Ui_NewTerraDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPlainTextEdit *amplaria;
    QPlainTextEdit *profunditat;
    QPlainTextEdit *y;

    void setupUi(QDialog *NewTerraDialog)
    {
        if (NewTerraDialog->objectName().isEmpty())
            NewTerraDialog->setObjectName(QString::fromUtf8("NewTerraDialog"));
        NewTerraDialog->resize(400, 142);
        NewTerraDialog->setModal(true);
        buttonBox = new QDialogButtonBox(NewTerraDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(NewTerraDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 71, 20));
        label_2 = new QLabel(NewTerraDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 101, 20));
        label_3 = new QLabel(NewTerraDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 110, 21, 21));
        amplaria = new QPlainTextEdit(NewTerraDialog);
        amplaria->setObjectName(QString::fromUtf8("amplaria"));
        amplaria->setGeometry(QRect(110, 20, 121, 31));
        amplaria->setFocusPolicy(Qt::WheelFocus);
        amplaria->setTabChangesFocus(true);
        amplaria->setPlainText(QString::fromUtf8(""));
        profunditat = new QPlainTextEdit(NewTerraDialog);
        profunditat->setObjectName(QString::fromUtf8("profunditat"));
        profunditat->setGeometry(QRect(110, 60, 121, 31));
        profunditat->setFocusPolicy(Qt::WheelFocus);
        profunditat->setTabChangesFocus(true);
        profunditat->setPlainText(QString::fromUtf8(""));
        y = new QPlainTextEdit(NewTerraDialog);
        y->setObjectName(QString::fromUtf8("y"));
        y->setGeometry(QRect(110, 100, 121, 31));
        y->setFocusPolicy(Qt::WheelFocus);
        y->setTabChangesFocus(true);
        y->setPlainText(QString::fromUtf8(""));
        buttonBox->raise();
        label->raise();
        label_3->raise();
        amplaria->raise();
        profunditat->raise();
        y->raise();
        label_2->raise();
        QWidget::setTabOrder(amplaria, profunditat);
        QWidget::setTabOrder(profunditat, y);
        QWidget::setTabOrder(y, buttonBox);

        retranslateUi(NewTerraDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewTerraDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewTerraDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewTerraDialog);
    } // setupUi

    void retranslateUi(QDialog *NewTerraDialog)
    {
        NewTerraDialog->setWindowTitle(QApplication::translate("NewTerraDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewTerraDialog", "AMPL\303\200RIA", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewTerraDialog", "PROFUNDITAT", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewTerraDialog", "Y", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewTerraDialog: public Ui_NewTerraDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWTERRADIALOG_H
