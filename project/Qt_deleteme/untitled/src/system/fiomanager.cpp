#include "fiomanager.h"

FIOManager::FIOManager(const QString &fp)
{
    filepath = fp;
}

FIOManagerXML::FIOManagerXML(const QString &filepath) : FIOManager(filepath)
{}

void FIOManagerXML::read(Data &data)
{
    qDebug() << "reading xml";

    QDomDocument doc("mydocument");
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly))
        throw std::invalid_argument("Faied opening file.");
    if (!doc.setContent(&file)) {
        file.close();
        throw std::invalid_argument("Faied reading file.");
    }
    file.close();

    data.fromXML(doc);
}

void FIOManagerXML::write(const Data &data)
{
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        throw std::invalid_argument("Faied opening file.");
    }

    auto doc = data.toXML();
    QTextStream stream(&file);
    stream << doc.toString();

    file.close();
}

FIOManagerJSON::FIOManagerJSON(const QString &filepath) : FIOManager(filepath)
{}

void FIOManagerJSON::read(Data &data)
{
    qDebug() << "reading json";

    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::invalid_argument("Faied opening file.");
    }
    auto val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val);

    if (!doc.isObject()) {
        throw std::invalid_argument("Failed reading file.");
    }
    data.fromJson(doc.object());
}

void FIOManagerJSON::write(const Data &data)
{
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        throw std::invalid_argument("Faied opening file.");
    }

    QJsonDocument doc{ data.toJson() };
    QTextStream stream(&file);
    stream << doc.toJson();

    file.close();
}

FIOManagerFactory::FIOManagerFactory()
{
}

std::unique_ptr<FIOManager> FIOManagerFactory::getFIOManager(FileFormat format, const QString &filepath)
{
    switch (format) {
    case XML:{
        return std::make_unique<FIOManagerXML>(filepath);
    }
    case JSON:{
        return std::make_unique<FIOManagerJSON>(filepath);
    }
    }
}


