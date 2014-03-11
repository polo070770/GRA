#include "newterradialog.h"
#include "ui_newterradialog.h"
#include "mainwindow.h"

NewTerraDialog::NewTerraDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTerraDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(emitAccepted()));
}

NewTerraDialog::~NewTerraDialog()
{
    delete ui;
}

void NewTerraDialog::emitAccepted()
{
    emit Accepted(this->ui->amplaria->toPlainText().toFloat(),
                  this->ui->profunditat->toPlainText().toFloat(),
                  this->ui->y->toPlainText().toFloat());
}


