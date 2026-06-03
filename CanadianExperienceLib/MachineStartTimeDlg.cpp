/**
 * @file MachineStartTimeDlg.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include "MachineStartTimeDlg.h"


/**
 * Constructor
 * @param parent The parent window we will center in
 * @param machineDrawable pointer to the machine drawable we are editing
 * @param rightMachineDrawable The machine on the right side
 */
MachineStartTimeDlg::MachineStartTimeDlg(wxWindow *parent, std::shared_ptr<MachineDrawable> machineDrawable,
                                         std::shared_ptr<MachineDrawable> rightMachineDrawable) : mLeftMachineDrawable(machineDrawable),
                                                                                  mRightMachineDrawable(rightMachineDrawable)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"SetStartTimeDialog");

    mLeftStartTime = mLeftMachineDrawable->GetStartTime();
    mRightStartTime = mRightMachineDrawable->GetStartTime();

    Bind(wxEVT_BUTTON, &MachineStartTimeDlg::OnOK, this, wxID_OK);

    auto LeftStartTimeCtrl = XRCCTRL(*this, "LeftStartTime", wxTextCtrl);
    wxIntegerValidator<int> LeftStartTimeValidator(&mLeftStartTime);
    LeftStartTimeValidator.SetRange(0, 100000);
    LeftStartTimeCtrl->SetValidator(LeftStartTimeValidator);

    auto RightStartTimeCtrl = XRCCTRL(*this, "RightStartTime", wxTextCtrl);
    wxIntegerValidator<int> RightStartTimeValidator(&mRightStartTime);
    RightStartTimeValidator.SetRange(0, 100000);
    RightStartTimeCtrl->SetValidator(RightStartTimeValidator);
}

/**
 * Handle an OK button press
 * @param event Button event
 */
void MachineStartTimeDlg::OnOK(wxCommandEvent &event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        mLeftMachineDrawable->SetStartTime(mLeftStartTime);
        mRightMachineDrawable->SetStartTime(mRightStartTime);

        EndModal(wxID_OK);
    }
}
