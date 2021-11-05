#include "run.hpp"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4THitsCollection.hh"
#include "G4UnitsTable.hh"

namespace ne697 {
  Run::Run():
    G4Run(),
    m_hits()
  {
    G4cout << "Creating Run" << G4endl;
  }

  Run::~Run() {
    G4cout << "Deleting Run" << G4endl;
  }

  void Run::RecordEvent(G4Event const* event) {
    /****** GEANT4 BOILERPLATE ******/
    auto hc_id = G4SDManager::GetSDMpointer()->GetCollectionID("world_sd_hits");
    if (hc_id == -1) {
      G4cerr << "HC ID was < 0; it was not Initialize()'d!" << G4endl;
      return;
    }
    auto hc_ev = event->GetHCofThisEvent();
    if (!hc_ev) {
      G4cerr << "No hits collection for this event! ID: " << event->GetEventID()
            << G4endl;
      return;
    }
    auto hc = (G4THitsCollection<Hit>*)hc_ev->GetHC(hc_id);
    if (!hc) {
      G4cerr << "Failed to grab hits collection object" << G4endl;
      return;
    }
    /****** GEANT4 BOILERPLATE ******/
    // Ok, now we've got the container (which is a pointer)
    G4cout << "Event had " << hc->entries() << " hits" << G4endl;
    for (std::size_t ihit = 0; ihit < hc->entries(); ++ihit) {
      // (*hc)[ihit] means we FIRST de-reference hc with the *, then we access
      // the [ihit] element. The parentheses makes it so the de-reference happens
      // first, then we just have a vector-like object we can use [] on
      // Finally, we must also cast to our Hit; remember, Geant4 is keeping a
      // pointer to a G4VHit, which we inherit from with Hit
      auto hit_in = dynamic_cast<Hit*>((*hc)[ihit]);
      // Same as...
      //Hit* hit_in = dynamic_cast<Hit*>((*hc)[ihit]);
      hit_in->setEventID(event->GetEventID());
      G4cout << "Event ID: " << hit_in->getEventID() << "\n";
      G4cout << "Track ID: " << hit_in->getTrackID() << "\n";
      G4cout << "Parent ID: " << hit_in->getParentID() << "\n";
      G4cout << "Volume: " << hit_in->getVolume() << "\n";
      G4cout << "Particle: " << hit_in->getParticle() << "\n";
      G4cout << "Creator process: " << hit_in->getProcess() << "\n";
      G4cout << "Position: " << G4BestUnit(hit_in->getPosition(), "Length")
            << "\n";
      G4cout << "Energy: " << G4BestUnit(hit_in->getEnergy(), "Energy") << "\n";
      G4cout << "Time: " << G4BestUnit(hit_in->getTime(), "Time") << "\n"
            << G4endl;
      m_hits.push_back(*hit_in);
    }

    // Don't forget to call the base class RecordEvent! Geant4 does some
    // bookkeeping
    G4Run::RecordEvent(event);
    return;
  }

  void Run::Merge(G4Run const* from_run) {
    auto other_run = dynamic_cast<Run const*>(from_run);
    auto hits = other_run->getHits();
    for (auto& hit : hits) {
      m_hits.push_back(hit);
    }

    // Don't forget to call the base class Merge! Geant4 does some bookkeeping
    G4Run::Merge(from_run);
    return;
  }

  std::vector<Hit> Run::getHits() const {
    return m_hits;
  }
}
