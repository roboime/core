#ifndef CORE_H
#define CORE_H

#include <thread>
#include <mutex>
#include <condition_variable>

#include "control/control.h"
#include "intel.h"
#include "team.h"
#include "gamestate.h"
#include "skill.h"

namespace ime {

class Core {
public:
  Core();
  ~Core();

  void changeTeam(const Team team);

  void addIntel(const char* name);
  void start();

  GameState getGameState() const;
  void updateGameState(GameState gameState);
  void waitGameStateUpdate();

private:
  /*
   * Game
   */
  Team ourTeam_;
  GameState gameState_;

  Skill skills_[MAX_NUM_ROBOTS];

  /*
   * Intel
   */
  Intel intel_;
  std::thread intelThread_;

  /*
   * Control
   */
  /*
  Control control_;
  std::thread controlThread_;
  */

  // CVs
  std::condition_variable gameStateUpdateCv_;

  // Mutexes
  std::mutex gameStateUpdateMutex_;
  mutable std::mutex gameStateMutex_;
  mutable std::mutex skillsMutex_;
};

}

#endif
