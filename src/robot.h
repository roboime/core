#pragma once

#include <utils/vector2.h>
#include <team.h>

namespace ime {

struct Robot {
  bool visible;

  //Team team;

  Vector2 position;
  Vector2 velocity;

  float orientation;
  float angularVelocity;
};

}
