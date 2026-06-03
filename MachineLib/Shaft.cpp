/**
 * @file Shaft.cpp
 * @author Charlie Zhu
 */

#include"pch.h"
#include "Shaft.h"

/// The color to draw the shaft
const wxColour ShaftColor = wxColour(220, 220, 220);

/// The color to draw the lines on the shaft
/// First parameter to Cylinder::SetLines
const wxColour ShaftLineColor = wxColour(100, 100, 100);

/// The width to draw the lines on the shaft
/// Second parameter to Cylinder::SetLines
const int ShaftLinesWidth = 1;

/// The number of lines to draw on the shaft
/// Third parameter to Cylinder::SetLines
const int ShaftNumLines = 4;

/**
 * Constructor
 */
Shaft::Shaft()
{
    mCylinder.SetColour(ShaftColor);
    mCylinder.SetLines(ShaftLineColor, ShaftLinesWidth, ShaftNumLines);
}

/**
 * Set shaft's size
 * @param diameter diameter of shaft
 * @param length length of shaft
 */
void Shaft::SetSize(double diameter, double length)
{
    mCylinder.SetSize(diameter, length);
}

/**
 * Set the offset rotation for the shaft
 * @param offset offset to use
 */
void Shaft::SetOffset(double offset)
{
    mRotation += offset;
}

/**
 * Draw the shaft
 * @param graphics
 */
void Shaft::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Component::Draw(graphics);

    mCylinder.Draw(graphics, GetX(), GetY(), mRotation);
}

/**
 * Set rotation for the shaft
 * @param rotation rotation to set
 */
void Shaft::SetRotation(double rotation)
{
    mRotation = rotation;

    /// Set rotation for rotation sink for the shaft
    mSource.SetRotation(rotation);
}

