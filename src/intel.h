#ifndef INTEL_H
#define INTEL_H

#include "interface/subprocess.h"
#include "gamestate.h"

namespace ime {

class Core;

class Intel{
public:
  Intel();
  ~Intel();
  void start(Core* core, const char* name);
  void run();
private:
  void send();
  void receive();

  SubProcess subProcess_;
  GameState gameState_;
  Core* core_;
};

}

#endif
