#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QtXml>
#include "../system/notifictionlistener.h"
#include "state.h"


class Sensor : public QObject
{
    Q_OBJECT
public:
    enum SensorType{ Pressure, Temperature, MagneticField };

    explicit Sensor(const QString &, SensorType, QObject *parent = nullptr);
    explicit Sensor(const QJsonObject &obj);
    explicit Sensor(const QDomElement &el);

    void changeMode( State::StateEnum );
    State::StateEnum getMode() const;
    float getValue() const;
    const QString &getID() const;
    SensorType getType() const;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &);
    void toXML(QDomElement &el) const;
    void fromXML(const QDomElement &);

signals:
    void updated(const Event&);
    void modeChanged(const QString&);

private slots:
    void onUpdate(float val);

private:
    QString ID;
    SensorType type;
    std::unique_ptr<State> state;
    double normalStateValue;
};


#endif // SENSOR_H
