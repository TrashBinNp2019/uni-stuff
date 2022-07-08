#ifndef NOTIFICTIONLISTENER_H
#define NOTIFICTIONLISTENER_H

#include <QObject>


struct Event;

// Object, used in system class for receiving notifications from sensors
class NotifictionListener : public QObject
{
    Q_OBJECT
public:
    explicit NotifictionListener(QObject *parent = nullptr);

signals:
    void notify(const QString&);

public slots:
    void notified(const Event&);
};


// Custom event structure, useful for encapsulating event information
struct Event
{
    Event(const QString &sourceId, float value);
    QString sourceId;
    float value;
};


#endif // NOTIFICTIONLISTENER_H
