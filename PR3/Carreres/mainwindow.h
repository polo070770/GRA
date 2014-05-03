#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newterradialog.h"
#include "newobstacledialog.h"
#include "newcotxedialog.h"
#include <QGLWidget>
#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    GLWidget *glWidget;
    NewTerraDialog *ntd;
    NewObstacleDialog *nod;
    NewCotxeDialog *ncd;

public slots:
    void acceptedNewTerra(float amplaria, float profunditat, float y);
    void acceptedNewObstacle(int nombre);
    void acceptedNewCotxe(float escala, float x, float z, float xdirector, float ydirector, float zdirector);
    void resetView();
};

#endif // MAINWINDOW_H
