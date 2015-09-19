#pragma once

#include <cinttypes>

#include "world.h"
#include "ball.h"
#include "robot.h"

namespace ime {

const int MAX_NUM_ROBOTS = 12;

struct GameState {
  uint64_t gameTime; // microseconds
  int ourScore, theirScore;
  int ourGoalie, theirGoalie;

  RefereeState refState;
  uint16_t timeLeft; // time left on ref state

  World world;
  Ball ball;
  Robot ourRobots[MAX_NUM_ROBOTS];
  Robot theirRobots[MAX_NUM_ROBOTS];
};

}
