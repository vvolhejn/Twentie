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
    //std::cout<<s;
    uint num = write(fifo, s, strlen(s));
    if(num < strlen(s)) {
        std::cout << "Not all data written to pipe!" << std::endl;
    }
}

void setButton(const char* button, const bool press) {
    char buf[64];
    sprintf(buf, "%s %s\n", press?"PRESS":"RELEASE", button);
    sendInput(buf);
}

void setAnalogButton(const char* button, const float val) {
    char buf[64];
    sprintf(buf, "SET %s %.6f\n", button, val);
    if(COMMAS) { //LOCALE FIX - COMMAS INSTEAD OF POINTS
        buf[7] = ',';
    }
    sendInput(buf);
}

void setStick(const bool isLeft, const float x, const float y) {
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
    setButton("A", false);
    setButton("B", false);
    setButton("X", false);
    setButton("Y", false);
    setButton("Z", false);
    setAnalogButton("L", 0.0);
    setAnalogButton("R", 0.0);
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
