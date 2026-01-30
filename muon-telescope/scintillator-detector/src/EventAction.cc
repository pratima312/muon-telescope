#include "EventAction.hh"
#include "RunAction.hh"
#include "TriangularBarHit.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4SystemOfUnits.hh"

#include <cmath>
#include <fstream>

EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction),
  fEdep(0.)
{
    
}

EventAction::~EventAction()
{

}

// void EventAction::BeginOfEventAction(const G4Event*)
// {
//     fEdep = 0.;
//     fMCTruthHits.clear();
// }

void EventAction::BeginOfEventAction(const G4Event* event)
{
    fEdep = 0.;

    const G4PrimaryVertex* vtx = event->GetPrimaryVertex(0);
    if (!vtx) return;

    const G4PrimaryParticle* pp = vtx->GetPrimary();
    if (!pp) return;

    G4int evtID   = event->GetEventID();
    G4int trackID = 1; // Primary track always ID=1
     G4int pdg     = pp->GetPDGcode();

    double px = pp->GetPx() ;
    double py = pp->GetPy() ;
    double pz = pp->GetPz();
    double p = std::sqrt(px*px + py*py + pz*pz);
    if (p <= 0.) return; 


    double theta = std::acos(pz / p); 
    double phi   = std::atan2(py, px);

    G4ThreeVector pos = vtx->GetPosition();
    double x = pos.x() ;
    double y = pos.y() ;
    double z = pos.z() ;

    fRunAction->truthCSV
        << evtID << ","
        << trackID << ","
        << px << "," << py << "," << pz << "," << p << ","
        << theta << "," << phi << ","
        << pos.x() << "," << pos.y() << "," << pos.z()
        << "\n";
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    fRunAction->AddEdep(fEdep);

    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    if (!hce) return;

    static G4int hcID = -1;

    if (hcID < 0)
    {
        hcID = G4SDManager::GetSDMpointer()->GetCollectionID("TriangularBarHitsCollection");
        if (hcID < 0) return;
    }

    auto* hits = static_cast<TriangularBarHitsCollection*>(hce->GetHC(hcID));
    if (!hits) return;

    G4int evtID = event->GetEventID();
    G4int nHits = hits->entries();

    for (G4int i = 0; i < nHits; i++)
    {
        auto* hit = (*hits)[i];
 
        fRunAction->hitCSV
            << evtID << ","
            << hit->GetTrackID() << ","
            << hit->GetPDG() << ","
            << hit->GetCopyNo() << ","
            << hit->GetPVName() << ","
            << hit->GetEdep() << ","
            << hit->GetPos().x() << ","
            << hit->GetPos().y() << ","
            << hit->GetPos().z()
            << "\n";
    }
}