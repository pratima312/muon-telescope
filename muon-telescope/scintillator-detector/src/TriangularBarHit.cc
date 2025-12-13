#include "TriangularBarHit.hh"

#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<TriangularBarHit>* TriangularBarHitAllocator = nullptr;


G4bool TriangularBarHit::operator==(const TriangularBarHit& right) const
{
  return (this == &right);
}

void TriangularBarHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if (!pVVisManager) return;

  G4Circle circle(fPos);
  circle.SetScreenSize(6.);
  circle.SetFillStyle(G4Circle::filled);
  
  G4Colour col(1.0, 0.0, 0.0); // red default
  if (fEdep > 1.*CLHEP::MeV) col = G4Colour(0.0, 1.0, 0.0); // green for higher energy
  G4VisAttributes attribs(col);
  circle.SetVisAttributes(attribs);

  pVVisManager->Draw(circle);
}


void TriangularBarHit::Print()
{
  G4cout << "TriangularBarHit: "
         << " trackID=" << fTrackID
         << " copyNo="  << fCopyNo
         << " pvName="  << fPVName
         << " Edep="    << std::setw(7) << G4BestUnit(fEdep, "Energy")
         << " Pos="     << std::setw(7) << G4BestUnit(fPos, "Length")
         << G4endl;
}
