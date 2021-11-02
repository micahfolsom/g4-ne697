#ifndef EVENT_ACTION_HPP
#define EVENT_ACTION_HPP
#include "G4UserEventAction.hh"

namespace ne697 {
  class EventAction: public G4UserEventAction {
    public:
      EventAction();
      ~EventAction();

      void EndOfEventAction(G4Event const* event) override final;
  };
}

#endif