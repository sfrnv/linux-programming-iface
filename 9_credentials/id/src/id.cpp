#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main() {
    uid_t euid;

    cout    << "Real user ID: " << getuid() << "\n"
            << "Real group ID: " << getgid() << "\n"
            << "Effective user ID: " << geteuid() << "\n"
            << "Effective group ID: " << getegid() << "\n"
            << endl;
    euid = geteuid();

    if (seteuid(getuid()) == -1)
        return -1;
    
    cout    << "Dropping privileges..." << "\n\n"
            << "Real user ID: " << getuid() << "\n"
            << "Real group ID: " << getgid() << "\n"
            << "Effective user ID: " << geteuid() << "\n"
            << "Effective group ID: " << getegid() << "\n"
            << endl;

    if (seteuid(euid) == -1)
        return -1;

    cout    << "Regaining privileges..." << "\n\n"
            << "Real user ID: " << getuid() << "\n"
            << "Real group ID: " << getgid() << "\n"
            << "Effective user ID: " << geteuid() << "\n"
            << "Effective group ID: " << getegid() << "\n"
            << endl;
  return 0;
}