#include "Layer.hh"
#include "TriangularBar.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4VSolid.hh"

#include "G4String.hh"

#include <array>


Layer::Layer()   
    {

    }
    
Layer::~Layer()
{
    
}

void Layer::Place(G4LogicalVolume* motherLV,
    const G4ThreeVector& /*pos*/,
    G4RotationMatrix* /*rot*/)

    
{
    G4Material* barMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    G4RotationMatrix* rot1 = new G4RotationMatrix();           
    G4RotationMatrix* rot2 = new G4RotationMatrix(); rot2->rotateZ(90*deg); 
    G4RotationMatrix* rot3 = new G4RotationMatrix(); rot3->rotateY(180*deg);
    G4RotationMatrix* rot4 = new G4RotationMatrix(); rot4->rotateZ(90*deg); rot4->rotateY(180*deg);

    G4double layerSpacing = 150*mm;

    TriangularBar* barGreen  = new TriangularBar(barMaterial, 33, 528, 17, nullptr);
    TriangularBar* barYellow = new TriangularBar(barMaterial, 33, 528, 17, nullptr);


    bool greenLVcolored = false;
    bool yellowLVcolored = false;

    const std::array<G4String,3> layerPrefix = {"b","m","t"};      
    const std::array<G4String,4> subPrefix = {"tg","ty","bg","by"}; 
 

    G4int globalCopy = 0; 
 
    const G4double clearance = 0*mm;

static bool geometryBuilt1 = false; 
static bool geometryBuilt2 = false;
static bool geometryBuilt3 = false;
static bool geometryBuilt4 = false;


if (!geometryBuilt1) { 

    for (G4int layerIdx = 0; layerIdx < 3; ++layerIdx) {
        G4double zLayer = layerIdx * layerSpacing;
        
        for (G4int i = 0; i < 16; ++i) {
            G4String pvName = layerPrefix[layerIdx] + subPrefix[0] + std::to_string(i + 1); 
            
            G4ThreeVector barPos((-250*mm + i*(33*mm + clearance)), 0*mm + clearance, -150*mm + zLayer + clearance);
            
            barGreen->Place(motherLV, barPos, rot1, pvName, globalCopy);

            if (!greenLVcolored) {
                G4VisAttributes* visAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); 
                visAtt->SetForceSolid(true);
                barGreen->GetLogicalVolume()->SetVisAttributes(visAtt);
                greenLVcolored = true;
            }
            ++globalCopy;
        }
    }
    geometryBuilt1 = true; 
}



    if (!geometryBuilt2) {
        for (G4int layerIdx = 0; layerIdx < 3; ++layerIdx) {
            G4double zLayer = -17*mm + layerIdx * layerSpacing;
            for (G4int i = 0; i < 16; ++i) {
                G4String pvName = layerPrefix[layerIdx] + subPrefix[2] + std::to_string(i + 1); 
                G4ThreeVector barPos((-250*mm + 247.5*mm + clearance), -250*mm + i*(33*mm + clearance), -150*mm + zLayer + clearance);
                barGreen->Place(motherLV, barPos, rot2, pvName, globalCopy);

            
                ++globalCopy;
            }
        }
        geometryBuilt2 = true;
    }



   if (!geometryBuilt3) {
    for (G4int layerIdx = 0; layerIdx < 3; ++layerIdx) {
        G4double zLayer = layerIdx * layerSpacing;
        
        for (G4int i = 0; i < 16; ++i) {
            G4String pvName = layerPrefix[layerIdx] + subPrefix[1] + std::to_string(i + 1); 
            G4double xPos = -250*mm - 16.5*mm - (clearance/2.0) + i*(33*mm + clearance);
            G4ThreeVector barPos(xPos, 0*mm, -150*mm + zLayer + clearance);

            barYellow->Place(motherLV, barPos, rot3, pvName, globalCopy);

            if (!yellowLVcolored) {
                G4VisAttributes* visAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); 
                visAtt->SetForceSolid(true);
                barYellow->GetLogicalVolume()->SetVisAttributes(visAtt);
                yellowLVcolored = true;
            }
            ++globalCopy;
        }
    }
    geometryBuilt3 = true;
}


if (!geometryBuilt4) {
    for (G4int layerIdx = 0; layerIdx < 3; ++layerIdx) {
        G4double zLayer = -17*mm + layerIdx * layerSpacing;
        
        for (G4int i = 0; i < 16; ++i) {
            G4String pvName = layerPrefix[layerIdx] + subPrefix[3] + std::to_string(i + 1); 
            G4double yPos = -266.5*mm - (clearance/2.0) + i*(33*mm + clearance);
            G4ThreeVector barPos(-250*mm + 247.5*mm + clearance, 
                                 yPos, 
                                 -150*mm + zLayer + clearance);
                                 
            barYellow->Place(motherLV, barPos, rot4, pvName, globalCopy);

            ++globalCopy;
        }
    }
    geometryBuilt4 = true;
}
   
}
