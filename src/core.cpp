#include "core.h"
#include "intel.h"

namespace ime {

Core::
Core() {
}

Core::
~Core() {
}

void Core::
changeTeam(const Team team) {
  ourTeam_ = team;
}

void Core::
addIntel(const char* name) {
  // TODO(naum): Don't start, just store (libuv to resolve)
  intel_.start(this, name);
}

void Core::
start() {
  // TODO(naum): Start vision
  // TODO(naum): Start control

  intelThread_ = std::thread {&Intel::run, std::ref(intel_)};

  intelThread_.join();
}

GameState Core::
getGameState() const {
  std::lock_guard<std::mutex> lock {gameStateMutex_};
  return gameState_;
}

void Core::
updateGameState(GameState gameState) {
  {
    std::lock_guard<std::mutex> lock {gameStateMutex_};
    gameState_ = gameState;
  }
  gameStateUpdateCv_.notify_all();
}

void Core::
waitGameStateUpdate() {
  std::unique_lock<std::mutex> lock {gameStateUpdateMutex_};
  gameStateUpdateCv_.wait(lock);
}

}