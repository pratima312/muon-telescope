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


Layer::Layer()   
    {

    }
    
Layer::~Layer()
{
    
}

void Layer::Place(G4LogicalVolume* motherLV,
    const G4ThreeVector& pos,
    G4RotationMatrix* rot)

{

    
    G4Material* barMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SCINTILLATOR");

    G4RotationMatrix* rot1 = new G4RotationMatrix();
    
    G4RotationMatrix* rot2 = new G4RotationMatrix();
    rot2->rotateZ(90*deg);

    G4double layerSpacing = 150*mm;

    
    for (int n = 0; n<3; ++n){
    G4double zLayer = n * layerSpacing;
    for (int i = 0; i < 16; ++i) {
                fTriangularBar = new TriangularBar(barMaterial,
                                                   33,    // Width
                                                   500,   // Height
                                                   17 );  // Length
        
                G4ThreeVector barPos((-250*mm + i*33*mm), 0*mm, -150*mm + zLayer);
                
                fTriangularBar->Place(motherLV, barPos, rot1);

                G4VisAttributes* visAtt =
                    new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); // green
                visAtt->SetForceSolid(true);
                fTriangularBar->GetLogicalVolume()->SetVisAttributes(visAtt);
            }
        }

        
    for (int n = 0; n<3; ++n){
    G4double zLayer = -16.5*mm + n * layerSpacing;
    for (int i = 0; i < 16; ++i) {
                fTriangularBar = new TriangularBar(barMaterial,
                                                33,    // Width
                                                500,   // Height
                                                17 );  // Length
        
                G4ThreeVector barPos((-250*mm + 247.5*mm), -250*mm + i*33*mm, -150*mm + zLayer);
                

                fTriangularBar->Place(motherLV, barPos, rot2);
        
                G4VisAttributes* visAtt =
                    new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); // green
                visAtt->SetForceSolid(true);
                fTriangularBar->GetLogicalVolume()->SetVisAttributes(visAtt);
                }
            }


    G4RotationMatrix* rot3 = new G4RotationMatrix();
    rot3->rotateY(180*deg);

    G4RotationMatrix* rot4 = new G4RotationMatrix();
    rot4->rotateZ(90*deg);
    rot4->rotateY(180*deg);



    for (int n = 0; n<3; ++n){
    G4double zLayer =  n * layerSpacing;
    for (int i = 0; i < 16; ++i) {
                fTriangularBar = new TriangularBar(barMaterial,
                                                    33,    // Width
                                                    500,   // Height
                                                    17 );  // Length
        
                G4ThreeVector barPos(-250*mm - 16.5*mm+i*33*mm, 0*mm, -150*mm + zLayer);
    
                fTriangularBar->Place(motherLV, barPos, rot3);
    
                G4VisAttributes* visAtt =
                    new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); // yellow
                visAtt->SetForceSolid(true);
                fTriangularBar->GetLogicalVolume()->SetVisAttributes(visAtt);
                }
            }
       
    for (int n = 0; n<3; ++n){
    G4double zLayer = -16.5*mm + n * layerSpacing;
    for (int i = 0; i < 16; ++i) {
                fTriangularBar = new TriangularBar(barMaterial,
                                                    33,    // Width
                                                    500,   // Height
                                                    17 );  // Length
        
                G4ThreeVector barPos(-250*mm + 247.5*mm, -266.5*mm + i*33*mm, -150*mm + zLayer);

            fTriangularBar->Place(motherLV, barPos, rot4);
        
                G4VisAttributes* visAtt =
                    new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); // yellow
                visAtt->SetForceSolid(true);
                fTriangularBar->GetLogicalVolume()->SetVisAttributes(visAtt);
                }
            }

    
}