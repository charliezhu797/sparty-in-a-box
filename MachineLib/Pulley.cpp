/**
 * @file Pulley.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include <cmath>
#include "Pulley.h"


/// How wide the hub is on each side of the pulley
const double PulleyHubWidth = 3;

/// How deep the belt is into the pulley
const double PulleyBeltDepth = 3;

/// The color to use for pulleys
const wxColour PulleyColor = wxColour(205, 250, 5);

/// The line color to use for the hub
/// First parameter to Cylinder::SetLines
const wxColour PulleyHubLineColor = wxColour(139, 168, 7);

/// The width to draw the lines on the hub
/// Second parameter to Cylinder::SetLines
const int PulleyHubLineWidth = 4;

/// The number of lines to draw on a pulley is the int(diameter / 6.0)
/// Third parameter to Cylinder::SetLines
const double PulleyHubLineCountDiviser = 6.0;

/**
 * Constructor
 * @param diameter the pulley diameter to draw
 * @param width the total width of the pulley
 */
Pulley::Pulley(double diameter, double width)
{
    mDiameter = diameter;
    mWidth = width;

    mLeftHub.SetColour(PulleyColor);
    mLeftHub.SetLines(PulleyHubLineColor, PulleyHubLineWidth, int(mDiameter / PulleyHubLineCountDiviser));
    mLeftHub.SetSize(diameter, PulleyHubWidth);

    mRightHub.SetColour(PulleyColor);
    mRightHub.SetLines(PulleyHubLineColor, PulleyHubLineWidth, int(mDiameter / PulleyHubLineCountDiviser));
    mRightHub.SetSize(diameter, PulleyHubWidth);
}

/**
 * Draw the pulley
 * @param graphics
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Component::Draw(graphics);

    mLeftHub.Draw(graphics, GetX() - mWidth / 2, GetY(), mRotation);
    mRightHub.Draw(graphics, GetX() + mWidth / 2, GetY(), mRotation);

    // Draw the belt
    if (mSinkPulley != nullptr)
    {
        // y position of top left of belt
        double startY = 0;
        // x position
        double startX = 0;

        // Length of belt
        double len = 0;

        if (mSinkPulley->GetY() > GetY())
        {
            startY = GetY() - mDiameter / 2 + PulleyBeltDepth;
            startX = GetX() - mWidth / 2 + PulleyHubWidth;
            len = abs(startY - mSinkPulley->GetBeltEndY());
        }

        else
        {
            startY = mSinkPulley->GetBeltStart();
            startX = mSinkPulley->GetX() - mWidth / 2 + PulleyHubWidth;
            double endY = GetY() + mDiameter / 2 - PulleyBeltDepth;
            len = abs(startY - endY);
        }

        graphics->PushState();

        wxPen pen(*wxBLACK, 1);
        wxBrush brush(*wxBLACK);

        graphics->SetPen(pen);
        graphics->SetBrush(brush);

        graphics->DrawRectangle(startX, startY, mWidth - PulleyHubWidth, len);

        graphics->PopState();

    }
}

/**
 * Set rotation for the pulley
 * @param rotation rotation to set
 */
void Pulley::SetRotation(double rotation)
{
    // Set the rotation for any source
    // for you to figure out
    mRotation = rotation;
    mSource.SetRotation(rotation);

    if (mSinkPulley != nullptr)
    {
        // Set the rotation for any pulley we
        // are connected to by a belt.
        // for you to figure out
        //If a pulley with radius N drives a pulley with radius M using the belt,
        // the speed of the second pulley is N/M times the speed of the first pulley.

        // radius of source pulley
        double n = mDiameter / 2;
        // radius of sink pulley
        double m = mSinkPulley->GetDiameter() / 2;
        // Calculate rotation for sink pulley
        double newRotation = n / m * rotation;

        mSource.SetRotation(newRotation);

    }
}

/**
 * Set connection between pulleys
 * @param pulley pulley to connect with
 */
void Pulley::BeltTo(std::shared_ptr<Pulley> pulley)
{
    mSinkPulley = pulley;
    (&mSource)->AddSink(mSinkPulley);
}

/**
 * Get the end y position of the belt
 * @return end y position
 */
double Pulley::GetBeltEndY()
{
    if (mSinkPulley == nullptr)
    {
        double endY = GetY() + mDiameter / 2 - PulleyBeltDepth;
        return endY;
    }
    return 0;
}

/**
 * Get the start y position of the belt
 * @return start y position
 */
double Pulley::GetBeltStart()
{
    if (mSinkPulley == nullptr)
    {
        double startY = GetY() - mDiameter / 2 + PulleyBeltDepth;
        return startY;
    }
    return 0;
}



