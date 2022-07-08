#include "data.h"

Data::Data(QObject *parent)
    : QObject{parent}
{
    saveAsJson = true;
    filepath = "";
}

Data::~Data()
{
    for (auto s: sensors) {
        delete s;
    }
}

QList<Sensor *>::ConstIterator Data::begin() const
{
    return sensors.begin();
}

QList<Sensor *>::ConstIterator Data::end() const
{
    return sensors.end();
}

Data &Data::operator<<(Sensor *sensor)
{
    sensors.push_back(sensor);
    return *this;
}

Sensor *Data::add(Sensor *sensor)
{
    sensors.push_back(sensor);
    return sensors.last();
}

QJsonObject Data::toJson() const
{
    QJsonObject obj{};

    QJsonArray arr{};
    for (auto s: sensors) {
        arr.append((*s).toJson());
    }

    obj["sensors"] = arr;
    return obj;
}

void Data::fromJson(const QJsonObject &obj)
{
    if (!(obj.contains("sensors") && obj["sensors"].isArray())) {
        throw std::invalid_argument("Invalid JSON data object.");
    }

    for (auto s: sensors) {
        delete s;
    }
    sensors.clear();
    for (auto const &val: obj["sensors"].toArray()) {
        auto s = new Sensor(val.toObject());
        sensors << s;
    }
}

QDomDocument Data::toXML() const
{
    QDomDocument doc{};

    QDomElement root = doc.createElement("Data");
    doc.appendChild(root);

    for (auto s: sensors) {
        QDomElement el = doc.createElement("sensor");
        s->toXML(el);
        root.appendChild(el);
    }

    return doc;
}

void Data::fromXML(const QDomDocument &doc)
{
    auto list = doc.elementsByTagName("sensor");

    for (int i = 0; i < list.count(); i++) {
        if (!list.at(i).isElement()) {
            throw std::invalid_argument("Invalid XML data document.");
        }
    }

    for (auto s: sensors) {
        delete s;
    }
    sensors.clear();
    for (int i = 0; i < list.count(); i++) {
        auto s = new Sensor(list.at(i).toElement());
        sensors << s;
    }
}

bool Data::getSaveAsJson() const
{
    return saveAsJson;
}

void Data::setSaveAsJson(bool newSaveAsJson)
{
    saveAsJson = newSaveAsJson;
}

const QString &Data::getFilepath() const
{
    return filepath;
}

void Data::setFilepath(const QString &newFilepath)
{
    filepath = newFilepath;
}
