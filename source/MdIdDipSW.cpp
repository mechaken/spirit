#include "MdIdDipSW.h"

#include "mbed.h"

namespace spirit {

MdIdDipSW::MdIdDipSW(PinName p0, PinName p1, PinName p2, PinName p3, PinName p4, PinName p5, PinName p6, PinName p7,
                     PinName p8, PinName p9, PinName p10, PinName p11, PinName p12, PinName p13, PinName p14,
                     PinName p15)
    : BusIn(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15)
{
    mode(PullDown);
    _rx_filter_id = read() * 16 + offset_id;
}

MdIdDipSW::MdIdDipSW(PinName pins[16]) : BusIn(pins)
{
    mode(PullDown);
    _rx_filter_id = read() * 16 + offset_id;
}

int MdIdDipSW::id(int number) const
{
    return _rx_filter_id + (number * 2);
}

}  // namespace spirit
