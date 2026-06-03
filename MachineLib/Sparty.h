/**
 * @file Sparty.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SPARTY_H
#define CANADIANEXPERIENCE_MACHINELIB_SPARTY_H

#include <string>
#include "Polygon.h"
#include "Component.h"
#include "ITriggerable.h"

/**
 * Sparty class
 */
class Sparty : public ITriggerable
{
private:
    /// sparty image
    cse335::Polygon mSparty;

    /// The length of spring
    double mSpringLength = 50;

    /// Full length of spring
    double mSpringFullLength = 0;

    /// Width of spring
    double mSpringWidth = 0;

    /// Number of loops of spring
    int mNumOfLoops = 0;

    /// Should the spring spring out
    bool mSpringOut = false;

    /// Length of spring when compressed
    double mCompressedLength = 0;



public:
    Sparty(std::wstring image, int size, int springLength, int springWidth, int numLinks);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void DrawSpring(std::shared_ptr<wxGraphicsContext> graphics,
                    int x,
                    int y,
                    double length,
                    double width,
                    int numLinks);

    void Advance(double delta) override;

    void Reset() override;

    void Trigger() override;

    void Untrigger() override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_SPARTY_H
