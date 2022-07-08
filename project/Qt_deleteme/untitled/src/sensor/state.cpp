#include "state.h"
#include <QTimer>
#include <QRandomGenerator>


State::State(QObject *parent)
    : QObject{parent}
{
    value = 0;
}

float State::getValue() const
{
    return value;
}

void State::setValue(float val)
{
    value = val;
}

IdleState::IdleState(QObject *parent)
    : State( parent )
{

}

CalibrationState::CalibrationState(QObject *parent)
    : State( parent )
{
    repeater = new QTimer(this);
    repeater->setInterval(1000);
    connect(repeater, SIGNAL(timeout()), this, SLOT(update()));
    repeater->start();
}

CalibrationState::~CalibrationState()
{
    delete repeater;
}

void CalibrationState::update()
{
    value += 0.1;
    emit updated(value);
}


NormalState::NormalState(QObject *parent)
    : State( parent )
{
    value = QRandomGenerator::global()->bounded(0, 124);
    repeater = new QTimer(this);
    repeater->setInterval(1000);
    connect(repeater, SIGNAL(timeout()), this, SLOT(update()));
    repeater->start();
}

NormalState::~NormalState()
{
    delete repeater;
}

void NormalState::update()
{
    value += QRandomGenerator::global()->generateDouble() - 0.5;
    emit updated(value);
}
