#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <string>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <sstream>

int fifo;
const bool COMMAS = false;

void sendInput(const char* s) {
    uint num = write(fifo, s, strlen(s));
    if(num < strlen(s)) {
        std::cout << "Not all data written to pipe!" << std::endl;
    }
}

void setButton(std::string button, bool press) {
    sendInput(((press ? "PRESS " : "RELEASE ") + button + "\n").c_str());
}

void setAnalogButton(std::string button, float val) {
    char buf[64];
    sprintf(buf, "SET %s %.6f\n", button.c_str(), val);
    if(COMMAS) { //LOCALE FIX - COMMAS INSTEAD OF POINTS
        buf[7] = ',';
    }
    sendInput(buf);
}

void setStick(bool isLeft, float x, float y) {
    char buf[64];
    sprintf(buf, "SET %s %.6f %.6f\n", isLeft ? "MAIN" : "C", x, y);
    if(COMMAS) {//LOCALE FIX - COMMAS INSTEAD OF POINTS
        if(isLeft) buf[10] = ',', buf[19] = ',';
        else buf[7] = ',', buf[16] = ',';
    }
    sendInput(buf);
}

void resetInputs() {
    setStick(true, 0.5, 0.5);
    setStick(false, 0.5, 0.5);
}

void controllerInit() {
    struct passwd *pw = getpwuid(getuid());
    std::string pipe_path = pw->pw_dir;
    pipe_path += "/.dolphin-emu/Pipes/twentie";
    std::cout << "Waiting for Dolphin: " << pipe_path << std::endl;
    if ((fifo = open(pipe_path.c_str(), O_WRONLY)) < 0) {
        printf("%s\n", strerror(errno));
        return;
    }
    std::cout << "Pipe started." << std::endl;
    resetInputs();
}

