/**
 * @file ITriggerable.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ITRIGGERABLE_H
#define CANADIANEXPERIENCE_MACHINELIB_ITRIGGERABLE_H

#include "Component.h"

/**
 * Interface for classes that can be triggered by cam
 */
class ITriggerable : public Component
{
private:

public:
    /**
     * Trigger the triggerable
     */
    virtual void Trigger() = 0;

    /**
     * Untrigger the triggerable
     */
    virtual void Untrigger() = 0;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_ITRIGGERABLE_H
