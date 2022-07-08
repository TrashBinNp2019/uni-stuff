#include "sensor.h"

Sensor::Sensor(const QString &id, SensorType _type, QObject *parent)
    : QObject( parent )
{
    ID = id;
    type = _type;
    state = std::make_unique<IdleState>();
    normalStateValue = -1;
    connect(state.get(), SIGNAL(updated(float)), this, SLOT(onUpdate(float)));
}

Sensor::Sensor(const QJsonObject &obj)
{
    ID = "aaaa";
    state = std::make_unique<IdleState>();
    connect(state.get(), SIGNAL(updated(float)), this, SLOT(onUpdate(float)));
    fromJson(obj);
}

Sensor::Sensor(const QDomElement &el)
{
    ID = "aaaa";
    state = std::make_unique<IdleState>();
    connect(state.get(), SIGNAL(updated(float)), this, SLOT(onUpdate(float)));
    fromXML(el);
}

void Sensor::changeMode(State::StateEnum target)
{
    disconnect(state.get(), SIGNAL(updated(float)), this, SLOT(onUpdate(float)));

    if (state->getType() == State::Normal) {
        normalStateValue = state->getValue();
    }

    switch (target) {
    case (State::StateEnum::Idle): {
        state = std::make_unique<IdleState>();
        emit modeChanged("Idle");
        break;
    }
    case (State::StateEnum::Calibration): {
        state = std::make_unique<CalibrationState>();
        emit modeChanged("Calibration");
        break;
    }
    case (State::StateEnum::Normal): {
        state = std::make_unique<NormalState>();
        if (normalStateValue != -1) {
            state->setValue(normalStateValue);
        }

        emit modeChanged("Normal");
        break;
    }
    }

    connect(state.get(), SIGNAL(updated(float)), this, SLOT(onUpdate(float)));
}

State::StateEnum Sensor::getMode() const
{
    return state->getType();
}

float Sensor::getValue() const
{
    return state->getValue();
}

QJsonObject Sensor::toJson() const
{
    QJsonObject obj{};

    obj["ID"] = ID;
    obj["type"] = type;
    obj["state"] = state->getType();
    obj["val"] = state->getValue();

    return obj;
}

void Sensor::fromJson(const QJsonObject &obj)
{
    if (!(obj.contains("ID") && obj["ID"].isString())
     || !(obj.contains("type") && obj["type"].isDouble())
     || !(obj.contains("val") && obj["val"].isDouble())
     || !(obj.contains("state") && obj["state"].isDouble()))
    {
        throw std::invalid_argument("Invalid JSON sensor object.");
    }

    ID = obj["ID"].toString();
    type = static_cast<SensorType>(obj["type"].toInt());
    changeMode(static_cast<State::StateEnum>(obj["state"].toInt()));
    state->setValue(obj["val"].toDouble());
}

void Sensor::toXML(QDomElement &el) const
{
    el.setAttribute("ID", ID);
    el.setAttribute("type", type);
    el.setAttribute("state", state->getType());
    el.setAttribute("val", state->getValue());
}

void Sensor::fromXML(const QDomElement &el)
{
    ID = el.attribute("ID", ID);
    type = static_cast<SensorType>(el.attribute("type", 0).toInt());
    changeMode(static_cast<State::StateEnum>(el.attribute("state", 0).toInt()));
    state->setValue(el.attribute("val", 0).toDouble());
}

void Sensor::onUpdate(float val)
{
    emit updated( {ID, val} );
}

const QString &Sensor::getID() const
{
    return ID;
}

Sensor::SensorType Sensor::getType() const
{
    return type;
}
