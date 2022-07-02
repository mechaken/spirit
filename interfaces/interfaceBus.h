#ifndef SPIRIT_INTERFACE_INTERFACE_BUS_H
#define SPIRIT_INTERFACE_INTERFACE_BUS_H

#include "SMPController.h"

namespace spirit {

namespace interface {

struct Bus {
    virtual ~Bus() {};
    virtual int write(SMPController &data) = 0;
    virtual int read()                     = 0;
};

}  // namespace interface

}  // namespace spirit

#endif  // SPIRIT_INTERFACE_INTERFACE_BUS_H
