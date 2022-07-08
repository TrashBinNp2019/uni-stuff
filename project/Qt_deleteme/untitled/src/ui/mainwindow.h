#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <src/system/system.h>
#include "ui_sensorblock.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class SensorBlock; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void clearSensors();
    void displayAll();
    void addSensor(Sensor *sensor);

private slots:
    void on_actionNew_triggered();

    void on_actionAdd_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionSettings_triggered();

private:
    System system;
    Ui::MainWindow *ui;
    QList<std::pair<Ui::SensorBlock *, QWidget *>> sensors;
    Dialog settings;
};
#endif // MAINWINDOW_H
