#ifndef SKILL_H
#define SKILL_H

#include "utils/vector2.h"

namespace ime {

struct Skill {
  enum class Type {
    None,
    GoTo,
    GoToBall,
    Kick,
    Wait
  };

  Type type;
  union info {
    struct target {
      Vector2 position;
      float area;
    };

    unsigned char robotId;

    struct kick {
      bool forceKick;
      bool forceChip;
      unsigned char kickForce;
    };
  };
};

}

#endif
