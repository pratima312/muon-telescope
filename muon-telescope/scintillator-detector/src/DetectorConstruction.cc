
#include "DetectorConstruction.hh"
#include "Layer.hh"
#include "TriangularBar.hh"

#include "TriangularBarSD.hh"

#include "G4NistManager.hh"
#include "G4Sphere.hh" 
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

    G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
    G4bool checkOverlaps = true;

    G4double innerRadius = 0 * m;
    G4double outerRadius = 0.7 * m;
    G4double startPhi    = 0 * deg;
    G4double deltaPhi    = 360 * deg;
    G4double startTheta  = 0 * deg;
    G4double deltaTheta  = 180 * deg;

    G4Sphere* solidWorld = new G4Sphere("World", 
                                        innerRadius, outerRadius, 
                                        startPhi, deltaPhi, 
                                        startTheta, deltaTheta);
                                        
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMaterial, "World");

    G4VisAttributes* worldVis = new G4VisAttributes();
    worldVis->SetVisibility(false); 
    logicWorld->SetVisAttributes(worldVis);

    // Place the World
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, checkOverlaps
    );


    //place the container
    G4double containerHalfSize = 400 * mm; 
    G4Box* solidContainer = new G4Box("Container_Solid", containerHalfSize, containerHalfSize, containerHalfSize);
    
    G4LogicalVolume* logicContainer = new G4LogicalVolume(solidContainer, worldMaterial, "Container_LV");
    
    G4VisAttributes* containerVis = new G4VisAttributes();
    containerVis->SetVisibility(false);
    logicContainer->SetVisAttributes(containerVis);

    fLayer1 = new Layer();
    fLayer2 = new Layer();

    G4RotationMatrix* layer1Rot = nullptr;
    G4ThreeVector layer1Pos(0, 0, 0);
   
    G4RotationMatrix* layer2Rot = new G4RotationMatrix();
    layer2Rot->rotateZ(90.* deg); 
    G4ThreeVector layer2Pos(0, 0, 17*mm); // Relative offset inside the container

    fLayer1->Place(logicContainer, layer1Pos, layer1Rot);
    fLayer2->Place(logicContainer, layer2Pos, layer2Rot);


    G4RotationMatrix* rotWhole = new G4RotationMatrix();
    rotWhole->rotateX(0 * deg);
    rotWhole->rotateY(0 * deg); 
    rotWhole->rotateZ(0 * deg);
    G4ThreeVector posWhole(0, 0, 0); // Center of the world

    new G4PVPlacement(
        rotWhole,        // The rotation of the whole detector
        posWhole,        // Position in the world
        logicContainer,  // The logical volume containing your layers
        "Detector_Whole",// Name
        logicWorld,      // Mother volume (World)
        false, 
        0, 
        checkOverlaps
    );

    return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
  auto* tribarSD = new TriangularBarSD("TriangularBarSD", "TriangularBarHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(tribarSD);
  SetSensitiveDetector("TriangularBarLV", tribarSD, true);
}

void DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit) && (maxStep > 0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}

void DetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps)
{
  fCheckOverlaps = checkOverlaps;
}