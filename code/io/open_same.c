#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
  int fd1, fd2;
  struct stat s1, s2;
  char c;
  fd1 = open("foo.txt", O_RDONLY, 0);
  fd2 = open("foo.txt", O_RDONLY, 0);
  read(fd1, &c, 1);
  read(fd2, &c, 1);
  printf("c=%c\n", c);
  return 0;
}
