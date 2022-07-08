#include "idgenerator.h"
#include "ctime"

// Necessary static field initialization.
IDGenerator::Generator *IDGenerator::instance = new IDGenerator::Generator();
int ID_LENGTH = 4;

QString IDGenerator::Generator::generate()
{
    QString id;
    while (id.length() < ID_LENGTH) {
        id.append(QString::number(rand() % 16, 16)[0]);
    }
    return id;
}
