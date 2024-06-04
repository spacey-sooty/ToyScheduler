// Copyright (c) 2024 Jade Turner
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include "Behaviour.h"

class Resource {
 public:
  virtual void Periodic() = 0;
  virtual void SimulationPeriodic() = 0;

  void SetDefaultBehaviour(Behaviour* behaviour) { _default_behaviour = behaviour; }
  Behaviour* GetDefaultBehaviour() { return _default_behaviour; }
  void SetActiveBehaviour(Behaviour* behaviour) { _active_behaviour = behaviour; }
  Behaviour* GetActiveBehaviour() { return _active_behaviour; }

 private:
  Behaviour* _default_behaviour = nullptr;
  Behaviour* _active_behaviour = nullptr;
};
