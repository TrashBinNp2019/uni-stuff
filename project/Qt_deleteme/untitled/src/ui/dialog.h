#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <src/system/data.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Data *data, QWidget *parent = nullptr);
    ~Dialog();

    void update();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    Data *data;
};

#endif // DIALOG_H
