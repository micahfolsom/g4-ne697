#include "geometrymessenger.hpp"
#include "detectorconstruction.hpp"
#include "G4UnitsTable.hh"

namespace ne697 {
  GeometryMessenger::GeometryMessenger(DetectorConstruction* dc):
    m_dc(dc)
  {
    // Directory: /ne697/geometry
    m_directory = new G4UIdirectory("/ne697/geometry/");
    m_directory->SetGuidance("Change parameters of the geometry.");

    // Set detector size: /ne697/geometry/det_size
    m_detSizeCmd = new G4UIcmdWith3VectorAndUnit("/ne697/geometry/det_size", this);
    m_detSizeCmd->SetGuidance("Set the detector size.");
    m_detSizeCmd->SetParameterName("x", "y", "z", true);
    m_detSizeCmd->SetDefaultValue(m_dc->get_det_size());
    m_detSizeCmd->AvailableForStates(G4State_PreInit);
  }

  GeometryMessenger::~GeometryMessenger() {
    delete m_directory;
    delete m_detSizeCmd;
  }

  void GeometryMessenger::SetNewValue(G4UIcommand* cmd, G4String val) {
    if (cmd == m_detSizeCmd) {
      G4ThreeVector parsed_val = m_detSizeCmd->GetNew3VectorValue(val);
      // This is fine too - just being clear above
      //auto parsed_val = m_detSizeCmd->GetNew3VectorValue(val);
      m_dc->set_det_size(parsed_val);
      G4cout << "Detector size set to " << G4BestUnit(parsed_val, "Length")
        << G4endl;
    }
    // Command didn't match
    return;
  }
}
