#ifndef TriangularBarHit_h
#define TriangularBarHit_h 1

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4Threading.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4String.hh"
#include "globals.hh"

class TriangularBarHit : public G4VHit
{
public:
  TriangularBarHit() = default;
  TriangularBarHit(const TriangularBarHit&) = default;
  ~TriangularBarHit() override = default;

  TriangularBarHit& operator=(const TriangularBarHit&) = default;
  G4bool operator==(const TriangularBarHit&) const;

  inline void* operator new(size_t);
  inline void operator delete(void*);

  void Draw() override;
  void Print() override;

  void SetTrackID(G4int track) { fTrackID = track; }
  void SetEdep(G4double de) { fEdep = de; }
  void SetPos(const G4ThreeVector& xyz) { fPos = xyz; }

  void SetCopyNo(G4int c) { fCopyNo = c; }
  void SetPVName(const G4String& n) { fPVName = n; }

  G4int GetTrackID() const { return fTrackID; }
  G4double GetEdep() const { return fEdep; }
  G4ThreeVector GetPos() const { return fPos; }
  G4int GetCopyNo() const { return fCopyNo; }
  G4String GetPVName() const { return fPVName; }

private:
  G4int fTrackID = -1;
  G4double fEdep = 0.;
  G4ThreeVector fPos;

  // identification
  G4int fCopyNo = -1;
  G4String fPVName;
};

using TriangularBarHitsCollection = G4THitsCollection<TriangularBarHit>;

extern G4ThreadLocal G4Allocator<TriangularBarHit>* TriangularBarHitAllocator;

inline void* TriangularBarHit::operator new(size_t)
{
  if (!TriangularBarHitAllocator) TriangularBarHitAllocator = new G4Allocator<TriangularBarHit>;
  return (void*)TriangularBarHitAllocator->MallocSingle();
}

inline void TriangularBarHit::operator delete(void* hit)
{
  TriangularBarHitAllocator->FreeSingle((TriangularBarHit*)hit);
}

#endif

