#include <dirent.h>
#include <errno.h>
#include <stdio.h>

//DIR *opendir(const char name);
//struct dirent *readdir(DIR *dirp);
//int closedir(DIR *dirp);

int main(int argc, char **argv) {
  DIR *streamp;
  struct dirent *dep;
  streamp = opendir(argv[1]);
  errno = 0;
  while (dep = readdir(streamp))
    printf("Found file: %s\n", dep->d_name);
  if (errno) 
    perror("readdir error");
  closedir(streamp);
  return 0;
}
