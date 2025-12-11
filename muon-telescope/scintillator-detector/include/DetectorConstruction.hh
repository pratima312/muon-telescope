#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"


// Forward declaration
class Layer;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    ~DetectorConstruction() override;
    
    // Mandatory method from base class
    G4VPhysicalVolume* Construct() override;
    G4LogicalVolume* fLogicWorld;
    //G4LogicalVolume* fScoringVolume = nullptr;
    // G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }


private:
    // Geometry components
    Layer* fLayer1 = nullptr;
    Layer* fLayer2 = nullptr;
   
   
    
};

#endif

