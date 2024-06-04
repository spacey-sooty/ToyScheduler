// Copyright (c) 2024 Jade Turner
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include <frc/RobotBase.h>
#include <wpi/SmallVector.h>

#include <deque>

#include "Resource.h"

class Scheduler {
 public:
  void Register(Resource* requirement) { _requirements.emplace_back(requirement); }

  /**
   * Should be called once every tick of your robot.
   */
  void Run() {
    for (auto resource : _requirements) {
      resource->Periodic();

      if (!frc::RobotBase::IsReal()) {
        resource->SimulationPeriodic();
      }

      if (resource->GetActiveBehaviour() == nullptr) {
        Schedule(resource->GetDefaultBehaviour());
      } else {
        if (resource->GetActiveBehaviour()->IsFinished()) {
          resource->SetActiveBehaviour(nullptr);
        }
      }
    }

    for (auto behaviour : _active_behaviours) {
      if (behaviour->IsFinished()) {
        behaviour->End(false);
      } else {
        behaviour->Execute();
      }
    }
  }

  /**
   * Schedules a behaviour. Note this interrupts any running behaviours on requirements.
   */
  void Schedule(Behaviour* behaviour) {
    for (auto resource : behaviour->GetRequirements()) {
      if (resource->GetActiveBehaviour() != nullptr) {
        resource->GetActiveBehaviour()->End(true);
      }

      resource->SetActiveBehaviour(behaviour);
    }

    _active_behaviours.emplace_back(behaviour);
    behaviour->Initialize();
  }

 private:
  wpi::SmallVector<Resource*, 8> _requirements;
  std::deque<Behaviour*> _active_behaviours;
};
