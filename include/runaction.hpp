#ifndef RUN_ACTION_HPP
#define RUN_ACTION_HPP

#include "G4UserRunAction.hh"
#include "hit.hpp"

namespace ne697 {
  // Forward declaration, to address circular dependency with RunMessenger
  // You still need to #include "runmessenger.hpp" in runaction.cpp
  class RunMessenger;

  class RunAction: public G4UserRunAction {
    public:
      RunAction();
      ~RunAction();

      // Geant4 overrides
      G4Run* GenerateRun() override final;
      void BeginOfRunAction(G4Run const*) override final;
      void EndOfRunAction(G4Run const* run) override final;

      // Code-facing part of the UI - storing and modifying the variables used
      // when doing Geant4 things (building objects, defining materials,
      bool save_data() const;
      void save_data(bool save);
      G4String const& get_path() const;
      void set_path(G4String const& path);

    private:
      void write_hits(std::vector<Hit> hits);

      RunMessenger* m_messenger;

      // Variables we will be modifying from the UI, so we want them to be
      // attached to RunAction. Then, when write_hits() is called, m_path holds
      // whatever value the user set
      bool m_fSaveData;
      G4String m_path;
  };
}

#endif
