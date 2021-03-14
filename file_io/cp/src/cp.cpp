#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

#define BUF_SIZE 8192

ssize_t rude_copy(int src, int dst, char* buf) {
  ssize_t numRead{0};
  while ((numRead = read(src, buf, BUF_SIZE)) > 0) {
    if (write(dst, buf, numRead) == -1) return -1;
  }
  return 0;
}

ssize_t copy(int src, off_t src_offset, int dst, off_t dst_offset, ssize_t size, char* buf) {
  ssize_t tmp{0}, remain{size};
  if (lseek(src, src_offset, SEEK_SET) == -1) return -1;
  if (lseek(dst, dst_offset, SEEK_SET) == -1) return -1;
  while ((tmp = read(src, buf, BUF_SIZE)) > 0) {
    if (write(dst, buf, tmp) != tmp) {
      cerr << "Couldn't write whole buffer to file" << endl;
      return -1;
    }
    if (tmp == remain) return size;
    remain -= tmp;
  }
  return size;
}

int main(int argc, char* argv[]) {
  int inputFd, outputFd, openFlags;
  mode_t filePerms;
  ssize_t numRead;
  off_t start{0}, end{0}, eof{0};
  char buf[BUF_SIZE];

  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    cout
    << "Usage: cp SOURCE DEST\n"
    << "Copy SOURCE to DEST\n";
    return -1;
  }

  inputFd = open(argv[1], O_RDONLY);
  if (inputFd == -1) {
    cerr << "Failed to open file " << argv[1] << endl;
    return -1;
  }

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // rw-rw-rw-
  outputFd = open(argv[2], openFlags, filePerms);
  if (outputFd == -1) {
    cerr << "Failed to open file " << argv[2] << endl;
    return -1;
  }
  // rude_copy(inputFd, outputFd, buf);
  eof = lseek(inputFd, 0, SEEK_END);
  start = lseek(inputFd, 0, SEEK_DATA);
  while (start != eof && end != eof) {
    end = lseek(inputFd, start, SEEK_HOLE);
    if (copy(inputFd, start, outputFd, start, end - start, buf) == -1) return -1;
    start = lseek(inputFd, end, SEEK_DATA);
  }

  return 0;
}