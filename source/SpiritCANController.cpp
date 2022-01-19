#include "SpiritCANController.h"

#include "SMPController.h"

namespace spirit {

SpiritCANController::SpiritCANController(CAN &can, unsigned int dip, unsigned int number) : _can(can)
{
    _id  = dip * 16U + number * 2U + offset_id_number;
    _len = 4U;
}

int SpiritCANController::write(SMPController &data)
{
    CANMessage msg(_id, data.get_data(), _len);
    _can.write(msg);
    return 0;
}

int SpiritCANController::read()
{
    return 0;
}

}  // namespace spirit
