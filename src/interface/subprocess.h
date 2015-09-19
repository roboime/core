#ifndef INTERFACE_SUBPROCESS_H
#define INTERFACE_SUBPROCESS_H

#include <sys/types.h>

namespace ime {

class SubProcess {
public:
  SubProcess();
  ~SubProcess();

  bool start(const char* name);

  int read(char* buffer, unsigned int size);
  int readErr(char* buffer, unsigned int size);
  int write(const char* buffer);
private:
  pid_t pid_;

  int fdin_[2];
  int fdout_[2];
  int fderr_[2];
};

}

#endif
