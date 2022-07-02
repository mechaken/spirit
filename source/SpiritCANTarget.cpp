#include "SpiritCANTarget.h"

#include "SMPTarget.h"
#include "mbed.h"

namespace spirit {

SpiritCANTarget::SpiritCANTarget(CAN &can) : _can(can)
{
}

int SpiritCANTarget::write(SMPController &data)
{
    return 0;
}

int SpiritCANTarget::read()
{
    CANMessage msg;
    _can.read(msg);
    _smp = (char *)msg.data;

    _has_new_message = true;
    return 0;
}

bool SpiritCANTarget::has_new_message()
{
    if (_has_new_message) {
        _has_new_message = false;
        return true;
    } else {
        return false;
    }
}

char *SpiritCANTarget::get_smp_data()
{
    return _smp;
}

}  // namespace spirit
