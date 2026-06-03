/**
 * @file Pulley.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

#include <memory>
#include "IRotationSink.h"
#include "Cylinder.h"
#include "RotationSource.h"

/**
 * Pulley class
 */
class Pulley : public IRotationSink
{
private:
    /// Left hub of the pulley
    cse335::Cylinder mLeftHub;

    /// Right hub of the pulley
    cse335::Cylinder mRightHub;

    /// The diameter of the pulley
    double mDiameter = 0;

    /// the total width of the pulley
    double mWidth = 0;

    /// Rotation for the pulley
    double mRotation = 0;

    /// The other pulley rotated by this pulley
    std::shared_ptr<Pulley> mSinkPulley;

    /// The rotation source of pulley
    RotationSource mSource;


public:
    Pulley(double diameter, double width);

    void SetRotation(double rotation) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void BeltTo(std::shared_ptr<Pulley> pulley);

    /**
     * Get the diameter of the pulley
     * @return diameter
     */
    double GetDiameter() {return mDiameter;}

    double GetBeltEndY();

    double GetBeltStart();

    /// Get a pointer to the source object
    /// @return Pointer to RotationSource object
    RotationSource *GetSource() { return &mSource; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
