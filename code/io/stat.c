#include <sys/stat.h>
#include <stdio.h>

//int stat(const char *filename, struct stat *buf);
//int fstat(int fd, struct stat *buf);

int main(int argc, char **argv) {
  struct stat st;
  fstat(0, &st);
  printf("st_nlink\t%d\nst_size\t%d\n",st.st_nlink,st.st_size);
  return 0;
}
