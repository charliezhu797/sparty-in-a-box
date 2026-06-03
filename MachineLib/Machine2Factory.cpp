/**
 * @file Machine2Factory.cpp
 * @author Charlie Zhu
 */

#include "pch.h"
#include "Machine2Factory.h"
#include "Machine.h"
#include "Box.h"
#include "Sparty.h"
#include "Crank.h"
#include "Shaft.h"
#include "Pulley.h"
#include "Cam.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
Machine2Factory::Machine2Factory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}

/**
 * Factory method to create machine #2
 * @return
 */
std::shared_ptr<Machine> Machine2Factory::Create()
{
    // The machine itself
    auto machine = std::make_shared<Machine>();

    const int Shaft1Y = -70;
    const int Shaft2Y = -180;

    auto box = std::make_shared<Box>(mImagesDir, 250, 240);
    machine->AddComponent(box);

    auto sparty =
        std::make_shared<Sparty>(mImagesDir + L"/sparty2.png", 212, 260, 80, 15);
    machine->AddComponent(sparty);

    // The hand crank
    auto crank = std::make_shared<Crank>();
    crank->SetPosition(150, Shaft1Y);
    crank->SetSpeed(0.5);       // In turns per second

    // The first shaft
    auto shaft1 = std::make_shared<Shaft>();
    shaft1->SetPosition(-110, Shaft1Y);       // Left-center end of the shaft
    shaft1->SetSize(10, 280);                // Diameter, length
    shaft1->SetOffset(0.3);                 // Rotation offset so the
    // lines don't all line up
    machine->AddComponent(shaft1);

    // Connect crank to shaft
    crank->GetSource()->AddSink(shaft1);

    // Note: If you made sinks through composition rather than
    // inheriting an interface, your code would likely be more
    // like this:
    // crank->GetSource()->AddSink(shaft1->GetSink());

    // Add the crank after the shaft is added so it is on top of the shaft
    machine->AddComponent(crank);


    /*
     * The first pulley
     * @param diameter The pully diameter to draw
     * @param width The total width of the pulley
     */
    auto pulley1 = std::make_shared<Pulley>(30, 15);
    pulley1->SetPosition(-95, Shaft1Y);

    shaft1->GetSource()->AddSink(pulley1);


    // The second pulley
    auto pulley2 = std::make_shared<Pulley>(30, 15);
    pulley2->SetPosition(pulley1->GetX(), Shaft2Y);

    auto shaft2 = std::make_shared<Shaft>();
    shaft2->SetPosition(-110, Shaft2Y);       // Left-center end of the shaft
    shaft2->SetSize(10, 80);                // Diameter, length
    shaft2->SetOffset(0.3);                 // Rotation offset so the
    // lines don't all line up
    machine->AddComponent(shaft2);

    machine->AddComponent(pulley1);


    pulley1->BeltTo(pulley2);

    machine->AddComponent(pulley2);

    pulley2->GetSource()->AddSink(shaft2);

    auto cam = std::make_shared<Cam>(mImagesDir);
    cam->SetPosition(-70, Shaft2Y);     // Center of the cam
    cam->SetHoleAngle(0.44);            // How far the hole is from top-dead-center
    // in turns. This means the cam would need
    // to rotate 0.44 turns before the key drops.
    machine->AddComponent(cam);

    cam->AddKeyDrop(box);               // Key drop triggers the box
    cam->AddKeyDrop(sparty);            // Key drop triggers Sparty

    shaft2->GetSource()->AddSink(cam);




    return machine;
}
