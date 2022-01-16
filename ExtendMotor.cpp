#include "ExtendMotor.h"

#include "Motor.h"

namespace spirit {

ExtendMotor::ExtendMotor()
{
    init();
}

void ExtendMotor::init()
{
    _duty_cycle   = 0.0F;
    _state        = default_state;
    _rise_level   = default_change_level;
    _fall_level   = default_change_level;
    _pulse_period = default_pulse_period;
    _ttl          = default_ttl;
    _decay        = default_decay;
}

void ExtendMotor::rise_level(ChangeLevel level)
{
    if ((static_cast<ChangeLevel>(0) <= level) && (level < ChangeLevel::TotalNum)) {
        _rise_level = level;
        _rise_unit  = convert_level(_rise_level);
    }
}

ChangeLevel ExtendMotor::rise_level() const
{
    return _rise_level;
}

void ExtendMotor::fall_level(ChangeLevel level)
{
    if ((static_cast<ChangeLevel>(0) <= level) && (level < ChangeLevel::TotalNum)) {
        _fall_level = level;
        _fall_unit  = convert_level(_fall_level);
    }
}

ChangeLevel ExtendMotor::fall_level() const
{
    return _fall_level;
}

void ExtendMotor::rise_unit(float value)
{
    if ((0.00F <= value) && (value <= 1.00F)) {
        _rise_unit = value;
    }
}

float ExtendMotor::rise_unit() const
{
    return _rise_unit;
}

void ExtendMotor::fall_unit(float value)
{
    if ((0.00F <= value) && (value <= 1.00F)) {
        _fall_unit = value;
    }
}

float ExtendMotor::fall_unit() const
{
    return _fall_unit;
}

void ExtendMotor::ttl(unsigned int millisec)
{
    _ttl = millisec;
}

unsigned int ExtendMotor::ttl() const
{
    return _ttl;
}

void ExtendMotor::decay(Decay value)
{
    if ((static_cast<Decay>(0) <= value) && (value < Decay::TotalNum)) {
        _decay = value;
    }
}

Decay ExtendMotor::decay() const
{
    return _decay;
}

float ExtendMotor::convert_level(ChangeLevel level)
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
        return 1.0F;
    }

    float value = 0.02F;
    for (int i = 0; i < static_cast<int>(level); i++) {
        value *= 0.7F;
    }

    return value;
}

}  // namespace spirit
