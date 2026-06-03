/**
 * @file MainFrame.cpp
 * @author Charles B. Owen
 */
#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

#include "MainFrame.h"

#include "ViewEdit.h"
#include "ViewTimeline.h"
#include "Picture.h"
#include "PictureFactory.h"
#include "MachineStartTimeDlg.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 * @param resourcesDir Directory path containing resources
 */
MainFrame::MainFrame(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{

}



/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");
#ifdef WIN32
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif

    auto sizer = new wxBoxSizer( wxVERTICAL );

    auto imagesDir = mResourcesDir + ImagesDirectory;

    mViewEdit = new ViewEdit(this);
    mViewTimeline = new ViewTimeline(this, imagesDir);

    sizer->Add(mViewEdit,1, wxEXPAND | wxALL );
    sizer->Add(mViewTimeline, 0, wxEXPAND | wxALL);

    SetSizer( sizer );
    Layout();

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnEditChooseMachineLeft, this, XRCID("EditChooseMachineLeft"));
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnEditChooseMachineRight, this, XRCID("EditChooseMachineRight"));
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnEditSetMachineStartTime, this, XRCID("EditSetStartTime"));



    //
    // Create the picture
    //
    PictureFactory factory;
    mPicture = factory.Create(mResourcesDir);

    // Tell the views about the picture
    mViewEdit->SetPicture(mPicture);
    mViewTimeline->SetPicture(mPicture);
}



/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
  Close(true);
}

/**
 * Application about box menu handler
 * @param event The menu command event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxDialog aboutDlg;
    wxXmlResource::Get()->LoadDialog(&aboutDlg, this, L"AboutDialog");
    aboutDlg.ShowModal();
}


/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mViewTimeline->Stop();
    Destroy();
}

/**
 * Choose which machine to display
 * @param event
 */
void MainFrame::OnEditChooseMachineLeft(wxCommandEvent &event)
{
    // Call dialog function in MachineDrawable to get a dialog object
    MachineDialog dialog = mPicture->GetMachineDrawable(true)->CreateDialog(this);

    if (dialog.ShowModal() == wxID_OK)
    {
        // A machine has been selected
        mPicture->UpdateObservers();

    }
}

/**
 * Choose which machine to display
 * @param event
 */
void MainFrame::OnEditChooseMachineRight(wxCommandEvent &event)
{
    // Call dialog function in MachineDrawable to get a dialog object
    MachineDialog dialog = mPicture->GetMachineDrawable(false)->CreateDialog(this);

    if (dialog.ShowModal() == wxID_OK)
    {
        // A machine has been selected
        mPicture->UpdateObservers();

    }
}

/**
 * Set machine start time
 * @param event
 */
void MainFrame::OnEditSetMachineStartTime(wxCommandEvent &event)
{
//    MachineStartTimeDlg dialog = mPicture->GetMachineDrawable(true)->CreateDlgForStartTime(this);
    MachineStartTimeDlg dialog = mPicture->CreateDlg(this);

    if(dialog.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Tmeline settings
        mPicture->UpdateObservers();
    }
}

