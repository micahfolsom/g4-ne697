#include "detectorconstruction.hpp"
#include "globals.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "sensitivedetector.hpp"
#include "G4SDManager.hh"
#include "geometrymessenger.hpp"

namespace ne697 {
  DetectorConstruction::DetectorConstruction():
    G4VUserDetectorConstruction(),
    m_trackingVols(),
    m_detSize(10.*cm, 10.*cm, 10.*cm)
  {
    G4cout << "Creating DetectorConstruction" << G4endl;
    m_messenger = new GeometryMessenger(this);
    build_materials();
  }

  DetectorConstruction::~DetectorConstruction() {
    G4cout << "Deleting DetectorConstruction" << G4endl;
    delete m_messenger;
  }

  G4PVPlacement* DetectorConstruction::Construct() {
    auto world_solid = new G4Box("world_solid", 0.5*m, 0.5*m, 0.5*m);
    auto nist = G4NistManager::Instance();
    //auto world_mat = nist->FindOrBuildMaterial("G4_AIR");
    auto world_mat = nist->FindOrBuildMaterial("NE697_LIQUID_OXYGEN");
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

    auto det_solid = new G4Box("det_solid",
      m_detSize.getX() * 0.5,
      m_detSize.getY() * 0.5,
      m_detSize.getZ() * 0.5);
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

  void DetectorConstruction::build_materials() {
    auto o16 = new G4Isotope("NE697_O16", 8, 16, 15.99491463*g/mole);
    auto o17 = new G4Isotope("NE697_O17", 8, 17, 16.9991312*g/mole);
    auto o18 = new G4Isotope("NE697_O18", 8, 18, 17.9991603*g/mole);

    auto nat_o = new G4Element("NE697_natO", "O_ne697", 3);
    nat_o->AddIsotope(o16, 99.757*perCent);    
    nat_o->AddIsotope(o17, 0.038*perCent);    
    nat_o->AddIsotope(o18, 0.205*perCent);

    auto liq_o = new G4Material("NE697_LIQUID_OXYGEN", 1.141*g/cm3, 1);
    liq_o->AddElement(nat_o, 1);
    G4cout << "OUR MATERIAL: " << liq_o << G4endl;

    auto nist_man = G4NistManager::Instance();
    auto nist_o = nist_man->FindOrBuildElement("O");
    auto nist_liq_o = new G4Material("NIST_LIQUID_OXYGEN", 1.141*g/cm3, 1);
    nist_liq_o->AddElement(nist_o, 1);
    G4cout << "NIST MATERIAL: " << nist_liq_o << G4endl;
    return;
  }

  void DetectorConstruction::set_det_size(G4ThreeVector const& detsize) {
    m_detSize = detsize;
    return;
  }

  G4ThreeVector const& DetectorConstruction::get_det_size() const {
    return m_detSize;
  }
}
