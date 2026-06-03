/**
 * @file Sparty.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include "Sparty.h"

/// The spring pen size to use in pixels
const double SpringWireSize = 2;

/// Minimum spacing between spring wire
const double SpringWireMinSpacing = 1;

/// Color to draw the spring
const wxColour SpringColor = wxColour(220, 220, 220);

/// Sparty popup time in seconds
const double SpartyPopupTime = 0.25;


/**
 * The Sparty class constructor parameters are:
 * @param image Image file to load
 * @param size Size to draw Sparty (width and height)
 * @param springLength How long the spring is when fully extended in pixels
 * @param springWidth How wide the spring is in pixels
 * @param numLinks How many links (loops) there are in the spring
 */
Sparty::Sparty(std::wstring image, int size, int springLength, int springWidth, int numLinks)
{
//    mSparty.Rectangle(-size/2, -mSpringLength / 2, size, size);

    mCompressedLength = (SpringWireSize + SpringWireMinSpacing) * numLinks;
    mSpringFullLength = springLength;
    mSpringLength = mCompressedLength;
    mSpringWidth = springWidth;
    mNumOfLoops = numLinks;

//    mSparty.Rectangle(-size/2, -mSpringFullLength + compressedLength / 2, size, size);
    mSparty.Rectangle(-size/2, -mCompressedLength / 2, size, size);
    mSparty.SetImage(image);
}

/**
 * Draw sparty
 * @param graphics
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
//    DrawSpring(graphics, 0, 0, DecompressedLength, 85, 12);
//    DrawSpring(graphics, 0, 0, mSpringLength, 85, NumOfLoops);
    DrawSpring(graphics, 0, 0, mSpringLength, mSpringWidth, mNumOfLoops);

    Component::Draw(graphics);
    mSparty.DrawPolygon(graphics, GetX(), GetY());

}

/**
 * Draw a spring.
 * @param graphics Graphics context to render to
 * @param x X location of the bottom center of the spring in pixels
 * @param y Y location of the bottom center of the spring in pixels
 * @param length Length to draw the spring (bottom to top) in pixels
 * @param width Spring width in pixels
 * @param numLinks Number of links (loops) in the spring
 */
void Sparty::DrawSpring(std::shared_ptr<wxGraphicsContext> graphics,
                        int x, int y, double length, double width, int numLinks)
{
    auto path = graphics->CreatePath();

    // We keep track of three locations, the bottom of which
    // is y1. First half-loop will be y1 to y3, second half-loop
    // will be y3 to y2.
    double y1 = y;
    double linkLength = length / numLinks;

    // Left and right X values
    double xR = x + width / 2;
    double xL = x - width / 2;

    path.MoveToPoint(x, y1);

    for(int i=0; i<numLinks; i++)
    {
        auto y2 = y1 - linkLength;
        auto y3 = y2 - linkLength / 2;

        path.AddCurveToPoint(xR, y1, xR, y3, x, y3);
        path.AddCurveToPoint(xL, y3, xL, y2, x, y2);

        y1 = y2;
    }

    graphics->PushState();

    wxPen pen(SpringColor, SpringWireSize);
    graphics->SetPen(pen);
    graphics->StrokePath(path);
    graphics->PopState();
}

/**
 * Advance the animation in time
 * @param delta Amount of time to advance in seconds
 */
void Sparty::Advance(double delta)
{
    Component::Advance(delta);

    if (mSpringOut && mSpringLength < mSpringFullLength)
    {
        double dist = mSpringFullLength * delta / SpartyPopupTime;
        mSpringLength += dist;

        SetY(GetY() - dist);

        // Check if y position of sparty is already past its max height.
        if (GetY() < -mSpringFullLength + mCompressedLength / 2)
        {
            SetY(-mSpringFullLength + mCompressedLength);
        }

        if (mSpringLength > mSpringFullLength)
        {
            mSpringLength = mSpringFullLength;
        }
    }
}

/**
 * Reset Sparty
 */
void Sparty::Reset()
{
    Component::Reset();
    mSpringLength = mCompressedLength;
    SetY(0);
}

/**
 * Trigger Sparty so Sparty jumps out
 */
void Sparty::Trigger()
{
    mSpringOut = true;
}

/**
 * Untrigger Sparty so Sparty won't jump out
 */
void Sparty::Untrigger()
{
    mSpringOut = false;
}
