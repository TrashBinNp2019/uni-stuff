#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QtXml>
#include "../sensor/sensor.h"


// Wrapper for Sensor List and some application settings

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);
    ~Data();

    QList<Sensor *>::ConstIterator begin() const;
    QList<Sensor *>::ConstIterator end() const;

    // Returns reference to self for chaining
    Data &operator <<(Sensor *);
    // Returns reference to added object
    Sensor *add(Sensor *);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &);
    QDomDocument toXML() const;
    void fromXML(const QDomDocument &);

    bool getSaveAsJson() const;
    void setSaveAsJson(bool newSaveAsJson);
    const QString &getFilepath() const;
    void setFilepath(const QString &newFilepath);

signals:

private:
    QList<Sensor *> sensors;
    bool saveAsJson;
    QString filepath;
};


#endif // DATA_H
