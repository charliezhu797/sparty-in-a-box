/**
 * @file Component.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

#include<wx/gdicmn.h>
#include <memory>
#include <wx/graphics.h>
#include "Machine.h"

/**
 * Class for components of a machine
 */
class Component
{
private:
    /// Position of the component relative to the origin of the machine
    wxPoint mPosition = wxPoint(0, 0);

    /// Machine the component belongs to
    Machine mMachine;

    /// time of component
    double mTime = 0;

public:
    /**
     * Update Time
     * @param elapsedTime
     */
    virtual void Update(double elapsedTime);

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Set the machine
     * @param machine machine to set
     */
    void SetMachine(Machine machine) {mMachine = machine;}

    /**
     * Getter for x position
     * @return x position
     */
    double GetX() {return mPosition.x;}

    /**
     * Getter for y position
     * @return y position
     */
    double GetY() {return mPosition.y;}

    /**
     * Setter for x position
     * @param x position to set
     */
    void SetX(double x) {mPosition.x = x;}

    /**
     * Setter for y position
     * @param y position to set
     */
    void SetY(double y) {mPosition.y = y;}

    /**
     * Draw the foreground of the component
     * @param graphics
     */
    virtual void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) {}

    /**
     * Set time
     * @param time time to set
     */
    void SetTime(double time) {mTime = time;}

    /**
     * Reset time to 0
     */
    virtual void Reset() {mTime = 0;}

    virtual void Advance(double delta);

    virtual void SetPosition(int x, int y);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
