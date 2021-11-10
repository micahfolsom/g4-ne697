#include "detectorconstruction.hpp"
#include "globals.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "sensitivedetector.hpp"
#include "G4SDManager.hh"

namespace ne697 {
  DetectorConstruction::DetectorConstruction():
    G4VUserDetectorConstruction(),
    m_trackingVols()
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
    // Commented since we don't want to record Hits in the world's air volume
    //m_trackingVols.push_back(world_log);
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

    auto det_solid = new G4Box("det_solid", 5*cm, 5*cm, 5*cm);
    auto det_mat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    auto det_log = new G4LogicalVolume(det_solid, det_mat, "det_log");
    // Tracking Hits in this volume
    m_trackingVols.push_back(det_log);
    new G4PVPlacement(
      nullptr,
      G4ThreeVector(0, 0, 20*cm),
      det_log,
      "det_phys",
      world_log,
      false,
      0,
      true
    );
    return world_phys;
  }

  void DetectorConstruction::ConstructSDandField() {
    // We will ask for "world_sd_hits" later in Run::RecordEvent()
    auto sd = new SensitiveDetector("world_sd");
    G4SDManager::GetSDMpointer()->AddNewDetector(sd);
    // Connect the sensitive detector to all of the logical volumes on the list
    for (auto& log : m_trackingVols) {
      SetSensitiveDetector(log, sd);
    }
    return;
  }
}
