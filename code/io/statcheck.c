//#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

//int stat(const char *filename, struct stat *buf);
//int fstat(int fd, struct stat *buf);

int main(int argc, char **argv) {
  struct stat st;
  char *type, *readok;
  stat(argv[1], &st);
  if (S_ISREG(st.st_mode))
    type = "regular";
  else if (S_ISDIR(st.st_mode))
    type = "directory";
  else
    type = "other";
  if (st.st_mode & S_IRUSR)
    readok = "yes";
  else 
    readok = "no";
  printf("type: %s, read: %s\n", type, readok);
  return 0;
}
