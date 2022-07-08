#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(Data *d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    data = d;
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::update()
{
    ui->JsonRadio->setChecked(data->getSaveAsJson());
}

void Dialog::on_buttonBox_accepted()
{
    if (data->getSaveAsJson() != ui->JsonRadio->isChecked()) {
        data->setFilepath("");
        data->setSaveAsJson(ui->JsonRadio->isChecked());
    }
}

