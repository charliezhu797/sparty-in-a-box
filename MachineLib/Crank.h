/**
 * @file Crank.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CRANK_H
#define CANADIANEXPERIENCE_MACHINELIB_CRANK_H

#include <cmath>
#include "Component.h"
#include "Cylinder.h"
#include "RotationSource.h"

/**
 * Crank class
 */
class Crank : public Component
{
private:
    /// Handle of crank
    cse335::Cylinder mHandle;

    /// Turning speed of crank in turns per second
    double mSpeed = 0;

    /// Rotation angle in turns
    double mRotation = 0;

    /// Angle of crank in radians
    double mAngle = 0;

    /// If the crank is rotating
    bool mRotating = true;

    /// if crank is going up
    bool mGoingUp = true;

    /// Rotation source for this component
    RotationSource mSource;


public:
    Crank();

    void SetSpeed(double speed);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Advance(double delta) override;

    void Reset() override;

    /// Get a pointer to the source object
    /// @return Pointer to RotationSource object
    RotationSource *GetSource() { return &mSource; }



};

#endif //CANADIANEXPERIENCE_MACHINELIB_CRANK_H
