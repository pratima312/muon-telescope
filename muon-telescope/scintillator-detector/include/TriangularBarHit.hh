// #ifndef TriangularBarHit_h
// #define TriangularBarHit_h 1

// #include "G4Allocator.hh"
// #include "G4THitsCollection.hh"
// #include "G4Threading.hh"
// #include "G4ThreeVector.hh"
// #include "G4VHit.hh"


// /// Tracker hit class
// ///
// /// It defines data members to store the trackID, chamberNb, energy deposit,
// /// and position of charged particles in a selected volume:
// /// - fTrackID, fChamberNB, fEdep, fPos

// class TriangularBarHit : public G4VHit
// {
//   public:
//     TriangularBarHit() = default;
//     TriangularBarHit(const TriangularBarHit&) = default;
//     ~TriangularBarHit() override = default;

//     // operators
//     TriangularBarHit& operator=(const TriangularBarHit&) = default;
//     G4bool operator==(const TriangularBarHit&) const;

//     inline void* operator new(size_t);
//     inline void operator delete(void*);

//     // methods from base class
//     void Draw() override;
//     void Print() override;

//     // Set methods
//     void SetTrackID(G4int track) { fTrackID = track; };
//     //void SetChamberNb(G4int chamb) { fChamberNb = chamb; };
//     void SetEdep(G4double de) { fEdep = de; };
//     void SetPos(G4ThreeVector xyz) { fPos = xyz; };

//     // Get methods
//     G4int GetTrackID() const { return fTrackID; };
//     //G4int GetChamberNb() const { return fChamberNb; };
//     G4double GetEdep() const { return fEdep; };
//     G4ThreeVector GetPos() const { return fPos; };

//   private:
//     G4int fTrackID = -1;
//     //G4int fChamberNb = -1;
//     G4double fEdep = 0.;
//     G4ThreeVector fPos;
// };

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// using TriangularBarHitsCollection = G4THitsCollection<TriangularBarHit>;

// extern G4ThreadLocal G4Allocator<TriangularBarHit>* TriangularBarHitAllocator;

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// inline void* TriangularBarHit::operator new(size_t)
// {
//   if (!TriangularBarHitAllocator) TriangularBarHitAllocator = new G4Allocator<TriangularBarHit>;
//   return (void*)TriangularBarHitAllocator->MallocSingle();
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// inline void TriangularBarHit::operator delete(void* hit)
// {
//   TriangularBarHitAllocator->FreeSingle((TriangularBarHit*)hit);
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//  // namespace B2

// #endif

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

