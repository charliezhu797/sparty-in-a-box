/**
 * @file Machine2Factory.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H

#include <string>
#include <memory>
#include "Machine.h"

/**
 * Factory for machine 2
 */
class Machine2Factory
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

public:
    Machine2Factory(std::wstring resourcesDir);

    std::shared_ptr<Machine> Create();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
