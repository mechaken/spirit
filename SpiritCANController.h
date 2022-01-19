#ifndef SPIRIT_SPIRIT_CAN_CONTROLLER_H
#define SPIRIT_SPIRIT_CAN_CONTROLLER_H

#include "interfaces/interfaceBus.h"
#include "mbed.h"

namespace spirit {

class SpiritCANController : public interface::Bus {
public:
    SpiritCANController(CAN &can, unsigned int dip, unsigned int number);

    int write(SMPController &data) override;

    int read() override;

private:
    CAN &         _can;
    unsigned int  _id;
    unsigned char _len;

    static constexpr int offset_id_number = 0x300;
};

}  // namespace spirit

#endif  // SPIRIT_SPIRIT_CAN_CONTROLLER_H
