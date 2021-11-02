#include "runaction.hpp"
#include "globals.hh"
#include "run.hpp"

namespace ne697 {
  RunAction::RunAction():
    G4UserRunAction()
    {
      G4cout << "Creating RunAction" << G4endl;
    }

  RunAction::~RunAction() {
    G4cout << "Deleting RunAction" << G4endl;
  }

  G4Run* RunAction::GenerateRun() {
    return new Run;
  }
  void RunAction::BeginOfRunAction(G4Run const*) {
    G4cout << "Starting a run!" << G4endl;
    return;
  }

  void RunAction::EndOfRunAction(G4Run const*) {
    G4cout << "Ending a run!" << G4endl;
    return;
  }
}