#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
  ssize_t size;
  char buf[BUF_SIZE];
  int fd, openFlags;
  mode_t filePerms;
  
  if ((argc < 2 && argc > 3) || (argc == 3 && strcmp(argv[1], "-a") != 0) || strcmp(argv[1], "--help") == 0) {
    cout
    << "Usage: tee [OPTION]... [FILE]\n"
    << "Copy standard input to FILE, and also standard output.\n\n"
    << "\t-a,\t--append\t\tappend to the given FILE, do not owerwrite\n";
    return -1;
  }

  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // rw-rw-rw-

  if (argc == 3) {
    openFlags = O_CREAT | O_WRONLY | O_APPEND;
    fd = open(argv[2], openFlags, filePerms);
  } else {
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    fd = open(argv[1], openFlags, filePerms);

  }

  if (fd == -1) {
    cerr << "Failed to open file " << argv[1] << endl;
    return -1;
  }

  while ((size = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    if (write(STDOUT_FILENO, buf, size) != size) {
      cerr << "Couldn't write whole buffer to stdout" << endl;
      return -1;
    }
    if (write(fd, buf, size) != size) {
      cerr << "Couldn't write whole buffer to file" << endl;
      return -1;
    }
  }

  if (size == -1) {
    cerr << "Failed to read from stdin" << endl;
    return -1;
  }

  return 0;
}