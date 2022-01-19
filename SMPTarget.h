#ifndef SPIRIT_SMP_TARGET_H
#define SPIRIT_SMP_TARGET_H

#include "Motor.h"

namespace spirit {

class SMPTarget {
public:
    int encode(char *data, Motor &motor);

    int decode(const char *data, Motor &motor);

private:
};

}  // namespace spirit

#endif  // SPIRIT_SMP_TARGET_H
