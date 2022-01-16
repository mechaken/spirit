#ifndef SPIRIT_SPIRIT_H
#define SPIRIT_SPIRIT_H

#include "ExtendMotor.h"
#include "mbed.h"

namespace spirit {

/** An CAN Motor is used to controll CAN motor driver
 *
 * You can use as many separate Spirit objects as you require.
 *
 * Example:
 * @code
 * #include "Spirit.h"
 * #include "mbed.h"
 *
 * using namespace spirit;
 *
 * int main()
 * {
 *     BufferedSerial pc(USBTX, USBRX, 115200);
 *
 *     CAN can(p9, p10);
 *
 *     Spirit motor[] = {
 *         Spirit(can, 0, 0),
 *         Spirit(can, 0, 1),
 *         Spirit(can, 1, 0),
 *         Spirit(can, 2),
 *     };
 *
 *     // モーター0のデューティー比の変化具合を設定
 *     motor[0].rise_level(ChangeLevel::Low);
 *     motor[0].fall_level(ChangeLevel::High);
 *
 *     while (true) {
 *         // 下のように、それぞれ設定したいモーターに
 *         // デューティー比と回転方向を入力していく
 *         // （モーターには書き込まれない）
 *         motor[3] = 0.42F;
 *         motor[3] = State::CW;
 *
 *         // m.write() が実行されて初めてモータードライバに設定値が送信される
 *         for (auto&& m : motor) {
 *             int result = m.write();
 *
 *             debug_if(!result, "Couldn't write to can bus.\r");
 *             ThisThread::sleep_for(3ms);
 *         }
 *
 *         ThisThread::sleep_for(10ms);
 *     }
 * }
 *
 * @endcode
 */
class Spirit : public ExtendMotor {
public:
    /** Create a CAN Motor interface
     *
     * @param can connect to can pins
     * @param dip Slave DPI value
     * @param number Slave motor number
     */
    Spirit(CAN &can, unsigned int dip, unsigned int number = 0);

    /** Set the duty cycle
     *
     * @param duty_cycle duty cycle to set
     */
    void duty_cycle(float value) override;

    Spirit &operator=(const float value) override;

    /** Set the state
     *
     * @param type state to set
     */
    void state(State type) override;

    Spirit &operator=(const State type) override;

    /** Set the rise level
     *
     * @param level rise level to set
     */
    void rise_level(ChangeLevel level) override;

    /** Set the fall level
     *
     * @param level fall level to set
     */
    void fall_level(ChangeLevel level) override;

    /** Write a CANMessage to the bus.
     *
     *  @param msg The CANMessage to write.
     *
     *  @returns
     *    0 if write failed,
     *    1 if write successful
     */
    virtual int write(void);

protected:
    CAN &      _can;
    CANMessage _normal_msg;

    /** Update the duty cycle to MotorDriver
     *
     * @param duty_cycle duty cycle to update
     */
    static void update_duty_cycle_data(unsigned char *data, float value);

    /** Update the state to MotorDriver
     *
     * @param type state to update
     */
    static void update_state_data(unsigned char *data, State type);

    static void update_rise_level_data(unsigned char *data, ChangeLevel level);

    static void update_fall_level_data(unsigned char *data, ChangeLevel level);

    static constexpr int offset_id_number = 0x300;
};

}  // namespace spirit

#endif  // SPIRIT_SPIRIT_H
