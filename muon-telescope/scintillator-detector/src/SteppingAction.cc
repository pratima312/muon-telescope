#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


SteppingAction::SteppingAction(EventAction* eventAction)
: fEventAction(eventAction)
{}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const DetectorConstruction* detConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
   
  }

  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  if (volume != fScoringVolume) return;

  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);
}



