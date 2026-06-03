/**
 * @file MachineDrawable.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include "MachineDrawable.h"
#include "AnimChannelAngle.h"
#include "Timeline.h"
#include "MachineStartTimeDlg.h"

/**
 * Draw the machine by calling draw on machine system which is the adaptee
 * @param graphics
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mSystem->SetLocation(wxPoint(mPlacedPosition.x, mPlacedPosition.y));
    mSystem->DrawMachine(graphics);
}

/**
 * Hit test function for drawable
 * @param pos the position of the click
 * @return
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
    return false;
}

/**
 * Update keyframe of machine
 */
void MachineDrawable::GetKeyframe()
{
    Drawable::GetKeyframe();

    // Get timeline first in order to get the frame number
    AnimChannelAngle *channel = GetAngleChannel();
    Timeline *timeline = channel->GetTimeline();
    double curFrame = timeline->GetCurrentFrame();

    if (curFrame >= mStartTime)
    {
        mSystem->SetMachineFrame(curFrame - mStartTime);
    }
}

/**
 * constructor
 * @param name name of the drawable
 * @param resourcesDir the resource directory
 */
MachineDrawable::MachineDrawable(const std::wstring &name, const std::wstring& resourcesDir) : Drawable(name)
{
    MachineSystemFactory factory(resourcesDir);
    mSystem = factory.CreateMachineSystem();
    mSystem->SetFrameRate(15);
}

/**
 * Create a dialog box for choosing machine
 * @param frame frame of the menu item
 * @return MachineDialog object
 */
MachineDialog MachineDrawable::CreateDialog(wxFrame* frame)
{
    return MachineDialog(frame, mSystem);
}

/**
 * Set placed position
 * @param loc
 */
void MachineDrawable::SetPlacedPosition(wxPoint loc)
{
    mPlacedPosition = loc;
}

/**
 * Save attributes of machine drawable
 * @param root root node
 * @param machineName name of the machine
 * @return xml node that contains the attributes
 */
wxXmlNode* MachineDrawable::Save(wxXmlNode *root, std::wstring machineName)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"Machine");
    root->AddChild(itemNode);
    itemNode->AddAttribute(L"name", wxString::Format(wxT("%s"), machineName));
    itemNode->AddAttribute(L"startTime", wxString::Format(wxT("%i"), mStartTime));
    itemNode->AddAttribute(L"machineNumber", wxString::Format(wxT("%i"), mSystem->GetMachineNumber()));
    return itemNode;
}

/**
 * Load attributes of node
 * @param root node to load
 * @param leftOrRight left machine or right machine
 */
void MachineDrawable::Load(wxXmlNode *root, std::wstring leftOrRight)
{
    //
    // Traverse the children of the node
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        auto machineName = child->GetAttribute(L"name", L"");

        if (name == L"Machine" && machineName == leftOrRight)
        {
            mStartTime = wxAtoi(child->GetAttribute(L"startTime", L"0"));

            int machineNumber = wxAtoi(child->GetAttribute(L"machineNumber", L"1"));
            mSystem->ChooseMachine(machineNumber);
        }
    }
}


