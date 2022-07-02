#ifndef SPIRIT_SMP_CONTROLLER_H
#define SPIRIT_SMP_CONTROLLER_H

#include <cstddef>

#include "Motor.h"

namespace spirit {

class SMPController {
public:
    int encode(Motor &motor);

    int decode(Motor &motor);

    char *get_data();

private:
    char _data[4];

    static void update_duty_cycle_bits(char *data, float value);

    static void update_state_bits(char *data, State type);

    static void update_change_level_bits(char *data, ChangeLevel rise, ChangeLevel fall);

    static constexpr size_t max_data_size = 4;
};

}  // namespace spirit

#endif  // SPIRIT_SMP_CONTROLLER_H
