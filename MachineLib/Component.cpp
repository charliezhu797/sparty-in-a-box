/**
 * @file Component.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include "Component.h"


void Component::Update(double elapsedTime)
{

}

/**
 * Draw the component
 * @param graphics
 */
void Component::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

}

/**
 * Advance the system in time
 * @param delta time to advance
 */
void Component::Advance(double delta)
{

}

/**
 * Set position for component
 * @param x x location to set
 * @param y y location to set
 */
void Component::SetPosition(int x, int y)
{
    SetX(x);
    SetY(y);
}
