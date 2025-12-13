#ifndef TriangularBarSD_h
#define TriangularBarSD_h 1

#include "TriangularBarHit.hh"

#include "G4VSensitiveDetector.hh"
#include "G4String.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class TriangularBarSD : public G4VSensitiveDetector
{
public:
  TriangularBarSD(const G4String& name, const G4String& hitsCollectionName);
  ~TriangularBarSD() override = default;

  void Initialize(G4HCofThisEvent* hitCollection) override;
  G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
  void EndOfEvent(G4HCofThisEvent* hitCollection) override;

private:
  TriangularBarHitsCollection* fHitsCollection = nullptr;
};

#endif

