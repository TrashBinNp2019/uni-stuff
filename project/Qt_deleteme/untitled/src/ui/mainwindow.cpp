#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QScrollArea>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings(system.getData(), this)
{
    ui->setupUi(this);
    connect(&system, &System::notified, [=](const QString& msg){
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage(msg);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearSensors()
{
    for (auto p : sensors) {
        delete p.first;
        delete p.second;
    }
    sensors.clear();
}

void MainWindow::displayAll()
{
    clearSensors();
    for (auto i = system.getData()->begin(); i != system.getData()->end(); i++) {
        addSensor(*i);
    }
}

void MainWindow::addSensor(Sensor *sensor)
{
    auto modeStr = "";
    switch (sensor->getMode()) {
    case State::Calibration: {
        modeStr = "Calibration";
        break;
    }
    case State::Normal: {
        modeStr = "Normal";
        break;
    }
    case State::Idle: {
        modeStr = "Idle";
        break;
    }
    }
    auto typeStr = "";
    switch (sensor->getType()) {
    case Sensor::MagneticField: {
        typeStr = "Magnetic Field";
        break;
    }
    case Sensor::Pressure: {
        typeStr = "Pressure";
        break;
    }
    case Sensor::Temperature: {
        typeStr = "Temperature";
        break;
    }
    }

    auto widget = new QWidget();
    auto sensorUi = new Ui::SensorBlock();
    sensors.push_back(std::make_pair(sensorUi, widget));
    sensorUi->setupUi(widget);
    if (modeStr[0] == 'I') sensorUi->val->display("-");
    sensorUi->idLabel->setText(sensor->getID());
    sensorUi->typeLabel->setText(typeStr);
    sensorUi->modeLabel->setText(modeStr);
    connect(sensor, &Sensor::updated, [=](const Event& ev){
        sensorUi->val->display(ev.value);
    });
    connect(sensor, &Sensor::modeChanged, [=](const QString& str){
        sensorUi->modeLabel->setText(str);
        sensorUi->val->display("-");
    });
    connect(sensorUi->pushButton, &QPushButton::released, [=](){
        switch (sensor->getMode()) {
        case State::Calibration: {
            sensor->changeMode(State::Normal);
            return;
        }
        case State::Normal: {
            sensor->changeMode(State::Idle);
            return;
        }
        case State::Idle: {
            sensor->changeMode(State::Calibration);
            return;
        }
        }
    });

    ui->scrollAreaWidgetContents->layout()->addWidget(widget);
}


void MainWindow::on_actionNew_triggered()
{
    system.reset();
    clearSensors();
}


void MainWindow::on_actionAdd_triggered()
{
    auto str = QInputDialog::getItem(this, "Choose sensor type", "Type:",
                                     {"Pressure", "Temperature", "Magnetic Field"}, 0, false);
    auto type = Sensor::Pressure;
    if (str[0] == 'T') {
        type = Sensor::Temperature;
    } else if (str[0] == 'M') {
        type = Sensor::MagneticField;
    }
    auto sensor = system.addSensor(type);
    addSensor(sensor);

    ui->statusbar->showMessage("Added " + sensor->getID());
}


void MainWindow::on_actionSave_triggered()
{
    QString filepath = system.getData()->getFilepath();
    if (filepath.length() == 0) {
        auto filetype = "Data Files (*.xml)";
        if (system.getData()->getSaveAsJson()) {
            filetype = "Data Files (*.json)";
        }
        filepath = QFileDialog::getSaveFileName(this, "Choose save file", QDir::home().absolutePath(), filetype);
    }
    system.write(filepath);

    ui->statusbar->showMessage("Written " + filepath);
}


void MainWindow::on_actionSave_as_triggered()
{
    auto filetype = "Data Files (*.xml)";
    if (system.getData()->getSaveAsJson()) {
        filetype = "Data Files (*.json)";
    }
    QString filepath = QFileDialog::getSaveFileName(this, "Choose save file", QDir::home().absolutePath(), filetype);
    system.write(filepath);

    ui->statusbar->showMessage("Written " + filepath);
}


void MainWindow::on_actionOpen_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Choose data file", QDir::home().absolutePath(),
                                                    "Data Files (*.json *.xml)");
    system.read(filepath);
    displayAll();

    ui->statusbar->showMessage("Read " + filepath);
}


void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::exit();
}


void MainWindow::on_actionSettings_triggered()
{
    settings.open()	;
}

