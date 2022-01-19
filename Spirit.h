#ifndef SPIRIT_SPIIRT_H
#define SPIRIT_SPIIRT_H

#include "SMPController.h"
#include "SpiritCANController.h"
#include "interfaces/interfaceBus.h"
#include "mbed.h"

namespace spirit {

class Spirit {
public:
    Spirit(interface::Bus &bus_controller);

    int write();

    Motor motor;

private:
    SMPController   _smp;
    interface::Bus &_bus_controller;
};

}  // namespace spirit

#endif  // SPIRIT_SPIIRT_H
