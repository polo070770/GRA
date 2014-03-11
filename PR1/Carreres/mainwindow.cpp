#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdlib.h>
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Carreres Practica 1: GiVD 2013-2014"));
    resize(640, 640);

    //creo el glwidget y lo asigno como el central
    glWidget = new GLWidget;
    setCentralWidget(glWidget);

    //conecto las distintas opciones de menú con sus diálogos de forma bidireccional
    ntd = new NewTerraDialog(this);
    connect(this->ui->actionNew_Terra, SIGNAL(triggered()), ntd, SLOT(show()));
    connect(ntd, SIGNAL(Accepted(float,float,float)), this, SLOT(acceptedNewTerra(float,float,float)));

    //conecto las distintas opciones de menú con sus diálogos de forma bidireccional
    nod = new NewObstacleDialog(this);
    connect(this->ui->actionNew_Obstacle, SIGNAL(triggered()), nod, SLOT(show()));
    connect(nod, SIGNAL(Accepted(int)), this, SLOT(acceptedNewObstacle(int)));

    ncd = new NewCotxeDialog(this);
    connect(this->ui->actionNew_Cotxe, SIGNAL(triggered()), ncd, SLOT(show()));
    connect(ncd, SIGNAL(Accepted(float,float,float,float,float,float)), this, SLOT(acceptedNewCotxe(float,float,float,float,float,float)));

    connect(this->ui->actionReset, SIGNAL(triggered()), this, SLOT(resetView()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::acceptedNewObstacle(int nombre)
{
    this->glWidget->newObstacle(nombre);
}


void MainWindow::acceptedNewTerra(float amplaria, float profunditat, float y)
{
    this->glWidget->newTerra(amplaria, profunditat, y);
}

void MainWindow::acceptedNewCotxe(float escala, float x, float z, float xdirector, float ydirector, float zdirector)
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isNull())
        this->glWidget->newCotxe(fileName, x, z, escala, xdirector, ydirector, zdirector);
}


void MainWindow::resetView()
{
    this->glWidget->resetView();
}
