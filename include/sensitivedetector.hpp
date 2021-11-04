#ifndef SENSITIVE_DETECTOR_HPP
#define SENSITIVE_DETECTOR_HPP
#include "G4VSensitiveDetector.hh"
#include "hit.hpp"

namespace ne697 {
  class SensitiveDetector : public G4VSensitiveDetector {
  public:
    SensitiveDetector(G4String const& name);

    void Initialize(G4HCofThisEvent* hc) override final;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override final;

  private:
    int m_id;
    HitsCollection* m_hitsCollection;
  };
}

#endif