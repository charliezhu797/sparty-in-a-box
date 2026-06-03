/**
 * @file IRotationSink.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H

#include "Component.h"

/**
 * Base class for rotation sink
 *
 * Rotation sink can be rotated by other components
 */
class IRotationSink : public Component
{
private:

public:
    /**
     * Set rotation for the sink
     * @param rotation rotation value to set
     */
    virtual void SetRotation(double rotation) = 0;


};

#endif //CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
