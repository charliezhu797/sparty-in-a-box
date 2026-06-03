/**
 * @file Machine.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"

/**
 * Add a component to the component vector
 * @param component component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
    component->SetMachine(*this);
}

/**
 * Draw the machine
 * @param graphics
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto component : mComponents)
    {
//        component->DrawSpring()
        component->Draw(graphics);
    }
    for (auto component : mComponents)
    {
        component->DrawForeground(graphics);
    }
}

/**
 * Call SetTime on each component of machine
 * @param time time to set
 */
void Machine::SetTime(double time)
{
    for (auto component : mComponents)
    {
        component->SetTime(time);
    }
}

/**
 * Reset all components time to 0
 */
void Machine::Reset()
{
    for (auto component : mComponents)
    {
        component->Reset();
    }
}

/**
 * Advance the system in time
 * @param delta
 */
void Machine::Advance(double delta)
{
    for (auto component : mComponents)
    {
        component->Advance(delta);
    }
}
