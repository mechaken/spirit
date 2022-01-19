#include "SMPTarget.h"

#include "Motor.h"

namespace spirit {

int SMPTarget::encode(char *data, Motor &motor)
{
    return 0;
}

int SMPTarget::decode(const char *data, Motor &motor)
{
    // if ((data[0] & 0x80) == 0x80) {
    float duty_cycle =
        (((data[0] & 0x7F) << 9) + (data[1] << 1) + ((data[2] & 0x80) >> 7)) / 65535.0F;  // 2^16 - 1 = 65535

    auto state = static_cast<State>((data[2] & 0x60) >> 5);

    auto rise_level = static_cast<ChangeLevel>((data[2] & 0x1C) >> 2);
    auto fall_level = static_cast<ChangeLevel>(((data[2] & 0x03) << 2) + (data[3] & 0x80));

    motor.duty_cycle(duty_cycle);
    motor.state(state);
    motor.rise_level(rise_level);
    motor.fall_level(fall_level);
    // }
    // else
    // {
    // // rps
    // ;
    // }

    return 0;
}

}  // namespace spirit
