#ifndef PGA_HPP
#define PGA_HPP

#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace ne697 {
  class PGA: public G4VUserPrimaryGeneratorAction {
    public:
      PGA();
      ~PGA();

      void GeneratePrimaries(G4Event* event) override final;

    private:
      G4ParticleGun* m_gun;
  };
}

#endif