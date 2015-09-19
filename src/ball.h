#ifndef BALL_H
#define BALL_H

#include "utils/vector2.h"

namespace ime {

struct Ball {
  bool visible;
  Vector2 position;
  Vector2 velocity;
};

}

#endif
