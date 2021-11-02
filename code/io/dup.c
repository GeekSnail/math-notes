#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

//int dup2(int oldfd, int newfd);

int main() {
  int fd1, fd2;
  struct stat s1, s2;
  char c1, c2;
  fd1 = open("foo.txt", O_RDONLY, 0);
  fd2 = open("foo.txt", O_RDONLY, 0);
  fstat(fd1, &s1);
  fstat(fd2, &s2);
  printf("fd1=%d, s1.st_nlink=%d, fd2=%d, s2.st_nlink=%d\n", fd1, s1.st_nlink, fd2, s2.st_nlink);
  read(fd2, &c2, 1);
  printf("read, c2 = %c\n", c2);
  dup2(fd2, fd1);
  read(fd1, &c1, 1);
  read(fd2, &c2, 1);
  printf("dup2(fd2, fd1);\nread, c1 = %c, c2 = %c\n", c1, c2);
  return 0;
}
