#include "TriangularBar.hh"
#include "G4Trd.hh"              // For trapezoidal shape
#include "G4SystemOfUnits.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"    // For visualization
#include "G4String.hh"
#include "G4NistManager.hh"
#include "G4ios.hh"


TriangularBar::TriangularBar(G4Material* material,
                             G4double width,
                             G4double height,
                             G4double length,
                             G4RotationMatrix* rotation)
                             
    : fWidth(width), fHeight(height), fLength(length), fMaterial(material), fRotation(rotation),
      fSolid(nullptr), fLogicalVolume(nullptr), fPhysicalVolume(nullptr)

      
{
    // Initialize pointers
    // fSolid = nullptr;
    // fLogicalVolume = nullptr;
    // fPhysicalVolume = nullptr; 

    if (!fMaterial) {
        G4NistManager* nist = G4NistManager::Instance();
        fMaterial = nist->FindOrBuildMaterial("G4_WATER");
    }

    // G4NistManager* nist = G4NistManager::Instance();
    // G4Material* barMaterial = nist->FindOrBuildMaterial("G4_WATER"); 
    
    fSolid = new G4Trd("TriangularBarSolid",
                       fWidth/2*mm,        // Half X at -z (16.5 mm)
                       0.0,             // Half X at +z (0 mm - tapers to point)
                       fHeight/2*mm,       // Half Y at -z (8.5 mm)
                       fHeight/2*mm,       // Half Y at +z (8.5 mm - constant)
                       fLength/2*mm);      // Half Z (250 mm)
}

TriangularBar::~TriangularBar()
{
    
}

 

void TriangularBar::Place(G4LogicalVolume* motherLV,
    const G4ThreeVector& position,
    G4RotationMatrix* rotation,
    const G4String& pvName,
    G4int copyNo)
{
 
    if (rotation) {
        fRotation = rotation;
    }

    
    if (!fLogicalVolume) {
        fLogicalVolume = new G4LogicalVolume(fSolid, fMaterial, "TriangularBarLV");
        
        
    }
    
    fPhysicalVolume = new G4PVPlacement(rotation,   // Rotation (use stored member)
                                    position,     // Position
                                    fLogicalVolume, //logical volume
                                    pvName,       
                                    motherLV,
                                    false,
                                    copyNo,       // use caller-provided copy number
                                    true);


                                    
                                    
}


