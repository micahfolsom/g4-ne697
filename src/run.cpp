#include "run.hpp"

namespace ne697 {
  Run::Run():
    G4Run()
    {
      G4cout << "Creating Run" << G4endl;
    }

  Run::~Run() {
    G4cout << "Deleting Run" << G4endl;
  }

  void Run::RecordEvent(G4Event const*) {
    return;
  }

  void Run::Merge(G4Run const*) {
    return;
  }
}