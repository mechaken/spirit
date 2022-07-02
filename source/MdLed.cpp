#include "MdLed.h"

#include <chrono>

#include "Motor.h"
#include "mbed.h"

namespace spirit {

MdLed::MdLed(PinName p0, PinName p1) : BusOut(p0, p1)
{
    _interval = default_interval;
    _mode     = default_mode;
}

void MdLed::write(State type)
{
    lock();
    _mode = Mode::Normal;
    write(static_cast<int>(type));
    unlock();
}

void MdLed::mode(Mode mode)
{
    if (_mode == mode) {
        return;
    }

    lock();

    _counter = 0;
    _mode    = mode;

    if (mode == Mode::Normal) {
        write(static_cast<int>(Motor::default_state));
    }
    unlock();
}

void MdLed::coordinate()
{
    if (_mode == Mode::Normal) {
        // 何もしない
    } else {
        if (++_counter >= _interval) {
            _counter = 0;
            if (_mode == Mode::Alternate) {
                alternately_blink();
            } else if (_mode == Mode::Concurrent) {
                concurrently_blink();
            }
        }
    }
}

MdLed &MdLed::operator=(const State type)
{
    write(type);
    return *this;
}

MdLed &MdLed::operator=(const Mode type)
{
    mode(type);
    return *this;
}

void MdLed::alternately_blink()
{
    if (read() == 0) {
        write(3);
    } else {
        write(0);
    }
}

void MdLed::concurrently_blink()
{
    if (read() == 1) {
        write(2);
    } else {
        write(1);
    }
}

void MdLed::lock()
{
    _mutex.lock();
}

void MdLed::unlock()
{
    _mutex.unlock();
}

}  // namespace spirit
