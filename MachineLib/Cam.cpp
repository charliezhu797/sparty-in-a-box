/**
 * @file Cam.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include "Cam.h"

/// Width of the cam on the screen in pixels
const double CamWidth = 17;

/// Cam diameter
const double CamDiameter = 60;

/// Initial size of hole
const double HoleInitialSize = 3;

/// How big is the hole in the cam?
const double HoleSize = 8;

/// The key image
const std::wstring KeyImage = L"/key.png";

/// The key image size
const int KeyImageSize = 20;

/// The amount the key drops into the hole
const int KeyDrop = 10;

/**
 * Constructor
 * @param imagesDir
 */
Cam::Cam(std::wstring imagesDir)
{
    mKey.SetImage(imagesDir + KeyImage);
    mKey.Rectangle(-KeyImageSize/2, 0, KeyImageSize, KeyImageSize);
}

/**
 * Draw the cam
 * @param graphics
 */
void Cam::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Component::Draw(graphics);

    if (!mKeyDrop)
    {
        mKey.DrawPolygon(graphics, GetX(), GetY() - CamDiameter / 2);
    }

    else
    {
        mKey.DrawPolygon(graphics, GetX(), GetY() - CamDiameter / 2 + KeyDrop);
    }

    graphics->PushState();

    wxPen pen(*wxBLACK, 1);
    wxBrush brush(*wxWHITE);

    graphics->SetPen(pen);
    graphics->SetBrush(brush);

    graphics->DrawRectangle(GetX() - CamWidth / 2, GetY() - CamDiameter / 2, CamWidth, CamDiameter);

    brush = wxBrush(*wxBLACK);
    graphics->SetBrush(brush);

    double dist = mRotation * (CamDiameter / mAngle);
    double x = GetX();

    if (dist > (CamDiameter - HoleInitialSize / 2))
    {
        if (!mTriggered)
        {
            mKeyDrop = true;
        }

        Trigger();
        mTriggered = true;
    }

    if (dist > CamDiameter)
    {
        dist = CamDiameter;
    }

    double y = GetY() + CamDiameter / 2 - dist;
    double radius = HoleSize / 2;

    double height = (HoleInitialSize - 2 * radius) / (-mAngle / 2) * mRotation + HoleInitialSize;

    if (height > HoleSize)
    {
        height = -(HoleInitialSize - 2 * radius) / (-mAngle / 2) * mRotation + HoleInitialSize -
            (-(HoleInitialSize - 2 * radius) / (-mAngle / 2)) * mAngle;
    }

    if (dist >= CamDiameter)
    {
        height = HoleInitialSize;
        mKeyDrop = false;
    }

    graphics->Clip(GetX() - CamWidth / 2, GetY() - CamDiameter / 2, CamWidth, CamDiameter);

    graphics->DrawEllipse(x - radius, y - radius, 2 * radius, height);

    graphics->PopState();
}

/**
 * Set rotation for cam
 * @param rotation
 */
void Cam::SetRotation(double rotation)
{
    mRotation = rotation;
}

/**
 * How far the hole is from top-dead-center in turns.
 * @param angle Amount of turns cam needs before key drops
 */
void Cam::SetHoleAngle(double angle)
{
    mAngle = angle;
}

/**
 * Reset time for cam
 */
void Cam::Reset()
{
    Component::Reset();

    mRotation = 0;
    Untrigger();
    mKeyDrop = false;
    mTriggered = false;

}

/**
 * Add a triggerable to the vector
 * @param iTriggerable triggerable to add
 */
void Cam::AddKeyDrop(std::shared_ptr<ITriggerable> iTriggerable)
{
    mITriggerables.push_back(iTriggerable);
}

/**
 * Trigger the triggerables in vector
 */
void Cam::Trigger()
{
    for (auto triggerable : mITriggerables)
    {
        triggerable->Trigger();
    }
}

/**
 * Untrigger the triggerables when cam is reset
 */
void Cam::Untrigger()
{
    for (auto triggerable : mITriggerables)
    {
        triggerable->Untrigger();
    }
}

