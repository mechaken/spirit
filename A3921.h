#ifndef SPIRIT_A3921_H
#define SPIRIT_A3921_H

#include "Motor.h"
#include "mbed.h"

namespace spirit {

class A3921 {
public:
    A3921(PinName sr, PinName pwmh, PinName pwml, PinName phase, PinName reset);

    void sleep();
    void awake();

    void set(float duty_cycle, State state, Decay decay = Motor::default_decay);
    void pulse_period(float seconds);
    void frequency(float hz);

private:
    DigitalOut _sr;
    PwmOut     _pwmh;
    PwmOut     _pwml;
    DigitalOut _phase;
    DigitalOut _reset;
};

}  // namespace spirit

#endif  // SPIRIT_A3921_H
