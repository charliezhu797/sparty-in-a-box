/**
 * @file Box.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include <cmath>
#include "Box.h"

/// The background image to use
const std::wstring BoxBackgroundImage = L"/box-background.png";

/// The foreground image to use
const std::wstring BoxForegroundImage = L"/box-foreground.png";

/// The lid image to use
const std::wstring BoxLidImage = L"/box-lid.png";

/// The horizontal scale for the lid when the angle is zero
const double LidZeroAngleScale = 0.02;

/// How long it takes to up the lid in seconds
const double LidOpeningTime = 0.25;


/**
 * Constructor
 * @param imagesDir Directory containing the images
 * @param boxSize Size of the box in pixels (just the box, not the lid)
 * @param lidSize Size of the lid in pixels
 */
Box::Box(std::wstring imagesDir, int boxSize, int lidSize)
{
    mBox.Rectangle(-boxSize / 2, 0, boxSize, boxSize);
    mBox.SetImage(imagesDir + BoxBackgroundImage);

    mForeground.Rectangle(-boxSize / 2, 0, boxSize, boxSize);
    mForeground.SetImage(imagesDir + BoxForegroundImage);

    mLid.Rectangle(-lidSize / 2, 0, lidSize, lidSize);
    mLid.SetImage(imagesDir + BoxLidImage);
    mLidPosition = wxPoint(0, -boxSize);
}

/**
 * Draw the box
 * @param graphics
 */
void Box::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Component::Draw(graphics);
    mBox.DrawPolygon(graphics, GetX(), GetY());

    graphics->PushState();
    graphics->Translate(mLidPosition.x, mLidPosition.y);

    mOpenScale = 1.96 / M_PI * mAngle + 0.02;
    graphics->Scale(1, mOpenScale);

    mLid.DrawPolygon(graphics, 0, 0);

    graphics->PopState();
}

/**
 * Draw the foreground of the box
 * @param graphics
 */
void Box::DrawForeground(std::shared_ptr<wxGraphicsContext> graphics)
{
    Component::DrawForeground(graphics);
    mForeground.DrawPolygon(graphics, GetX(), GetY());
}

/**
 * Advance the animation in time
 * @param delta Amount of time to advance in seconds
 */
void Box::Advance(double delta)
{
    Component::Advance(delta);	// Upcall

    double openAngle = M_PI / 2;

    if(mOpen && mAngle < openAngle)
    {
        mAngle += openAngle * delta / LidOpeningTime;

        if(mAngle > openAngle)
        {
            mAngle = openAngle;
        }
    }
}

/**
 * Reset box
 */
void Box::Reset()
{
    Component::Reset();
    mAngle = 0;
}

/**
 * Trigger the box so the box opens
 */
void Box::Trigger()
{
    mOpen = true;
}

/**
 * Untrigger the box so the box won't open
 */
void Box::Untrigger()
{
    mOpen = false;
}
