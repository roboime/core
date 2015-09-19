#pragma once

#include <interface/subprocess.h>
#include <base/gamestate.h>
#include <base/core.h>

namespace ime{

class Intel{
public:
  Intel(Core& core);
  ~Intel();
  void start(const char* name);
  void run();
private:
  void send();
  void receive();

  SubProcess subProcess_;
  GameState gameState_;
  Core& core_;
};

}
