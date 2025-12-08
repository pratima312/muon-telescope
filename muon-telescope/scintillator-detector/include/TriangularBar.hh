#ifndef TriangularBar_h
#define TriangularBar_h 1

#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "globals.hh"
#include "G4PVPlacement.hh"

class TriangularBar
{
public:
    // Constructor & destructor
    TriangularBar(G4Material* material,
                  G4double width,     // 33 mm (triangle base along X)
                  G4double height,    // 17 mm (triangle height along Y)
                  G4double length,
                  G4RotationMatrix* rotation = nullptr);  // 500 mm (extrusion along Z) 
    ~TriangularBar();
    
    
    void Place(G4LogicalVolume* motherLV,
        const G4ThreeVector& position = G4ThreeVector(0,0,0),
        G4RotationMatrix* rotation = nullptr,
        const G4String& pvName = "TriangularBarPV",
        G4int copyNo = 0);
    
    
    G4LogicalVolume* GetLogicalVolume() const { return fLogicalVolume; }
    G4VPhysicalVolume* GetPhysicalVolume() const { return fPhysicalVolume; }
    G4VSolid* GetSolid() const { return fSolid; }
    G4RotationMatrix* GetRotation() const { return fRotation; }

   
    G4double GetWidth() const { return fWidth; }
    G4double GetHeight() const { return fHeight; }
    G4double GetLength() const { return fLength; }

     
    
private:
    G4double fWidth;      // 33 mm
    G4double fHeight;     // 17 mm
    G4double fLength;     // 500 mm
    G4Material* fMaterial;
    G4RotationMatrix* fRotation;
    
    G4VSolid* fSolid;
    G4LogicalVolume* fLogicalVolume;
    G4VPhysicalVolume* fPhysicalVolume;
    
};

#endif

