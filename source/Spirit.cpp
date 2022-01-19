#include "Spirit.h"

#include "SMPController.h"
#include "SpiritCANController.h"
#include "interfaces/interfaceBus.h"

namespace spirit {

Spirit::Spirit(interface::Bus &bus_controller) : _bus_controller(bus_controller)
{
}

int Spirit::write()
{
    _smp.decode(motor);
    _bus_controller.write(_smp);

    return 0;
}

}  // namespace spirit
