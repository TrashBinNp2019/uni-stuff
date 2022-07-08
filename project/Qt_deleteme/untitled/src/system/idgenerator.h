#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <QString>
#include <QDebug>


// Singleton
// ID format: 4 character unique hex string incapsulated in a QString.

class IDGenerator
{
public:
    // should be public for some reason
    class Generator {
    public:
        Generator() {
            srand(time(nullptr));
        };

        QString generate();
    private:

    };

    static QString generate() {
        return instance->generate();
    };

private:
    static Generator *instance;
};

#endif // IDGENERATOR_H
