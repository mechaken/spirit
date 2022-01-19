#ifndef SPIRIT_SPIRIT_CAN
#define SPIRIT_SPIRIT_CAN
#include "Spirit.h"
#include "mbed.h"

namespace spirit {

class SpiritCAN : public Spirit {
public:
    SpiritCAN(CAN& can, unsigned int dip, unsigned int number = 0);
    ~SpiritCAN();

private:
    interface::Bus* _bus_controller;
};

}  // namespace spirit

#endif
