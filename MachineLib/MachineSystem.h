/**
 * @file MachineSystem.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H

class Machine;

#include "IMachineSystem.h"

/**
 * class for the machine system
 */
class MachineSystem : public IMachineSystem
{
private:
    /// Location of the machine
    wxPoint mLocation = wxPoint(0, 0);

    /// Machine number
    int mNumber;

    /// Frame rate of machine
    double mFrameRate = 30;

    /// Flag of machine
    int mFlag;

    /// Number of frame
    int mFrame = 0;

    /// machine of the system
    std::shared_ptr<Machine> mMachine;

    /// resource directory
    std::wstring mResourcesDir;

    /// time
    double mTime;


public:
//    virtual ~MachineSystem() {}
//
//    /** Default constructor disabled */
//    MachineSystem() = delete;
//    /** Copy constructor disabled */
//    MachineSystem(const MachineSystem &) = delete;
//    /** Assignment operator disabled */
//    void operator=(const MachineSystem &) = delete;

    MachineSystem(std::wstring resourcesDir);

    /**
     * Set location of machine
     * @param location location to set
     */
    void SetLocation(wxPoint location) override {mLocation = location;}

    /**
     * Get location of machine
     * @return location of machine
     */
    wxPoint GetLocation() override {return mLocation;}

    void Reset();

    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetMachineFrame(int frame) override;
    void SetFrameRate(double rate) override;
    void ChooseMachine(int machine) override;
    int GetMachineNumber() override;
    double GetMachineTime() override;
    void SetFlag(int flag) override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
