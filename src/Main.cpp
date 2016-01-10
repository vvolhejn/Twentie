#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <thread>
#include <pwd.h>
#include <sstream>

#include "Controller.h"
#include "Logic.h"
#include "Types.h"

using namespace std;

Logic logic;

void go() {
    //Mostly identical with spxtr's example usage:
    //https://github.com/dolphin-emu/dolphin/pull/3403
    struct passwd *pw = getpwuid(getuid());
    char *path = pw->pw_dir;
    strcat(path, "/.dolphin-emu/MemoryWatcher/MemoryWatcher");
    std::cout << path << std::endl;
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd < 0)
        printf("Can't create socket: %d\n", errno);
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    unlink(path);
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    if (bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
        printf("Can't bind: %d\n", errno);

    char buf[64];
    while (1) {
        struct sockaddr remaddr;
        socklen_t addr_len;
        recvfrom(fd, buf, sizeof(buf), 0, &remaddr, &addr_len);

        u32 pos, x, y;
        sscanf(buf, "%x%x", &pos, &x);
        if(pos == A_PLAYER_DATA_POINTERS[0] || pos == A_PLAYER_DATA_POINTERS[1]) {
            //We followed a pointer for a character
            sscanf(buf, "%x%x%x", &pos, &x, &y);
            logic.onMemoryChange(x, y, pos == A_PLAYER_DATA_POINTERS[1]);
        } else {
            logic.onMemoryChange(pos, x, -1);
        }
    }
}

int main() {
    controllerInit();
    go();
    return 0;
}
