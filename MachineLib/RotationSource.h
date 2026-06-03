/**
 * @file RotationSource.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H

#include "IRotationSink.h"
#include <vector>
#include <memory>

/**
 * Rotation source class
 *
 * Base class for all classes that are a rotation source that
 * can cause other component to rotate
 */
class RotationSource
{
private:
    /// A collection of sinks the source can have
    std::vector<std::shared_ptr<IRotationSink>> mSinks {};

public:
    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    RotationSource();

    void AddSink(std::shared_ptr<IRotationSink> sink);

    void SetRotation(double rotation);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
