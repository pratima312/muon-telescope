#include "TriangularBarSD.hh"
#include "TriangularBarHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

TriangularBarSD::TriangularBarSD(const G4String& name, const G4String& hitsCollectionName)
  : G4VSensitiveDetector(name)
{
  collectionName.insert(hitsCollectionName);
}

void TriangularBarSD::Initialize(G4HCofThisEvent* hce)

{
  fHitsCollection = new TriangularBarHitsCollection(SensitiveDetectorName, collectionName[0]);

  
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

  
  if (hcID < 0) {
    G4SDManager::GetSDMpointer()->AddNewDetector(this);
    hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }

  hce->AddHitsCollection(hcID, fHitsCollection);
}

G4bool TriangularBarSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  //G4cout<<"I am here"<<G4endl;
  G4double edep = step->GetTotalEnergyDeposit();

  if (edep == 0.) return false;

  auto* newHit = new TriangularBarHit();

  newHit->SetTrackID(step->GetTrack()->GetTrackID());
  newHit->SetEdep(edep);
  newHit->SetPos(step->GetPostStepPoint()->GetPosition());


  G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
  newHit->SetCopyNo(copyNo);

  G4String pvName = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
  newHit->SetPVName(pvName);

  fHitsCollection->insert(newHit);

  if (G4VVisManager::GetConcreteInstance()) {
    newHit->Draw();
  }


  return true;
}

void TriangularBarSD::EndOfEvent(G4HCofThisEvent*)
{
  {
    std::size_t nofHits = fHitsCollection->entries();
    G4cout << G4endl << "-------->Hits Collection: " << nofHits << " hits." << G4endl;
    for (std::size_t i = 0; i < nofHits; ++i) {
      (*fHitsCollection)[i]->Print();
    }
  }
}
