#include "pga.hpp"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"

namespace ne697 {
  PGA::PGA():
    G4VUserPrimaryGeneratorAction(),
    m_gun(new G4ParticleGun(1))
  {
    G4cout << "Creating PGA" << G4endl;
    m_gun->SetParticleDefinition(G4Gamma::Definition());
    m_gun->SetParticleEnergy(1.*MeV);
    m_gun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
    m_gun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  }

  PGA::~PGA() {
    G4cout << "Deleting PGA" << G4endl;
    delete m_gun;
  }

  void PGA::GeneratePrimaries(G4Event* event) {
    m_gun->GeneratePrimaryVertex(event);
    return;
  }
}