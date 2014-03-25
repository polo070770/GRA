#ifndef NEWTERRADIALOG_H
#define NEWTERRADIALOG_H

#include <QDialog>

namespace Ui {
class NewTerraDialog;
}

class NewTerraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTerraDialog(QWidget *parent = 0);
    ~NewTerraDialog();

private:
    Ui::NewTerraDialog *ui;

private slots:
    void emitAccepted();

signals:
    void Accepted(float amplaria, float profunditat, float y);
};

#endif // NEWTERRADIALOG_H
