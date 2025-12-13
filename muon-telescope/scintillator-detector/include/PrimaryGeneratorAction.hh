
#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

#include <vector>

class G4ParticleGun;
class G4Event;
class G4Box;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* event) override;

private:
    G4ParticleGun* fParticleGun;
    G4double fBeamRadius;

    std::vector<double> f_x;
    std::vector<double> f_y;
    std::vector<double> f_z;

    std::vector<double> f_px;
    std::vector<double> f_py;
    std::vector<double> f_pz;

    std::vector<double> f_phi;
    std::vector<double> f_theta;
    std::vector<double> f_charge;
};

#endif

