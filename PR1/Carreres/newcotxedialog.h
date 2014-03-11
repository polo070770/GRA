#ifndef NEWCOTXEDIALOG_H
#define NEWCOTXEDIALOG_H

#include <QDialog>

namespace Ui {
class NewCotxeDialog;
}

class NewCotxeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCotxeDialog(QWidget *parent = 0);
    ~NewCotxeDialog();

private:
    Ui::NewCotxeDialog *ui;
private slots:
    void emitAccepted();

signals:
    void Accepted(float escala, float x, float z, float xdirector, float ydirector, float zdirector);
};

#endif // NEWCOTXEDIALOG_H
