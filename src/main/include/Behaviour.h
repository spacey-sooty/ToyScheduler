// Copyright (c) 2024 Jade Turner
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include <wpi/SmallVector.h>

class Resource;

class Behaviour {
 public:
  virtual void Initialize() = 0;
  virtual void Execute() = 0;
  virtual void End(bool interrupted) = 0;
  virtual bool IsFinished() { return false; }

  wpi::SmallVector<Resource*, 4> GetRequirements() { return _requirements; }

  void SetDefaultBehaviour(Behaviour* behaviour) { _default_behaviour = behaviour; }
  Behaviour* GetDefaultBehaviour() { return _default_behaviour; }
  void SetActiveBehaviour(Behaviour* behaviour) { _active_behaviour = behaviour; }
  Behaviour* GetActiveBehaviour() { return _active_behaviour; }

 private:
  wpi::SmallVector<Resource*, 4> _requirements;
  Behaviour* _default_behaviour = nullptr;
  Behaviour* _active_behaviour = nullptr;
};
