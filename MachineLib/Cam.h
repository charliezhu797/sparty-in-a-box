/**
 * @file Cam.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CAM_H
#define CANADIANEXPERIENCE_MACHINELIB_CAM_H

#include <string>
#include <vector>
#include <memory>
#include "IRotationSink.h"
#include "Polygon.h"
#include "ITriggerable.h"

/**
 * Cam class that can trigger other classes
 */
class Cam : public IRotationSink
{
private:
    /// rotation of cam
    double mRotation = 0;

    /// Amount of turns cam needs before key drops
    double mAngle = 0;

    /// key on top of cam
    cse335::Polygon mKey;

    /// Check if key should drop
    bool mKeyDrop = false;

    /// If all triggerables are triggered
    bool mTriggered = false;

    /// A vector of all triggerables
    std::vector<std::shared_ptr<ITriggerable>> mITriggerables {};

public:
    Cam(std::wstring imagesDir);

    void SetRotation(double rotation) override;

    void SetHoleAngle(double angle);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Reset() override;

    void AddKeyDrop(std::shared_ptr<ITriggerable> iTriggerable);

    void Trigger();

    void Untrigger();



};

#endif //CANADIANEXPERIENCE_MACHINELIB_CAM_H
