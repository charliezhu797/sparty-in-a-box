/**
 * @file Crank.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include "Crank.h"

/// The width of the crank on the screen in pixels
const int CrankWidth = 10;

/// The depth of the crank away from the screen in pixels
const int CrankDepth = 20;

/// The length of the crank in pixels
const int CrankLength = 50;

/// The diameter to draw the crank handle
const int HandleDiameter = 7;

/// How long the handle is in pixels
const int HandleLength = 40;

/// How much to the left of the crank X the handle starts in pixels
const int HandleStartX = -10;

/// Crank color
const wxColour CrankColor = wxColour(220, 220, 220);

/// Line color for the rod
const wxColour CrankHandleLineColor = wxColour(100, 100, 100);

/**
 * Constructor
 */
Crank::Crank()
{
    mHandle.SetSize(HandleDiameter, HandleLength);
    mHandle.SetColour(CrankColor);
    mHandle.SetLines(CrankHandleLineColor, 1, 4);
}

/**
 * Draw the crank
 * @param graphics
 */
void Crank::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Component::Draw(graphics);

    // Draw the cylinder for the handle
    double handleY = GetY() + cos(mAngle) * (CrankLength);
    mHandle.Draw(graphics, GetX() + HandleStartX, handleY, mRotation);

    graphics->PushState();

    wxPen pen(*wxBLACK, 1);
    wxBrush brush(CrankColor);

    graphics->SetPen(pen);
    graphics->SetBrush(brush);

    // length of crank when rotating
    double rotatingCrankLen = cos(mAngle) * (CrankLength + 10);

    // Draw the rectangle for crank
    // GetX() = 150 and GetY = -180
    graphics->DrawRectangle(GetX(), GetY(), CrankWidth, rotatingCrankLen);

    graphics->PopState();

}



/**
 * setter for speed
 * @param speed speed to set
 */
void Crank::SetSpeed(double speed)
{
    mSpeed = speed;
}

/**
 * Advance the animation in time
 * @param delta Amount of time to advance in seconds
 */
void Crank::Advance(double delta)
{
    Component::Advance(delta);
    mRotation += delta * mSpeed;

    mSource.SetRotation(mRotation);

    double openAngle = M_PI;
    double closeAngle = 0;
    double timeToRotate1Turn = 1 / mSpeed;

    //Check if crank should be going up
    if(mRotating && mAngle < openAngle && mGoingUp)
    {
        // Going up is half a turn, so the time should be divided by 2
        mAngle += openAngle * delta / (timeToRotate1Turn / 2);

        if(mAngle >= openAngle)
        {
            mAngle = openAngle;
            mGoingUp = false;
        }
    }

    // Check if cran should be going down
    if (mRotating && mAngle > closeAngle && !mGoingUp)
    {
        mAngle -= openAngle * delta / (timeToRotate1Turn / 2);

        if (mAngle <= closeAngle)
        {
            mAngle = closeAngle;
            mGoingUp = true;
        }
    }
}

/**
 * Reset crank
 */
void Crank::Reset()
{
    Component::Reset();
    mAngle = 0;
    mRotation = 0;
    mGoingUp = true;
}


