#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
#include <cmath>

static std::ofstream truthPlaneCSV("mc_truth_plane_level_10k.csv");

// SteppingAction::SteppingAction(EventAction* eventAction)
// : fEventAction(eventAction)
SteppingAction::SteppingAction()
{
    if (truthPlaneCSV.is_open())
    {
        truthPlaneCSV
            << "EventID,TrackID,PDG,"
            << "Px,Py,Pz,P,"
            << "Theta,Phi,"
            << "X,Y,Z\n";
    }
}

SteppingAction::~SteppingAction()
{
    if (truthPlaneCSV.is_open())
        truthPlaneCSV.close();
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    if (!fScoringVolume)
    {
        const auto* det =
            static_cast<const DetectorConstruction*>(
                G4RunManager::GetRunManager()->GetUserDetectorConstruction());

        fScoringVolume = det->GetTriangularBarLV();
    }

    const G4Track* track = step->GetTrack();
    G4int pdg = track->GetDefinition()->GetPDGEncoding();
    if (pdg != 13 && pdg != -13)
        return;

//     const G4StepPoint* prePoint = step->GetPreStepPoint();
//     if (prePoint->GetStepStatus() != fGeomBoundary)
//         return;
// 
//     const G4LogicalVolume* volume =
//         prePoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

//     if (volume != fScoringVolume)
//         return;
    const G4StepPoint* prePoint  = step->GetPreStepPoint();
    const G4StepPoint* postPoint = step->GetPostStepPoint();

    const G4VPhysicalVolume* preVol  = prePoint->GetTouchableHandle()->GetVolume();
    const G4VPhysicalVolume* postVol = postPoint->GetTouchableHandle()->GetVolume();

    if (!postVol) return;

    if (preVol != postVol &&
    postVol->GetLogicalVolume() == fScoringVolume)
    {
    // Correct plane-level MC truth recording 
            G4int evtID =
                G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

            G4int trackID = track->GetTrackID();
        
        // Momentum
        G4ThreeVector pvec = track->GetMomentum();
        double px = pvec.x() / GeV;
        double py = pvec.y() / GeV;
        double pz = pvec.z() / GeV;
        double p  = pvec.mag() / GeV;


        // Angles (zenith from vertical)
        double theta = std::acos(std::abs(pz) / p);
        double phi   = std::atan2(py, px);

        // Position at entrance
        G4ThreeVector pos = prePoint->GetPosition();
        double x = pos.x() / m ;
        double y = pos.y() / m ;
        double z = pos.z() / m ;

        if (truthPlaneCSV.is_open())
        {
            truthPlaneCSV << evtID << ","
                        << trackID << ","
                        << pdg << ","
                        << px << "," << py << "," << pz << "," << p << ","
                        << theta << "," << phi << ","
                        << x << "," << y << "," << z
                        //<< pos.x() << "," << pos.y() << "," << pos.z()
                        << "\n";
        }
    }
}
