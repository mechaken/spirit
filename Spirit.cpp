#include "Spirit.h"

#include <cstdint>

#include "Motor.h"
#include "mbed.h"

namespace spirit {

Spirit::Spirit(CAN &can, unsigned int dip, unsigned int number)
    : _can(can)
{
    _normal_msg.id  = dip * 16 + number * 2 + offset_id_number;
    _normal_msg.len = 4U;
}

void Spirit::duty_cycle(float value)
{
    Motor::duty_cycle(value);
    update_duty_cycle_data();
}

Spirit &Spirit::operator=(const float value)
{
    duty_cycle(value);
    return *this;
}

void Spirit::state(State type)
{
    Motor::state(type);
    update_state_data();
}

Spirit &Spirit::operator=(const State type)
{
    state(type);
    return *this;
}

void Spirit::rise_level(ChangeLevel level)
{
    ExtendMotor::rise_level(level);
    update_change_level_data();
}

void Spirit::fall_level(ChangeLevel level)
{
    ExtendMotor::fall_level(level);
    update_change_level_data();
}

void Spirit::update_duty_cycle_data()
{
    uint16_t duty_cycle_16bit = 65535 * _duty_cycle;  // 2^16 - 1 = 65535

    // Clear DutyCycle bits
    _normal_msg.data[0] &= 0x80;
    _normal_msg.data[1] &= 0x00;
    _normal_msg.data[2] &= 0x7F;

    // Set DutyCycle bits
    _normal_msg.data[0] |= duty_cycle_16bit >> 9;
    _normal_msg.data[1] |= (duty_cycle_16bit & 0x01FE) >> 1;
    _normal_msg.data[2] |= (duty_cycle_16bit & 0x0001) << 7;
}

void Spirit::update_state_data()
{
    // Clear state bits
    _normal_msg.data[2] &= 0x9F;

    // Set state bits
    _normal_msg.data[2] |= static_cast<unsigned char>(_state) << 5;
}

void Spirit::update_change_level_data()
{
    // Clear DutyCycleChangeLevel bits
    _normal_msg.data[2] &= 0x1F;
    _normal_msg.data[3] &= 0x80;

    // Clear DutyCycleChangeLevel bits
    _normal_msg.data[2] |= static_cast<unsigned char>(_rise_level) << 2;
    _normal_msg.data[2] |= (static_cast<unsigned char>(_fall_level) & 0x06) >> 1;
    _normal_msg.data[3] |= (static_cast<unsigned char>(_fall_level) & 0x01) << 7;
}

int Spirit::write()
{
    return _can.write(_normal_msg);
}

}  // namespace spirit
