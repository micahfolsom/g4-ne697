#include "sensitivedetector.hpp"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"

namespace ne697 {
  SensitiveDetector::SensitiveDetector(G4String const& name):
    G4VSensitiveDetector(name),
    m_id(-1),
    m_hitsCollection(nullptr)
    {
      /****** GEANT4 BOILERPLATE ******/
      G4String hc_name = name + "_hits";
      collectionName.insert(hc_name);
      /****** GEANT4 BOILERPLATE ******/
    }

    void SensitiveDetector::Initialize(G4HCofThisEvent* hc) {
      /****** GEANT4 BOILERPLATE ******/
      if (m_id < 0) { 
        m_id = GetCollectionID(0);
      } 
      // Create a hits collection for this SD
      m_hitsCollection = 
          new HitsCollection(SensitiveDetectorName, collectionName[0]);
      // Give the collection to the G4Event, so we can get it at the end
      // in Run::RecordEvent()
      hc->AddHitsCollection(m_id, m_hitsCollection);
      /****** GEANT4 BOILERPLATE ******/
      return;
    }

    bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
        auto track = step->GetTrack();
        // "must use class tag", G4VSensitiveDetector has a member function
        // called Hit() so this would be ambiguous
        auto hit = new ne697::Hit(
            track->GetTrackID(), track->GetParentID(), track->GetVolume()->GetName(),
            track->GetDefinition()->GetParticleName(),
            (track->GetCreatorProcess() ? track->GetCreatorProcess()->GetProcessName()
                                        : "generator"),
            track->GetPosition(), step->GetTotalEnergyDeposit(),
            track->GetGlobalTime());
        m_hitsCollection->insert(hit);
        return true;
    }
}
