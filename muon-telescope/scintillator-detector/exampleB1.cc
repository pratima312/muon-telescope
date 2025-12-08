#include "DetectorConstruction.hh"
//#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"

#include "QBBC.hh"     //physics list

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"



int main(int argc, char** argv)
{
    // Detect interactive mode (if no arguments) and define UI session
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }
    
    // Construct the run manager
    G4RunManager* runManager = new G4RunManager;
    
    // Set up mandatory user initialization classes
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new QBBC());  // Your physics
    
    
    
    // Initialize G4 kernel
    runManager->Initialize();
    
    // Initialize visualization manager
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    
    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if (!ui) {
        // Batch mode (command line)
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // Interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }
    
    // Clean up
    delete visManager;
    delete runManager;
}