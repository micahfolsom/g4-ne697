#include "detectorconstruction.hpp"
#include "globals.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

namespace ne697 {
  DetectorConstruction::DetectorConstruction():
    G4VUserDetectorConstruction()
  {
    G4cout << "Creating DetectorConstruction" << G4endl;
  }

  DetectorConstruction::~DetectorConstruction() {
    G4cout << "Deleting DetectorConstruction" << G4endl;
  }

  G4PVPlacement* DetectorConstruction::Construct() {
    auto world_solid = new G4Box("world_solid", 0.5*m, 0.5*m, 0.5*m);
    auto nist = G4NistManager::Instance();
    auto world_mat = nist->FindOrBuildMaterial("G4_AIR");
    auto world_log = new G4LogicalVolume(
        world_solid,
        world_mat,
        "world_log"
    );
    auto world_phys = new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 0),
        world_log,
        "world_phys",
        nullptr,
        false,
        0,
        true
    );
    return world_phys;
  }
}
