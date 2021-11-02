#include <fcntl.h>
#include <stdio.h>

//ssize_t read(int fd, void *buf, size_t n);
//ssize.t write(int fd, const void *buf, size_t n);

int main() {
  char c;
  while(read(STDIN_FILENO, &c, 1) != 0)
    write(STDOUT_FILENO, &c, 1);
  return 0;
}
