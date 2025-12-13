#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"
#include "G4String.hh"
#include "G4Threading.hh"

// Forward declaration
class Layer;
class G4PhysicalVolume;
class G4Material;
class G4LogicalVolume;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    // Mandatory method from base class
    G4VPhysicalVolume* Construct() override;

    void ConstructSDandField() override;

    G4LogicalVolume* fLogicWorld = nullptr;

void SetMaxStep(G4double maxStep);
void SetCheckOverlaps(G4bool checkOverlaps);

private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    
    Layer* fLayer1 = nullptr;
    Layer* fLayer2 = nullptr;

    G4Material* fTargetMaterial = nullptr;
    G4LogicalVolume* fLogicTarget = nullptr;
    G4UserLimits* fStepLimit = nullptr;
    G4bool fCheckOverlaps = true;

};

#endif


