#pragma once

#include <mutex>

#include <base/gamestate.h>
#include <base/skill.h>

namespace ime {

class Core {
public:
private:
  GameState gameState_;
  std::mutex gameStateMutex_;

  // TODO(naum): Create skills for each team, in case we want to test both
  Skill skills[MAX_NUM_ROBOTS];
  std::mutex skillsMutex_;

  friend class Control;
};

}
