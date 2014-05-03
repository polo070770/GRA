#include "newcotxedialog.h"
#include "ui_newcotxedialog.h"

NewCotxeDialog::NewCotxeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCotxeDialog)
{
    ui->setupUi(this);
    ui->escala->setPlainText(QString("2"));
    ui->x->setPlainText(QString("0"));
    ui->z->setPlainText(QString("0"));
    ui->xdirector->setPlainText(QString("-1"));
    ui->ydirector->setPlainText(QString("0"));
    ui->zdirector->setPlainText(QString("0"));
    connect(this, SIGNAL(accepted()), this, SLOT(emitAccepted()));
}

NewCotxeDialog::~NewCotxeDialog()
{
    delete ui;
}

void NewCotxeDialog::emitAccepted()
{
    emit Accepted(this->ui->escala->toPlainText().toFloat(),
                  this->ui->x->toPlainText().toFloat(),
                  this->ui->z->toPlainText().toFloat(),
                  this->ui->xdirector->toPlainText().toFloat(),
                  this->ui->ydirector->toPlainText().toFloat(),
                  this->ui->zdirector->toPlainText().toFloat());
}
