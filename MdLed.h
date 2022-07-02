/*
  *This software includes the work that is distributed in the Apache License 2.0
  */

#ifndef SPIRIT_MD_LED_H
#define SPIRIT_MD_LED_H

#include <chrono>

#include "Motor.h"
#include "mbed.h"

namespace spirit {

class MdLed : public BusOut {
public:
    enum class Mode {
        Normal = 0,
        Alternate,   // ２つが同時に点滅
        Concurrent,  // 交互に点滅

        TotalNum,
    };

    MdLed(PinName p0, PinName p1);

    using BusOut::write;

    void write(State type);

    void mode(Mode type);

    void coordinate();

    void blinking_rate(int millisec);

    MdLed &operator=(const State type);
    MdLed &operator=(const Mode type);

private:
    Mode  _mode;
    Mutex _mutex;
    int   _interval;
    int   _counter;

    // 交互に点滅
    void alternately_blink();

    // ２つが同時に点滅
    void concurrently_blink();

    void lock() override;
    void unlock() override;

    static constexpr int  default_interval = 500;
    static constexpr Mode default_mode     = Mode::Normal;
};

}  // namespace spirit

#endif  // SPIRIT_MD_LED_H
