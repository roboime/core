#pragma once

#include <base/world.h>
#include <base/ball.h>
#include <base/robot.h>

namespace ime {

const int MAX_NUM_ROBOTS = 12;

struct GameState {
  float gameTime;
  //float timeRemaining;

  World world;
  Ball ball;
  Robot blueTeam[MAX_NUM_ROBOTS];
  Robot yellowTeam[MAX_NUM_ROBOTS];
};

}
