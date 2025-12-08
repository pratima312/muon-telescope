#ifndef Layer_h
#define Layer_h 1

#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"


class TriangularBar;

class Layer
{
public:
   Layer();
   ~Layer();
   
   void Place(G4LogicalVolume* motherLV,
              const G4ThreeVector& pos,
              G4RotationMatrix* layerRot = nullptr);

   void Place(G4RotationMatrix* rotation =  nullptr);


        
   private:
   G4RotationMatrix* fRotation = nullptr;     
   TriangularBar* fTriangularBar = nullptr;
   
};
#endif


