#ifndef SPIRIT_TARGET_MOTOR_H
#define SPIRIT_TARGET_MOTOR_H

namespace spirit {

enum class State {
    Free,
    CW,   // Clock Wise
    CCW,  // Counter Clock Wise
    Brake,

    TotalNum,
};

/** A Motor is abstract base class for moving the motor
 */
class Motor {
public:
    Motor();

    /** Initialize data
     *
     */
    void init();

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

    static constexpr State default_state        = State::Brake;
    static constexpr float default_pulse_period = 0.00002F;
    static constexpr float default_frequency    = 1.0F / default_pulse_period;

    static constexpr float min_pulse_period = 1.0F / 60000.0F;  // 60khz
    static constexpr float max_pulse_period = 1.0F / 10.0F;     // 10hz

protected:
    float _duty_cycle;
    State _state;
    float _pulse_period;
};

}  // namespace spirit

#endif  // SPIRIT_TARGET_MOTOR_H
