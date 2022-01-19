#include "Motor.h"

#include <cstddef>

#include "interfaces/interfaceMotor.h"

namespace spirit {

Motor::Motor()
    : _duty_cycle(0.00F),
      _state(default_state),
      _pulse_period(default_pulse_period),
      _rise_level(default_change_level),
      _fall_level(default_change_level),
      _ttl(default_ttl),
      _decay(default_decay)
{
}

void Motor::duty_cycle(float value)
{
    _duty_cycle = value;
}

Motor &Motor::operator=(const float value)
{
    duty_cycle(value);
    return *this;
}

Motor &Motor::operator+=(const float value)
{
    duty_cycle(_duty_cycle + value);
    return *this;
}

Motor &Motor::operator-=(const float value)
{
    duty_cycle(_duty_cycle - value);
    return *this;
}

float Motor::duty_cycle() const
{
    return _duty_cycle;
}

Motor::operator float()
{
    return duty_cycle();
}

void Motor::state(State type)
{
    if ((State::Begin <= type) && (type < State::End)) {
        _state = type;
    }
}

Motor &Motor::operator=(const State type)
{
    state(type);
    return *this;
}

State Motor::state() const
{
    return _state;
}

Motor::operator State()
{
    return state();
}

void Motor::pulse_period(float seconds)
{
    if ((min_pulse_period <= seconds) && (seconds <= max_pulse_period)) {
        _pulse_period = seconds;
    }
}

float Motor::pulse_period() const
{
    return _pulse_period;
}

void Motor::frequency(float hz)
{
    pulse_period(1.0F / hz);
}

void Motor::rise_level(ChangeLevel level)
{
    if ((ChangeLevel::Begin <= level) && (level < ChangeLevel::End)) {
        _rise_level = level;
        _rise_unit  = level2unit(_rise_level);
    }
}

ChangeLevel Motor::rise_level() const
{
    return _rise_level;
}

void Motor::fall_level(ChangeLevel level)
{
    if ((ChangeLevel::Begin <= level) && (level < ChangeLevel::End)) {
        _fall_level = level;
        _fall_unit  = level2unit(_fall_level);
    }
}

ChangeLevel Motor::fall_level() const
{
    return _fall_level;
}

void Motor::rise_unit(float value)
{
    if ((0.00F <= value) && (value <= 1.00F)) {
        _rise_unit = value;
    }
}

float Motor::rise_unit() const
{
    return _rise_unit;
}

void Motor::fall_unit(float value)
{
    if ((0.00F <= value) && (value <= 1.00F)) {
        _fall_unit = value;
    }
}

float Motor::fall_unit() const
{
    return _fall_unit;
}

void Motor::ttl(unsigned int millisec)
{
    _ttl = millisec;
}

unsigned int Motor::ttl() const
{
    return _ttl;
}

void Motor::decay(Decay type)
{
    if ((Decay::Begin <= type) && (type < Decay::End)) {
        _decay = type;
    }
}

Decay Motor::decay() const
{
    return _decay;
}

float Motor::level2unit(ChangeLevel level)
{
    // switch (level)
    // {
    // case ChangeLevel::Low:
    //     return 0.01f;
    // case ChangeLevel::Middle:
    //     return 0.005f;
    // case ChangeLevel::High:
    //     return 0.001f;
    // default:
    //     return 0.0f;
    // }

    if (level == ChangeLevel::OFF) {
        return 1.00F;
    }

    float value = 0.02F;
    for (size_t i = 0; i < static_cast<int>(level); i++) {
        value *= 0.7F;
    }

    return value;
}

}  // namespace spirit
