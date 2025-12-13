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
    G4Material* barMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SCINTILLATOR");

    G4RotationMatrix* rot1 = new G4RotationMatrix();           
    G4RotationMatrix* rot2 = new G4RotationMatrix(); rot2->rotateZ(90*deg); 
    G4RotationMatrix* rot3 = new G4RotationMatrix(); rot3->rotateY(180*deg);
    G4RotationMatrix* rot4 = new G4RotationMatrix(); rot4->rotateZ(90*deg); rot4->rotateY(180*deg);

    G4double layerSpacing = 150*mm;

    TriangularBar* barGreen  = new TriangularBar(barMaterial, 33, 500, 17, nullptr);
    TriangularBar* barYellow = new TriangularBar(barMaterial, 33, 500, 17, nullptr);


    bool greenLVcolored = false;
    bool yellowLVcolored = false;

    const std::array<G4String,3> layerPrefix = {"b","m","t"};      
    const std::array<G4String,4> subPrefix = {"bg","by","tg","ty"}; 

    G4int globalCopy = 0; 

    for (G4int layerIdx = 0; layerIdx < 3; ++layerIdx) {
        G4double zLayer = layerIdx * layerSpacing;
        for (G4int i = 0; i < 16; ++i) {
            G4String pvName = layerPrefix[layerIdx] + subPrefix[0] + std::to_string(i + 1); 
            G4ThreeVector barPos((-250*mm + i*33*mm), 0*mm, -150*mm + zLayer);
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

    for (G4int layerIdx = 0; layerIdx < 3; ++layerIdx) {
        G4double zLayer = -16.5*mm + layerIdx * layerSpacing;
        for (G4int i = 0; i < 16; ++i) {
            G4String pvName = layerPrefix[layerIdx] + subPrefix[0] + std::to_string(i + 1); 
            pvName = layerPrefix[layerIdx] + subPrefix[1] + std::to_string(i + 1); 
            G4ThreeVector barPos((-250*mm + 247.5*mm), -250*mm + i*33*mm, -150*mm + zLayer);
            barGreen->Place(motherLV, barPos, rot2, pvName, globalCopy);

          
            ++globalCopy;
        }
    }

    for (G4int layerIdx = 0; layerIdx < 3; ++layerIdx) {
        G4double zLayer = layerIdx * layerSpacing;
        for (G4int i = 0; i < 16; ++i) {
            G4String pvName = layerPrefix[layerIdx] + subPrefix[2] + std::to_string(i + 1); 
            G4ThreeVector barPos(-250*mm - 16.5*mm + i*33*mm, 0*mm, -150*mm + zLayer);
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

    for (G4int layerIdx = 0; layerIdx < 3; ++layerIdx) {
        G4double zLayer = -16.5*mm + layerIdx * layerSpacing;
        for (G4int i = 0; i < 16; ++i) {
            G4String pvName = layerPrefix[layerIdx] + subPrefix[3] + std::to_string(i + 1); 
            G4ThreeVector barPos(-250*mm + 247.5*mm, -266.5*mm + i*33*mm, -150*mm + zLayer);
            barYellow->Place(motherLV, barPos, rot4, pvName, globalCopy);

            ++globalCopy;
        }
    }

   
}
