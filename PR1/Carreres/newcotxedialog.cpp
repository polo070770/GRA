#include "newcotxedialog.h"
#include "ui_newcotxedialog.h"

NewCotxeDialog::NewCotxeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCotxeDialog)
{
    ui->setupUi(this);
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
