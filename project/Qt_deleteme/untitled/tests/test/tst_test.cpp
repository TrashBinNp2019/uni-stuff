#include <QtTest>
#include "../../src/system/idgenerator.h"
#include "../../src/sensor/sensor.h"


class Test : public QObject
{
    Q_OBJECT

public:
    Test();
    ~Test();

private slots:
    void id_generation_test();
    void sensor_fio_test();

};

Test::Test()
{

}

Test::~Test()
{

}

void Test::id_generation_test()
{
    auto id3 = IDGenerator::generate();
    auto id2 = IDGenerator::generate();
    auto id1 = IDGenerator::generate();
    QCOMPARE(id1.length(), 4);
    QVERIFY(id1 != id2);
    QVERIFY(id1 != id3);
    QVERIFY(id2 != id3);
}

void Test::sensor_fio_test()
{
    Sensor writtenJson("ffff", Sensor::Pressure);
    writtenJson.changeMode(State::Normal);
    auto fileJson = writtenJson.toJson();
    Sensor readJson("aaaa", Sensor::MagneticField);
    readJson.fromJson(fileJson);

    QCOMPARE(writtenJson.getMode(), readJson.getMode());
    QCOMPARE(writtenJson.getValue(), readJson.getValue());
    QCOMPARE(writtenJson.getID(), readJson.getID());
    QCOMPARE(writtenJson.getType(), readJson.getType());

    Sensor writtenXml("ffff", Sensor::Pressure);
    writtenXml.changeMode(State::Normal);
    QDomDocument doc{};
    QDomElement fileXml = doc.createElement("sensor");
    writtenXml.toXML(fileXml);
    doc.appendChild(fileXml);

    Sensor readXml("aaaa", Sensor::MagneticField);
    readXml.fromXML(doc.elementsByTagName("sensor").at(0).toElement());

    QCOMPARE(writtenXml.getID(), readXml.getID());
    QCOMPARE(writtenXml.getValue(), readXml.getValue());
    QCOMPARE(writtenXml.getType(), readXml.getType());
    QCOMPARE(writtenXml.getMode(), readXml.getMode());
}


QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
