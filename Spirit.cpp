#include "Spirit.h"

#include <cstdint>

#include "Motor.h"
#include "mbed.h"

namespace spirit {

Spirit::Spirit(CAN &can, unsigned int dip, unsigned int number) : _can(can) {
  _normal_msg.id = dip * 16U + number * 2U + offset_id_number;
  _normal_msg.len = 4U;
}

void Spirit::duty_cycle(float value) {
  Motor::duty_cycle(value);
  update_duty_cycle_data(_normal_msg.data, _duty_cycle);
}

Spirit &Spirit::operator=(const float value) {
  duty_cycle(value);
  return *this;
}

void Spirit::state(State type) {
  Motor::state(type);
  update_state_data(_normal_msg.data, _state);
}

Spirit &Spirit::operator=(const State type) {
  state(type);
  return *this;
}

void Spirit::rise_level(ChangeLevel level) {
  ExtendMotor::rise_level(level);
  update_rise_level_data(_normal_msg.data, _rise_level);
}

void Spirit::fall_level(ChangeLevel level) {
  ExtendMotor::fall_level(level);
  update_fall_level_data(_normal_msg.data, _fall_level);
}

void Spirit::update_duty_cycle_data(unsigned char *data, float value) {
  uint16_t duty_cycle_16bit = 65535 * value; // 2^16 - 1 = 65535

  // Clear DutyCycle bits
  data[0] &= 0x80;
  data[1] &= 0x00;
  data[2] &= 0x7F;

  // Set DutyCycle bits
  data[0] |= duty_cycle_16bit >> 9;
  data[1] |= (duty_cycle_16bit & 0x01FE) >> 1;
  data[2] |= (duty_cycle_16bit & 0x0001) << 7;
}

void Spirit::update_state_data(unsigned char *data, State type) {
  // Clear state bits
  data[2] &= 0x9F;

  // Set state bits
  data[2] |= static_cast<unsigned char>(type) << 5;
}

void Spirit::update_rise_level_data(unsigned char *data, ChangeLevel level) {
  // Clear rise level bits
  data[2] &= 0xE3;

  // Clear rise level bits
  data[2] |= static_cast<unsigned char>(level) << 2;
}

void Spirit::update_fall_level_data(unsigned char *data, ChangeLevel level) {
  // Clear fall level bits
  data[2] &= 0xFC;
  data[3] &= 0x7F;

  // Clear fall level bits
  data[2] |= (static_cast<unsigned char>(level) & 0x06) >> 1;
  data[3] |= (static_cast<unsigned char>(level) & 0x01) << 7;
}

int Spirit::write() { return _can.write(_normal_msg); }

} // namespace spirit
