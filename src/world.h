#pragma once

namespace ime {

struct World {
  // TODO(naum): Verify every name
  float fieldWidth;
  float fieldHeight;
  float goalWidth;
  float centerCircleRadius;
  float defenseRadius;
  float defenseStretch;
  float freeKickFromDefenseDist;
  float penaltySpotFromFieldLineDist;
  float penaltyLineFromSpotDist;
};

}
