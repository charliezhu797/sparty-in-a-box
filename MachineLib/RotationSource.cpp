/**
 * @file RotationSource.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include "RotationSource.h"

/**
 * Constructor
 */
RotationSource::RotationSource()
{

}

/**
 * Add a sink to the sink vector
 * @param sink sink to add
 */
void RotationSource::AddSink(std::shared_ptr<IRotationSink> sink)
{
    mSinks.push_back(sink);
}

/**
 * Set rotation for all the rotation sinks it has
 * @param rotation rotation to set
 */
void RotationSource::SetRotation(double rotation)
{
    for (auto sink : mSinks)
    {
        sink->SetRotation(rotation);
    }
}
