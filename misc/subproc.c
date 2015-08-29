// <ADD HEADER HERE>
#include "subproc.h"
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

// this demo is an example of how to use this module
#ifdef SUBPROC_DEMO
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
  char *const child_argv[] = {"./subproc_demo_echo.sh", 0};
  int child_io[3];
  char buffer[256];
  int child = subproc_open(child_io, child_argv);
  int din = child_io[0];
  int dout = child_io[1];
  int derr = child_io[2];

#define TRY(E) if ((E) < 0) { perror("error"); return -1; }

  TRY(subproc_lwrite(din, "foo\n"));
  TRY(subproc_lread(dout, buffer));
  printf("got: %s", buffer);

  TRY(subproc_lwrite(din, "bar\n"));
  TRY(subproc_lread(dout, buffer));
  printf("got: %s", buffer);

  TRY(subproc_lwrite(din, "enough\n"));
  TRY(subproc_lread(derr, buffer));
  printf("got: %s", buffer);

  printf("%i\n", subproc_close(child, child_io));

  return 0;
}
#endif

int subproc_open(int pipes[3], char *const argv[]) {
  int p[3][2], i;
  int pid;

  for (i = 0; i < 3; i++)
    if (pipe(p[i]) < 0) goto fail;

  // vfork is an optimization over fork, it makes no virtual page copy whatsoever,
  // because of that it only makes sense to do some pipe setup and exec
  // XXX: this is a critical part which should not do anything else other than this,
  if (!(pid = vfork())) {
    // DO NOT MODIFY ANY VARIABLES OUTSIDE THIS SCOPE, doing so is __undefined behaviour__
    // XXX: maybe some untangling is needed if, say, p[0][0] == 1 and p[1][1] == 0 for example
    if (p[0][0] != 0) {
      dup2(p[0][0], 0);
      close(p[0][0]);
    }
    if (p[1][1] != 1) {
      dup2(p[1][1], 1);
      close(p[1][1]);
    }
    if (p[2][1] != 2) {
      dup2(p[2][1], 2);
      close(p[2][1]);
    }
    close(p[0][1]);
    close(p[1][0]);
    close(p[2][0]);
    execv(argv[0], argv);
    _exit(127);
  }

  if (pid < 0) goto fail;

  //for (int i = 0; i < 3; ++i)
  //  printf("p[%i] = {%i, %i}\n", i, p[i][0], p[i][1]);

  pipes[0] = p[0][1];
  pipes[1] = p[1][0];
  pipes[2] = p[2][0];
  close(p[0][0]);
  close(p[1][1]);
  close(p[2][1]);
  return pid;

fail:
  for (i--; i >= 0; i--) {
    close(p[i][0]);
    close(p[i][1]);
  }
  return -1;
}

int subproc_close(const int pid, const int pipes[3]) {
  int status;
  // ignore errors on these close
  close(pipes[0]);
  close(pipes[1]);
  close(pipes[2]);
  // don't ignore errors for the kill call
  if (kill(pid, SIGTERM) < 0) {
    return -1;
  }
  if (waitpid(pid, &status, 0) < 0)
    return -1;
  return status;
}

int subproc_read(int fd, char *into_buffer, int buffer_size) {
  int s;
  int maxtries = 5;
again:
  s = read(fd, into_buffer, buffer_size - 1);
  if (s < 0) switch (errno) {
    case EAGAIN:
      printf("again\n");
      goto again;
    default: return -1;
  }
  into_buffer[s] = 0;
  return s;
}

int subproc_write(int fd, const char *from_buffer, int buffer_size) {
  int s;
  s = write(fd, from_buffer, buffer_size);
  return s;
}
