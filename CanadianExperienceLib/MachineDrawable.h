/**
 * @file MachineDrawable.h
 * @author Charlie Zhu
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H

class MachineStartTimeDlg;

#include <machine-api.h>
#include <memory>
#include <string>
#include "Drawable.h"


/**
 * Adapter class to integrate machine system into CanadianExperience
 */
class MachineDrawable : public Drawable
{
private:
    /// system to be adapted
    std::shared_ptr<IMachineSystem> mSystem;

    /// The time at which machine starts to run
    int mStartTime = 0;

public:
    /// Default constructor (disabled)
    MachineDrawable() = delete;

    /// Copy constructor (disabled)
    MachineDrawable(const MachineDrawable &) = delete;

    /// Assignment operator
    void operator=(const MachineDrawable &) = delete;

    MachineDrawable(const std::wstring& name, const std::wstring& resourcesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint pos) override;

    void GetKeyframe() override;

    MachineDialog CreateDialog(wxFrame* frame);

    void SetPlacedPosition(wxPoint loc);

    /**
     * Getter for mStartTime
     * @return mStartTime
     */
    int GetStartTime() {return mStartTime;}

    /**
     * Setter for mStartTime
     * @param time time to set
     */
    void SetStartTime(int time) {mStartTime = time;}

    wxXmlNode* Save(wxXmlNode* root, std::wstring machineName);

    void Load(wxXmlNode* root, std::wstring leftOrRight);

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
