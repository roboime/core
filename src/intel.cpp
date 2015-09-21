#include <cstdio>

#include "intel.h"
#include "core.h"

namespace ime {

Intel::
Intel() {
  hasStarted_ = false;
}

Intel::
~Intel()
{}

bool Intel::
start(Core* core, const char* name) {
  core_ = core;
  hasStarted_ = subProcess_.start(name);
  return hasStarted_;
}

bool Intel::
run() {
  if (!hasStarted_) {
    // TODO(naum): Log running without started intel
    ::printf("Trying to run intel while it hasn't started!\n");
    return false;
  }

  while (1) {
    core_->waitGameStateUpdate();
    gameState_ = core_->getGameState();
    send();
    receive();
  }

  return true;
}

void Intel::
send() {
  int ourRobots = 0,
      theirRobots = 0;
  for (int i = 0; i < MAX_NUM_ROBOTS; i++) {
    if (gameState_.ourRobots[i].visible) {
      ourRobots++;
    }

    if (gameState_.theirRobots[i].visible) {
      theirRobots++;
    }
  }

  char buffer[1024];
  sprintf(buffer, "%" PRIu64 "\n%d %d\n%d %d\n%f %f %f %f\n%d %d\n%d\n%d\n",
          gameState_.gameTime,
          gameState_.ourScore, gameState_.theirScore,
          static_cast<int>(gameState_.refState), gameState_.timeLeft,
          gameState_.ball.position.x, gameState_.ball.position.y,
          gameState_.ball.velocity.x, gameState_.ball.velocity.y,
          gameState_.ourGoalie, gameState_.theirGoalie,
          ourRobots, theirRobots);

  subProcess_.write(buffer);

  for (int i = 0; i < MAX_NUM_ROBOTS; i++) {
    if (gameState_.ourRobots[i].visible) {
      sprintf(buffer, "%d %f %f %f %f %f %f\n",
              i,
              gameState_.ourRobots[i].position.x, gameState_.ourRobots[i].position.y,
              gameState_.ourRobots[i].orientation,
              gameState_.ourRobots[i].velocity.x, gameState_.ourRobots[i].velocity.y,
              gameState_.ourRobots[i].angularVelocity);
    }

    subProcess_.write(buffer);
  }

  for (int i = 0; i < MAX_NUM_ROBOTS; i++) {
    if (gameState_.theirRobots[i].visible) {
      sprintf(buffer, "%d %f %f %f %f %f %f\n",
              i,
              gameState_.theirRobots[i].position.x, gameState_.theirRobots[i].position.y,
              gameState_.theirRobots[i].orientation,
              gameState_.theirRobots[i].velocity.x, gameState_.theirRobots[i].velocity.y,
              gameState_.theirRobots[i].angularVelocity);
    }

    subProcess_.write(buffer);
  }
}

void Intel::
receive() {
}

}
