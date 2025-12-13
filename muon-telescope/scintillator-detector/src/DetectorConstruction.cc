
#include "DetectorConstruction.hh"
#include "Layer.hh"
#include "TriangularBar.hh"

#include "TriangularBarSD.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4String.hh"

#include "G4UserLimits.hh"

class TriangularBarSD;

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(), 
   fLayer1(nullptr) , 
   fLayer2(nullptr) 
{
}

DetectorConstruction::~DetectorConstruction()
{
    
    delete fLayer1;
    delete fLayer2;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

    // Material manager
    G4NistManager* nist = G4NistManager::Instance();

    // Materials
    G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* barMaterial   = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"); 


    // Overlap checking flag
    G4bool checkOverlaps = true;

    // World half-dimensions
    G4double worldX = 300 * mm;
    G4double worldY = 300 * mm;
    G4double worldZ = 300 * mm;

    
    G4Box* solidWorld = new G4Box("World", worldX, worldY, worldZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMaterial, "World");

    
    G4VisAttributes* worldVis = new G4VisAttributes();
    worldVis->SetVisibility(true);
    logicWorld->SetVisAttributes(worldVis);

    
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        nullptr,
        G4ThreeVector(),
        logicWorld,
        "World",
        nullptr,
        false,   
        0,
        checkOverlaps
    );

    fLayer1 = new Layer();
    fLayer2 = new Layer();

    G4RotationMatrix* layer1Rot = nullptr ;
    G4ThreeVector layer1Pos(0, 0, 0);
   
    G4RotationMatrix* layer2Rot = new G4RotationMatrix();
    layer2Rot->rotateZ(90.* deg); 
    G4ThreeVector layer2Pos(0, 0, 17*mm);
 
    fLayer1->Place(logicWorld, layer1Pos, layer1Rot);
    fLayer2->Place(logicWorld, layer2Pos, layer2Rot);

    return physWorld;
}


void DetectorConstruction::ConstructSDandField()
{
  // Sensitive detectors

  auto* tribarSD = new TriangularBarSD("TriangularBarSD", "TrackerHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(tribarSD);

  SetSensitiveDetector("TriangularBarLV", tribarSD, true);

  G4ThreeVector fieldValue = G4ThreeVector();
}



void DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit) && (maxStep > 0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}


void DetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps)
{
  fCheckOverlaps = checkOverlaps;
}



