/********************************************************************************
** Form generated from reading UI file 'newobstacledialog.ui'
**
** Created: Mon Mar 3 18:04:58 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWOBSTACLEDIALOG_H
#define UI_NEWOBSTACLEDIALOG_H

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

class Ui_NewObstacleDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QPlainTextEdit *nombre;

    void setupUi(QDialog *NewObstacleDialog)
    {
        if (NewObstacleDialog->objectName().isEmpty())
            NewObstacleDialog->setObjectName(QString::fromUtf8("NewObstacleDialog"));
        NewObstacleDialog->resize(400, 111);
        NewObstacleDialog->setModal(true);
        buttonBox = new QDialogButtonBox(NewObstacleDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(NewObstacleDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 61, 20));
        nombre = new QPlainTextEdit(NewObstacleDialog);
        nombre->setObjectName(QString::fromUtf8("nombre"));
        nombre->setGeometry(QRect(80, 20, 151, 31));
        nombre->setFocusPolicy(Qt::WheelFocus);
        nombre->setTabChangesFocus(true);
        nombre->setPlainText(QString::fromUtf8(""));
        QWidget::setTabOrder(nombre, buttonBox);

        retranslateUi(NewObstacleDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewObstacleDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewObstacleDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewObstacleDialog);
    } // setupUi

    void retranslateUi(QDialog *NewObstacleDialog)
    {
        NewObstacleDialog->setWindowTitle(QApplication::translate("NewObstacleDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewObstacleDialog", "NOMBRE", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewObstacleDialog: public Ui_NewObstacleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWOBSTACLEDIALOG_H
