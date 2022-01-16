#include "Motor.h"

namespace spirit {

Motor::Motor()
    : _duty_cycle(0.0F), _state(default_state),
      _pulse_period(default_pulse_period) {}

void Motor::duty_cycle(float value) {
  if ((0.00F <= value) && (value <= 1.00F)) {
    _duty_cycle = value;
  }
}

Motor &Motor::operator=(const float value) {
  duty_cycle(value);
  return *this;
}

float Motor::duty_cycle() const { return _duty_cycle; }

Motor::operator float() { return duty_cycle(); }

void Motor::state(State type) {
  if ((State::Begin <= type) && (type < State::End)) {
    _state = type;
  }
}

Motor &Motor::operator=(const State type) {
  state(type);
  return *this;
}

State Motor::state() const { return _state; }

Motor::operator State() { return state(); }

void Motor::pulse_period(float seconds) {
  if ((min_pulse_period <= seconds) && (seconds <= max_pulse_period)) {
    _pulse_period = seconds;
  }
}

float Motor::pulse_period() const { return _pulse_period; }

void Motor::frequency(float hz) { pulse_period(1.0F / hz); }

} // namespace spirit
