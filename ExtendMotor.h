#ifndef SPIRIT_EXTEND_MOTOR_H
#define SPIRIT_EXTEND_MOTOR_H

#include "Motor.h"

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
class ExtendMotor : public Motor {
public:
    ExtendMotor();

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

    static constexpr auto  default_change_level = ChangeLevel::OFF;
    static constexpr float default_ttl          = 100.0F;
    static constexpr Decay default_decay        = Decay::Slow;

protected:
    ChangeLevel _rise_level;
    ChangeLevel _fall_level;
    float       _rise_unit;
    float       _fall_unit;
    int         _ttl;
    Decay       _decay;

    /** Convert level to unit
     *
     * @param level level to convert
     */
    static float level2unit(ChangeLevel level);
};

}  // namespace spirit

#endif  // SPIRIT_EXTEND_MOTOR_H
