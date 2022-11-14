#define _POSIX_C_SOURCE 200809L
#include <linux/stat.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

const char *get_stat_type(struct stat *stat) {
  switch (stat->st_mode & S_IFMT) {
    case S_IFSOCK:  return "socket";
    case S_IFLNK:   return "symlink";
    case S_IFREG:   return "regular file";
    case S_IFBLK:   return "block device";
    case S_IFDIR:   return "directory";
    case S_IFCHR:   return "character device";
    case S_IFIFO:   return "fifo";
    default:        return "unknown";
  }
}

int main(int argc, char **argv) {
  (void)argc; (void)argv;
  struct stat stat;
  if (fstat(STDOUT_FILENO, &stat) == -1) {
    fprintf(stderr, "Failed to stat stdout");
    return 1;
  }

  fprintf(stdout, "stdout is: %s\n", get_stat_type(&stat));
  return 0;
}