#pragma once
#include <string>
void controllerInit();
//Enumerating the buttons has no real benefit over inputting simply as string.
void setButton(std::string button, bool press);
void setAnalogButton(std::string button, float press);
void setStick(bool isLeft, float x, float y);
void resetInputs();

