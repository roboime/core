#pragma once

#include <mutex>

#include <interface/subprocess.h>
#include <control/control.h>
#include <base/gamestate.h>
#include <base/team.h>
#include <base/refereestate.h>
#include <base/skill.h>

namespace ime {

class Core {
public:
  Core();
  ~Core();

  void changeTeam(const Team team);

  void addIntel(const char* name);
  void start();

private:
  /*
   * Game
   */
  Team ourTeam_;
  GameState gameState_;

  // TODO(naum): Create skills for each team, in case we want to test both
  Skill skills_[MAX_NUM_ROBOTS];

  /*
   * Intel
   */
  // TODO(naum): Create intel for each team
  SubProcess intel_;

  /*
   * Control
   */
  Control control_;

  // Mutexes
  std::mutex gameStateMutex_;
  std::mutex skillsMutex_;

  //friend class Control;
  friend class Intel;
};

}
