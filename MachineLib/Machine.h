/**
 * @file Machine.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

class Component;

#include <vector>
#include <memory>

/**
 * Machine class
 */
class Machine
{
private:
    /// collection of components
    std::vector<std::shared_ptr<Component>> mComponents;

public:
    void AddComponent(std::shared_ptr<Component> component);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void SetTime(double time);

    void Reset();

    void Advance(double delta);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
