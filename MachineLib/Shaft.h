/**
 * @file Shaft.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SHAFT_H
#define CANADIANEXPERIENCE_MACHINELIB_SHAFT_H

#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "RotationSource.h"

/**
 * Shaft class
 */
class Shaft : public IRotationSink
{
private:
    /// Cylinder of shaft
    cse335::Cylinder mCylinder;

    /// Rotation for the shaft in turns
    double mRotation = 0;

    /// the rotation source the shaft is connected with
    RotationSource mSource;

public:
    Shaft();

    void SetSize(double diameter, double length);

    void SetOffset(double offset);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetRotation(double rotation) override;

    /// Get a pointer to the source object
    /// @return Pointer to RotationSource object
    RotationSource *GetSource() { return &mSource; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_SHAFT_H
