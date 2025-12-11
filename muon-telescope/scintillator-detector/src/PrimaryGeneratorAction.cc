#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4UnitsTable.hh"
#include "G4Exception.hh"
#include "G4RunManager.hh"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cctype>
#include <cmath>

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : fParticleGun(nullptr)
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* muplus = pTable->FindParticle("mu+");
    if (muplus) fParticleGun->SetParticleDefinition(muplus);

    std::ifstream in("muon_1000.csv");  
    
    auto trim = [](std::string &s){
        const char* ws = " \t\n\r\f\v";
        size_t a = s.find_first_not_of(ws);
        if (a == std::string::npos) { s.clear(); return; }
        size_t b = s.find_last_not_of(ws);
        s = s.substr(a, b - a + 1);
    };

    std::streampos pos_before = in.tellg();
    std::string firstline;
    bool header_skipped = false;
    while (std::getline(in, firstline)) {
        if (firstline.find_first_not_of(" \t\r\n") == std::string::npos) { pos_before = in.tellg(); continue; }
        bool hasLetter = false;
        for (char c : firstline) { if (std::isalpha(static_cast<unsigned char>(c))) { hasLetter = true; break; } }
        if (!hasLetter) {
           
            in.seekg(pos_before);
        } else {
            
            header_skipped = true;
        }
        break;
    }

   
    std::string line;
    size_t lineno = 0;
    while (std::getline(in, line)) {
        lineno++;
        if (line.empty()) continue;
        if (!line.empty() && line.back() == '\r') line.pop_back();

        std::stringstream ss(line);
        auto read_double = [&](double &out)->bool{
            std::string tok;
            if (!std::getline(ss, tok, ',')) return false;
            trim(tok);
            if (tok.empty()) return false;
            try {
                size_t idx=0;
                out = std::stod(tok, &idx);
                if (idx != tok.size()) return false;
            } catch(...) { return false; }
            return true;
        };

        double v1,v2,v3,v4,v5,v6,v7,v8,v9;
        if (!read_double(v1)) continue;
        if (!read_double(v2)) continue;
        if (!read_double(v3)) continue;
        if (!read_double(v4)) continue;
        if (!read_double(v5)) continue;
        if (!read_double(v6)) continue;
        if (!read_double(v7)) continue;
        if (!read_double(v8)) continue;
        if (!read_double(v9)) continue;

  
        f_x.push_back(v1);
        f_y.push_back(v2);
        f_z.push_back(v3);
        f_px.push_back(v4);
        f_py.push_back(v5);
        f_pz.push_back(v6);
        f_phi.push_back(v7);
        f_theta.push_back(v8);
        f_charge.push_back(v9);
    }
    in.close();

    G4cout << "PrimaryGeneratorAction: loaded " << f_x.size()
           << " rows from muon_100.csv (header_skipped=" << (header_skipped? "yes":"no") << ")\n";
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    G4int evID = event->GetEventID();
    const size_t n = f_x.size();

    if (static_cast<size_t>(evID) >= n) {
        G4cerr << "PrimaryGeneratorAction: event " << evID << " >= CSV rows ("<< n <<"), skipping.\n";
        return;
    }
    size_t idx = evID % n;

    
    double x = f_x[idx];
    double y = f_y[idx];
    double z = f_z[idx];
    fParticleGun->SetParticlePosition(G4ThreeVector(x * mm, y * mm, z * mm));

    double px = f_px[idx];
    double py = f_py[idx];
    double pz = f_pz[idx];
    double p = std::sqrt(px*px + py*py + pz*pz);
    fParticleGun->SetParticleMomentumDirection( G4ThreeVector(px, py, pz).unit() );


    const double muonMass = 105.6583755; // MeV/c^2
    double E_total = std::sqrt(p*p + muonMass*muonMass); // MeV
    double kin = E_total - muonMass; // MeV
    
    fParticleGun->SetParticleEnergy(kin * MeV);

    if (!f_charge.empty()) {
        if (f_charge[idx] < 0) {
            fParticleGun->SetParticleDefinition(
                G4ParticleTable::GetParticleTable()->FindParticle("mu-"));
        } else {
            fParticleGun->SetParticleDefinition(
                G4ParticleTable::GetParticleTable()->FindParticle("mu+"));
        }
    }

    fParticleGun->GeneratePrimaryVertex(event);
}