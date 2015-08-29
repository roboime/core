#pragma once

namespace ime {

class Core;

class Control {
public:
  Control();
  ~Control();
private:
  void transmit();

  Core* core;
};

}
