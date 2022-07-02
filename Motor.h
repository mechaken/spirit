#ifndef SPIRIT_EXTEND_MOTOR_H
#define SPIRIT_EXTEND_MOTOR_H

#include "interfaces/interfaceMotor.h"

namespace spirit {

enum class ChangeLevel {
    Begin  = 0,
    OFF    = 0,  // Direct
    Low    = 2,  // Rapid
    Middle = 4,
    High   = 6,
    Max    = 7,  // slow
    End,
};

enum class Decay {
    Begin = 0,
    Slow  = Begin,
    Mixed,
    Fast,
    End,
};

/** A Motor is abstract base class for moving the motor
 */
class Motor : public interface::Motor {
public:
    Motor();

    /** Set the duty cycle
     *
     * @param duty_cycle duty cycle to set
     */
    virtual void duty_cycle(float value);

    /** A shorthand for duty_cycle()
     * \sa Motor::duty_cycle()
     * @code
     *      Motor  motor;
     *      motor = 0.50F;
     * @endcode
     */
    virtual Motor &operator=(const float value);

    /** A shorthand for duty_cycle()
     * \sa Motor::duty_cycle()
     * @code
     *      Motor  motor;
     *      motor += 0.10F;
     * @endcode
     */
    virtual Motor &operator+=(const float value);

    /** A shorthand for duty_cycle()
     * \sa Motor::duty_cycle()
     * @code
     *      Motor  motor;
     *      motor -= 0.10F;
     * @endcode
     */
    virtual Motor &operator-=(const float value);

    /** Return the duty cycle
     *
     * @returns
     *    the duty cycle
     */
    float duty_cycle() const;

    /** A shorthand for duty_cycle()
     * \sa Motor::duty_cycle()
     * @code
     *      Motor  motor;
     *      float now_duty_cycle = motor;
     * @endcode
     */
    operator float();

    /** Set the state
     *
     * @param type state to set
     */
    virtual void state(State type);

    /** A shorthand for state()
     * \sa Motor::state()
     * @code
     *      Motor  motor;
     *      motor = State::CW;
     * @endcode
     */
    virtual Motor &operator=(const State type);

    /** Return the state
     *
     * @returns
     *    the state
     */
    State state() const;

    /** A shorthand for state()
     * \sa Motor::state()
     * @code
     *      Motor  motor;
     *      State now_state = motor;
     * @endcode
     */
    operator State();

    /** Set the pulse period
     *
     * @param seconds period to set
     */
    void pulse_period(float seconds);

    /** Return the pulse_period
     *
     * @returns
     *    the pulse_period
     */
    float pulse_period() const;

    /** Set the pulse frequency
     *
     * @param hz frequency to set
     */
    void frequency(float hz);

    /** Set the rise level
     *
     * @param level rise level to set
     */
    virtual void rise_level(ChangeLevel level);

    /** Return the rise level
     *
     * @returns
     *    the rise level
     */
    ChangeLevel rise_level() const;

    /** Set the fall level
     *
     * @param level fall level to set
     */
    virtual void fall_level(ChangeLevel level);

    /** Return the fall level
     *
     * @returns
     *    the fall level
     */
    ChangeLevel fall_level() const;

    /** Set the rise unit
     *
     * @param value rise unit to set
     */
    void rise_unit(float value);

    /** Return the rise unit
     *
     * @returns
     *    the rise unit
     */
    float rise_unit() const;

    /** Set the fall unit
     *
     * @param value fall unit to set
     */
    void fall_unit(float value);

    /** Return the fall unit
     *
     * @returns
     *    the fall unit
     */
    float fall_unit() const;

    /** Set the ttl(millisec)
     *
     * @param millisec time to set
     */
    void ttl(unsigned int millisec);

    /** return the ttl(millisec)
     *
     * @returns
     *   ttl(millisec)
     */
    unsigned int ttl() const;

    /** Set the control(LAP, SMB...)
     *
     * @param type to set
     */
    void decay(Decay type);

    /** return the control(LAP, SMB...)
     *
     * @returns
     *   decay
     */
    Decay decay() const;

    static constexpr ChangeLevel  default_change_level = ChangeLevel::OFF;
    static constexpr unsigned int default_ttl          = 100;
    static constexpr Decay        default_decay        = Decay::Slow;

protected:
    float        _duty_cycle;
    State        _state;
    float        _pulse_period;
    ChangeLevel  _rise_level;
    ChangeLevel  _fall_level;
    float        _rise_unit;
    float        _fall_unit;
    unsigned int _ttl;
    Decay        _decay;

    /** Convert level to unit
     *
     * @param level level to convert
     */
    static float level2unit(ChangeLevel level);
};

}  // namespace spirit

#endif  // SPIRIT_EXTEND_MOTOR_H
