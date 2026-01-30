#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"



RunAction::RunAction()
{
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fEdep2);

  if (G4Threading::IsMasterThread())
  {
    hitCSV.open("hits_10k_plane.csv");
    truthCSV.open("mc_truth_generator_level_10k_plane.csv");

    if (hitCSV.is_open())
      hitCSV << "EventID,TrackID,PDG,CopyNo,PVName,Edep,PosX,PosY,PosZ\n";

    if (truthCSV.is_open())
      truthCSV << "EventID,TrackID,Px,Py,Pz,P,Theta,Phi,X,Y,Z\n";
  }
}


RunAction::~RunAction()
{
  if (G4Threading::IsMasterThread())
  {
    if (hitCSV.is_open())   hitCSV.close();
    if (truthCSV.is_open()) truthCSV.close();
  }
}


void RunAction::BeginOfRunAction(const G4Run*)
{
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

}


void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4double edep  = fEdep.GetValue();
  G4double edep2 = fEdep2.GetValue();

  G4double rms = edep2 - edep*edep/nofEvents;
  if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;

  const DetectorConstruction* detConstruction
   = static_cast<const DetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  const PrimaryGeneratorAction* generatorAction
   = static_cast<const PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;

  if (IsMaster()) 
      {
    G4cout
      << G4endl
      << "-------------------- End of Run --------------------" << G4endl
      << " Number of events : " << nofEvents << G4endl
      << " Total Edep       : " << G4BestUnit(edep, "Energy") << G4endl
      << " RMS              : " << G4BestUnit(rms,  "Energy") << G4endl
      << "---------------------------------------------------"
      << G4endl;
  }
}

void RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}
