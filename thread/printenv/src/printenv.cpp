#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {

  char **ep;
  for (ep = environ; *ep != NULL; ep++) {
    cout << *ep << endl;
  }

  return 0;
}