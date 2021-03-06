#include <unistd.h>
#include <string.h>

#include <interface/subprocess.h>

#define READ  0
#define WRITE 1

namespace ime {

SubProcess::
SubProcess() {}

SubProcess::
~SubProcess() {}

bool SubProcess::
start(const char* name) {
  // Open input pipe
  if (::pipe(fdin_) == -1) {
    // TODO(naum): Log error
    return false;
  }

  // Open output pipe
  if (::pipe(fdout_) == -1) {
    // TODO(naum): Log error
    return false;
  }

  // Open error pipe
  if (::pipe(fderr_) == -1) {
    // TODO(naum): Log error
    return false;
  }

  // Create the child process
  pid_ = ::fork();

  if (pid_ == 0) // Child process
  {
    // Redirect input to stdin
    if (::dup2(fdin_[READ], STDIN_FILENO) == -1) {
      // TODO(naum): Log error
      return false;
    }

    // Redirect output to stdin
    if (::dup2(fdout_[WRITE], STDOUT_FILENO) == -1) {
      // TODO(naum): Log error
      return false;
    }

    // Redirect error to stdin
    if (::dup2(fderr_[WRITE], STDERR_FILENO) == -1) {
      // TODO(naum): Log error
      return false;
    }

    // Close all ends (only used in parent process)
    ::close(fdin_ [READ]);
    ::close(fdin_ [WRITE]);
    ::close(fdout_[READ]);
    ::close(fdout_[WRITE]);
    ::close(fderr_[READ]);
    ::close(fderr_[WRITE]);

    ::execl(name, "", (char*)NULL);
  } else if (pid_ > 0) { // Parent process
    // Close unused ends
    ::close(fdin_ [READ]);
    ::close(fdout_[WRITE]);
    ::close(fderr_[WRITE]);
  } else { // Error
    // Close all ends
    ::close(fdin_ [READ]);
    ::close(fdin_ [WRITE]);
    ::close(fdout_[READ]);
    ::close(fdout_[WRITE]);
    ::close(fderr_[READ]);
    ::close(fderr_[WRITE]);

    // TODO(naum): Log error
  }

  return true;
}

int SubProcess::
read(char* buffer, unsigned int size) {
  ::memset(buffer, 0, size);
  return ::read(fdout_[READ], buffer, size);
}

int SubProcess::
readErr(char* buffer, unsigned int size) {
  ::memset(buffer, 0, size);
  return ::read(fderr_[READ], buffer, size);
}

int SubProcess::
write(const char* buffer) {
  // TODO(naum): Log warning if last character is not '\n'
  return ::write(fdin_[WRITE], buffer, ::strlen(buffer));
}

}
