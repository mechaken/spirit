#ifndef SPIRIT_SPIRIT_CAN_TARGET_H
#define SPIRIT_SPIRIT_CAN_TARGET_H

#include "interfaces/interfaceBus.h"
#include "mbed.h"

namespace spirit {

class SpiritCANTarget : public interface::Bus {
public:
    SpiritCANTarget(CAN &can);

    int write(SMPController &data) override;

    int read() override;

    bool has_new_message();

    char *get_smp_data();

private:
    CAN & _can;
    char *_smp;

    bool _has_new_message;
};

}  // namespace spirit

#endif  // SPIRIT_SPIRIT_CAN_H
