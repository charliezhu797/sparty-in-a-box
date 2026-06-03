/**
 * @file MachineSystem.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include "MachineSystem.h"
#include "Machine.h"
#include "MachineCFactory.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"

using namespace std;

/**
 * constructor
 * @param resourcesDir resource directory containing files we need
 */
MachineSystem::MachineSystem(wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    ChooseMachine(1);
}

/**
 * Draw the machine
 * @param graphics Graphics context to draw on.
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    // This will put the machine where it is supposed to be drawn
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);

    mMachine->Draw(graphics);


    graphics->PopState();
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystem::SetMachineFrame(int frame)
{
    if (frame < mFrame)
    {
        mFrame = 0;
        Reset();
    }

    while (mFrame < frame) {
        mFrame++;
        mTime = mFrame / mFrameRate;
        mMachine->Advance(1.0 / mFrameRate);
        mMachine->SetTime(mTime);
    }
}

/**
 * Set the frame rate for the machine
 * @param rate frame rate to set
 */
void MachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
}

/**
 * Set the machine number, creating the appropriate machine
 * @param machine Machine number
 */
void MachineSystem::ChooseMachine(int machine)
{
    mNumber = machine;

    if(machine == 1)
    {
        Machine1Factory machine1Factory(mResourcesDir);
        mMachine = machine1Factory.Create();
    }
    else
    {
        Machine2Factory machine2Factory(mResourcesDir);
        mMachine = machine2Factory.Create();
    }

}

/**
 * Get the machine number
 * @return machine number
 */
int MachineSystem::GetMachineNumber()
{
    return mNumber;
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystem::GetMachineTime()
{
    return 0;
}

/**
 * Set the flag of the machine
 * @param flag flag to set
 */
void MachineSystem::SetFlag(int flag)
{

}

/**
 * Reset all components to time 0
 */
void MachineSystem::Reset()
{
    mMachine->Reset();
}
