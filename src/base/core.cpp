#include <base/core.h>

namespace ime {

Core::
Core() {
}

Core::
~Core() {
}

void Core::
changeTeam(const Team team) {
  ourTeam_ = team;
}

void Core::
addIntel(const char* name) {
  // TODO(naum): Don't start, just store (libuv to resolve)
  intel_.start(name);
}

void Core::
start() {
  // TODO(naum): Start vision
  // TODO(naum): Start intel
  // TODO(naum): Start control
}

}
