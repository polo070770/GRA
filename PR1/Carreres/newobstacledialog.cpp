#include "newobstacledialog.h"
#include "ui_newobstacledialog.h"
#include "mainwindow.h"

NewObstacleDialog::NewObstacleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewObstacleDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(emitAccepted()));
}

NewObstacleDialog::~NewObstacleDialog()
{
    delete ui;
}

void NewObstacleDialog::emitAccepted()
{
    emit Accepted(this->ui->nombre->toPlainText().toInt());
}
