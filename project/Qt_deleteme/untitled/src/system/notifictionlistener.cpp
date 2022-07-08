#include "notifictionlistener.h"
#include <QDebug>

NotifictionListener::NotifictionListener(QObject *parent)
    : QObject{parent}
{

}

void NotifictionListener::notified(const Event &e)
{
    emit notify(e.sourceId + ": " + QString::number(e.value));
}

Event::Event(const QString &sourceId, float value)
    : sourceId(sourceId)
    , value(value)
{}
