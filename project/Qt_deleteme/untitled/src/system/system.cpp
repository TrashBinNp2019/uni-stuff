#include "system.h"
#include "idgenerator.h"

System::System(QObject *parent)
    : QObject(parent)
{
    data = new Data();
    notif = new NotifictionListener();
    connect(notif, SIGNAL(notify(QString)), this, SIGNAL(notified(QString)));
}

void System::reset()
{
    delete data;
    delete notif;

    data = new Data();
    notif = new NotifictionListener();
    connect(notif, SIGNAL(notify(QString)), this, SIGNAL(notified(QString)));
}

Sensor *System::addSensor(Sensor::SensorType type)
{
    auto s = new Sensor(IDGenerator::generate(), type);
    connect(s, SIGNAL(updated(Event)), notif, SLOT(notified(Event)));
    *data << s;

    return s;
}

Data *System::getData() const
{
    return data;
}

void System::write(const QString &filepath)
{
    auto isJson = data->getSaveAsJson();
    auto manager = factory.getFIOManager(isJson? FIOManagerFactory::JSON : FIOManagerFactory::XML, filepath);
    manager->write(*data);
    data->setFilepath(filepath);
}

void System::read(const QString &filepath)
{
    auto isJson = filepath[filepath.lastIndexOf('.') + 1] == 'j';
    auto manager = factory.getFIOManager(isJson? FIOManagerFactory::JSON : FIOManagerFactory::XML, filepath);
    try {
        manager->read(*data);
        data->setSaveAsJson(isJson);
        data->setFilepath(filepath);
    } catch (std::exception e) {
        qDebug() << e.what();
    }
}
