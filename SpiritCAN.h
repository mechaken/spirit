#ifndef SPIRIT_SPIRIT_CAN
#define SPIRIT_SPIRIT_CAN
#include "Spirit.h"
#include "mbed.h"

namespace spirit {

/** An Spirit CAN is used to controll Spirit CAN motor driver
 *
 * You can use as many separate Spirit objects as you require.
 *
 * Example:
 * @code
 * #include "SpiritCAN.h"
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
 *     SpiritCAN spirit[] = {
 *         SpiritCAN(can, 0, 0),
 *         SpiritCAN(can, 0, 1),
 *         SpiritCAN(can, 1, 0),
 *         SpiritCAN(can, 2),
 *     };
 *
 *     // モーター0のデューティー比の変化具合を設定
 *     spirit[0].motor.rise_level(ChangeLevel::Low);
 *     spirit[0].motor.fall_level(ChangeLevel::High);
 *
 *     while (true) {
 *         // 下のように、それぞれ設定したいモーターに
 *         // デューティー比と回転方向を入力していく
 *         // （モーターには書き込まれない）
 *         spirit[3].motor = 0.42F;
 *         spirit[3].motor = State::CW;
 *
 *         // m.write() が実行されて初めてモータードライバに設定値が送信される
 *         for (auto&& s : spirit) {
 *             int result = s.write();
 *
 *             debug_if(!result, "Couldn't write to can bus.\r");
 *             ThisThread::sleep_for(3ms);
 *         }
 *
 *         ThisThread::sleep_for(10ms);
 *     }
 * }
 * @endcode
 */
class SpiritCAN : public Spirit {
public:
    SpiritCAN(CAN& can, unsigned int dip, unsigned int number = 0);
    ~SpiritCAN();

private:
    interface::Bus* _bus_controller;
};

}  // namespace spirit

#endif
