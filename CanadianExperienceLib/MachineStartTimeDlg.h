/**
 * @file MachineStartTimeDlg.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTTIMEDLG_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTTIMEDLG_H

#include "MachineDrawable.h"

/**
 * dialog box to set machine start time
 */
class MachineStartTimeDlg final : public wxDialog
{
private:
    void OnOK(wxCommandEvent& event);

    /// the machine drawable on the left
    std::shared_ptr<MachineDrawable> mLeftMachineDrawable;

    /// the machine drawable on the right
    std::shared_ptr<MachineDrawable> mRightMachineDrawable;

    /// The start time of the machine on the left
    int mLeftStartTime = 0;

    /// The start time of the machine on the right
    int mRightStartTime = 0;


public:
    MachineStartTimeDlg(wxWindow* parent, std::shared_ptr<MachineDrawable> machineDrawable,
                        std::shared_ptr<MachineDrawable> rightMachineDrawable);


};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTTIMEDLG_H
