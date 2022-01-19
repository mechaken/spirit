#include "SpiritCAN.h"

#include "Spirit.h"

namespace spirit {

SpiritCAN::SpiritCAN(CAN& can, unsigned int dip, unsigned int number) : Spirit(*_bus_controller)
{
    _bus_controller = new SpiritCANController(can, dip, number);
}

SpiritCAN::~SpiritCAN()
{
    delete _bus_controller;
}

}  // namespace spirit
