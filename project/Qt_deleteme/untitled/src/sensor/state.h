#ifndef STATE_H
#define STATE_H

#include <QObject>


// Abstract encapsulation for sensor's inner state and mode
class State : public QObject
{
    Q_OBJECT
public:
    enum StateEnum{ Idle, Calibration, Normal };

    explicit State(QObject *parent = nullptr);

    virtual StateEnum getType() = 0;
    float getValue() const;
    void setValue(float);

signals:
    void updated(float);

protected:
    float value;

protected slots:
    virtual void update() = 0;
};


class IdleState : public State
{
    Q_OBJECT
public:
    explicit IdleState(QObject *parent = nullptr);

    StateEnum getType() override { return Idle; };

protected slots:
    void update() override {};
};


class CalibrationState : public State
{
    Q_OBJECT
public:
    explicit CalibrationState(QObject *parent = nullptr);
    ~CalibrationState();

    StateEnum getType() override { return Calibration; };

protected:
    void update() override;
    QTimer *repeater;
};


class NormalState : public State
{
    Q_OBJECT
public:
    explicit NormalState(QObject *parent = nullptr);
    ~NormalState();

    StateEnum getType() override { return Normal; };

protected:
    void update() override;
    QTimer *repeater;
};

#endif // STATE_H
