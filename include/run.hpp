#ifndef RUN_HPP
#define RUN_HPP
#include "G4Run.hh"

namespace ne697 {
  class Run: public G4Run {
    public:
      Run();
      ~Run();

      void RecordEvent(G4Event const* event) override final;
      void Merge(G4Run const* from_run) override final;
  };
}

#endif