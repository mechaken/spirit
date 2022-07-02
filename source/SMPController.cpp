#include "SMPController.h"

#include <cstdint>

#include "Motor.h"

namespace spirit {

int SMPController::encode(Motor &motor)
{
    update_duty_cycle_bits(_data, motor.duty_cycle());
    update_state_bits(_data, motor.state());
    update_change_level_bits(_data, motor.rise_level(), motor.fall_level());

    return 0;
}

int SMPController::decode(Motor &motor)
{
    return 0;
}

char *SMPController::get_data()
{
    return _data;
}

void SMPController::update_duty_cycle_bits(char *data, float value)
{
    // Clear DutyCycle bits
    data[0] &= 0x80;
    data[1] &= 0x00;
    data[2] &= 0x7F;

    // Set DutyCycle bits
    uint16_t duty_cycle_16bit = 65535 * value;  // 2^16 - 1 = 65535
    data[0] |= duty_cycle_16bit >> 9;
    data[1] |= (duty_cycle_16bit & 0x01FE) >> 1;
    data[2] |= (duty_cycle_16bit & 0x0001) << 7;
}

void SMPController::update_state_bits(char *data, State type)
{
    // Clear state bits
    data[2] &= 0x9F;

    // Set state bits
    data[2] |= static_cast<char>(type) << 5;
}

void SMPController::update_change_level_bits(char *data, ChangeLevel rise, ChangeLevel fall)
{
    // Clear change level bits
    // rise level
    data[2] &= 0xE3;
    // fall level
    data[2] &= 0xFC;
    data[3] &= 0x7F;

    // set change level bits
    // rise level
    data[2] |= static_cast<char>(rise) << 2;
    // fall level
    data[2] |= (static_cast<char>(fall) & 0x06) >> 1;
    data[3] |= (static_cast<char>(fall) & 0x01) << 7;
}

}  // namespace spirit
