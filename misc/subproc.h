// <ADD HEADER HERE>
#ifndef SUBPROC_H
#define SUBPROC_H
#ifdef __cplusplus
extern "C" {
#endif

// will return the subprocess PID and set the proper FDs on pipes (in, out, err)
int subproc_open(int pipes[3], char *const argv[]);

// close pipes, send SIGQUIT to subprocess and wait for it to exit
// returns the process exit status
int subproc_close(const int pid, const int pipes[3]);

// helper read and write functions with basic error handling, these functions are blocking
// returns -1 for error
int subproc_read(int fd, char *into_buffer, int buffer_size);
int subproc_write(int fd, const char *from_buffer, int buffer_size);
#define subproc_lread(fd, buf) subproc_read(fd, (char *)(buf), sizeof(buf) / sizeof(*buf))
#define subproc_lwrite(fd, buf) subproc_write(fd, (const char *)(buf), sizeof(buf) / sizeof(*buf) - 1)

#ifdef __cplusplus
}
#endif
#endif // SUBPROC_H
