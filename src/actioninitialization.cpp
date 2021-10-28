#include "actioninitialization.hpp"
#include "globals.hh"

namespace ne697 {
  ActionInitialization::ActionInitialization():
    G4VUserActionInitialization()
  {
    G4cout << "Creating ActionInitialization" << G4endl;
  }

  ActionInitialization::~ActionInitialization() {
    G4cout << "Deleting ActionInitialization" << G4endl;
  }

  void ActionInitialization::BuildForMaster() const {
    return;
  }

  void ActionInitialization::Build() const {
    return;
  }
}
