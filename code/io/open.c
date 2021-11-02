#include <fcntl.h>
#include <stdio.h>

//int open(char *filename, int flags, modest mode);
//int close(int fd);

int main() {
  int fd = open("hello.c", O_RDONLY, 0);
  printf("%d", fd);
  close(fd);
  return 0;
}
