#ifndef SYSTEM_H
#define SYSTEM_H

#include "data.h"
#include "fiomanager.h"
#include <QObject>


class System : public QObject
{
    Q_OBJECT
public:
    explicit System(QObject *parent = nullptr);
    void reset();

    Sensor *addSensor(Sensor::SensorType);
    Data *getData() const;

    void write(const QString &filepath);
    void read(const QString &filepath);

signals:
    void notified(const QString&);

private:
    Data *data;
    NotifictionListener *notif;
    FIOManagerFactory factory;
};

#endif // SYSTEM_H
