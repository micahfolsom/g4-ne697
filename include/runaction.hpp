#ifndef RUN_ACTION_HPP
#define RUN_ACTION_HPP

#include "G4UserRunAction.hh"
#include "hit.hpp"

namespace ne697 {
  class RunAction: public G4UserRunAction {
    public:
      RunAction();
      ~RunAction();

      G4Run* GenerateRun() override final;
      void BeginOfRunAction(G4Run const*) override final;
      void EndOfRunAction(G4Run const* run) override final;

    private:
      void write_hits(std::vector<Hit> hits, std::string const& file_path);
  };
}

#endif