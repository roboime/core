#pragma once

#include <string>
#include <vector>

namespace ime {

struct TeamInfo {
  std::string  name;
  unsigned int score;
  unsigned int redCards;
  unsigned int yellowCards;
  unsigned int timeouts;
  unsigned int timeoutTime;
  unsigned int goalie;
  std::vector<unsigned int> yellowCardTimes;
};

}
