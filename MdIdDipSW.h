#ifndef SPIRIT_MD_ID_DIP_SW_H
#define SPIRIT_MD_ID_DIP_SW_H

#include "mbed.h"

namespace spirit {

class MdIdDipSW : public BusIn {
public:
    MdIdDipSW(PinName p0, PinName p1 = NC, PinName p2 = NC, PinName p3 = NC, PinName p4 = NC, PinName p5 = NC,
              PinName p6 = NC, PinName p7 = NC, PinName p8 = NC, PinName p9 = NC, PinName p10 = NC, PinName p11 = NC,
              PinName p12 = NC, PinName p13 = NC, PinName p14 = NC, PinName p15 = NC);

    MdIdDipSW(PinName pins[16]);

    int id(int number = 0) const;

private:
    int _rx_filter_id;

    static constexpr int offset_id = 0x300;  // 0x000 ~ 0x7E0
};

}  // namespace spirit

#endif  // SPIRIT_MD_ID_DIP_SW_H
