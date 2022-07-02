#include "A3921.h"

#include "Motor.h"

namespace spirit {

A3921::A3921(PinName sr, PinName pwmh, PinName pwml, PinName phase, PinName reset)
    : _sr(sr), _pwmh(pwmh), _pwml(pwml), _phase(phase), _reset(reset)
{
    awake();
}

void A3921::sleep()
{
    _reset = 0;

    set(0.00F, Motor::default_state);
}

void A3921::awake()
{
    _reset = 1;
}

void A3921::set(float duty_cycle, State state, Decay decay)
{
    if (decay == Decay::Slow) {
        switch (state) {
            case State::Free:
                _pwmh = 0.00F;
                _pwml = 0.00F;
                break;

            case State::CW:
                _phase = 1;  // a to b
                _pwmh  = duty_cycle;
                _pwml  = 1.00F;
                break;

            case State::CCW:
                _phase = 0;  // b to a
                _pwmh  = duty_cycle;
                _pwml  = 1.00F;
                break;

            case State::Brake:
                _pwmh = 0.00F;
                _pwml = 1.00F;
                break;

            default:
                break;
        }
    } else if (decay == Decay::Fast) {
        switch (state) {
            case State::Free:
                _pwmh = 0.00F;
                _pwml = 0.00F;
                break;

            case State::CW:
                _phase = 1;  // a to b
                _pwmh  = duty_cycle;
                _pwml  = duty_cycle;
                break;

            case State::CCW:
                _phase = 0;  // b to a
                _pwmh  = duty_cycle;
                _pwml  = duty_cycle;
                break;

            case State::Brake:
                _pwmh = 0.00F;
                _pwml = 0.00F;
                break;

            default:
                break;
        }
    }
}

void A3921::pulse_period(float seconds)
{
    if ((Motor::min_pulse_period <= seconds) && (seconds <= Motor::max_pulse_period)) {
        _pwmh.period(seconds);
        _pwml.period(seconds);
    }
}

void A3921::frequency(float hz)
{
    pulse_period(1.00F / hz);
}

}  // namespace spirit
