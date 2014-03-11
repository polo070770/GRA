#ifndef NEWOBSTACLEDIALOG_H
#define NEWOBSTACLEDIALOG_H

#include <QDialog>

namespace Ui {
class NewObstacleDialog;
}

class NewObstacleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewObstacleDialog(QWidget *parent = 0);
    ~NewObstacleDialog();

private:
    Ui::NewObstacleDialog *ui;

private slots:
    void emitAccepted();

signals:
    void Accepted(int nombre);
};

#endif // NEWOBSTACLEDIALOG_H
