/**
 * @file Box.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BOX_H
#define CANADIANEXPERIENCE_MACHINELIB_BOX_H

#include <string>
#include <cmath>
#include "Component.h"
#include "Polygon.h"
#include "ITriggerable.h"

/**
 * Box class
 * a component of machine
 */
class Box : public ITriggerable
{
private:
    /// The box background image
    cse335::Polygon mBox;

    /// The lid image
    cse335::Polygon mLid;

    /// Position of lid relative to machine
    wxPoint mLidPosition;

    /// foreground image
    cse335::Polygon mForeground;

    /// the scale value used by lid
    double mOpenScale = 0.02;

    /// angle of lid
    double mAngle = 0;

    /// if the box should be open
    bool mOpen = false;

public:
    Box(std::wstring imagesDir, int boxSize, int lidSize);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Trigger() override;

    void Untrigger() override;

    void Advance(double delta) override;

    void Reset() override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BOX_H
