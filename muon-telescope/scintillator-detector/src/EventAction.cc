#include "EventAction.hh"
#include "RunAction.hh"
#include "TriangularBarHit.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"

#include <fstream>

// CSV file created once globally
static std::ofstream hitCSV("hits_1k_hspr.csv");

EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction)
{
    if (hitCSV.is_open())
    {
        hitCSV << "EventID,TrackID,CopyNo,PVName,Edep,PosX,PosY,PosZ\n";
    }
}

EventAction::~EventAction()
{
    if (hitCSV.is_open()) hitCSV.close();
}

void EventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
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

        if (hitCSV.is_open())
        {
            hitCSV << evtID             << ","
                   << hit->GetTrackID() << ","
                   << hit->GetCopyNo()  << ","
                   << hit->GetPVName()  << ","
                   << hit->GetEdep()    << ","
                   << hit->GetPos().x() << ","
                   << hit->GetPos().y() << ","
                   << hit->GetPos().z() << "\n";
        }
    }
}





