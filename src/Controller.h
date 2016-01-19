#pragma once
#include <string>
void controllerInit();
//Enumerating the buttons has no real benefit over inputting simply as string.
void setButton(const char* button, const bool press);
void setAnalogButton(const char* button, const float press);
void setStick(const bool isLeft, const float x, const float y);
void resetInputs();

