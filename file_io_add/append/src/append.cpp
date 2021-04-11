#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
  int fd, openFlags;
  mode_t filePerms;
  off_t offset;
  ssize_t size;

  if ((argc < 3) || strcmp(argv[1], "--help") == 0) {
    cout
        << "Usage: append [FILE] [OFFSET] [PHRASE]\n"
        << "Append PHRASE to FILE at OFFSET\n";
    return -1;
  }
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // rw-rw-rw-
  openFlags = O_CREAT | O_WRONLY | O_APPEND;
  fd = open(argv[1], openFlags, filePerms);

  cout << lseek(fd, 0, SEEK_SET) << endl;

  if (fd == -1) {
    cerr << "Failed to open file " << argv[1] << endl;
    return -1;
  }

  size = strlen(argv[3]);
  if (write(fd, argv[3], size) != size) {
    cerr << "Couldn't write whole buffer to file" << endl;
    return -1;
  }
  cout << lseek(fd, 0, SEEK_CUR) << endl;

  return 0;
}