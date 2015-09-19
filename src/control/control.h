#ifndef CONTROL_CONTROL_H
#define CONTROL_CONTROL_H

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

#endif
