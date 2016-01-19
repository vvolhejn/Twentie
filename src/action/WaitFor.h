#pragma once
#include <functional>
#include "action/Action.h"
#include "State.h"

//A class used for all simple actions that do not really deserve a separate class, such as doublejumping or drifting
class WaitFor: public Action {
public:
    WaitFor(std::function<bool(const State&)> _cond);
    WaitFor(u32 endFrame); //end at this frame or later
    ~WaitFor();
    void execute(const State &s);
    bool hasEnded(const State& s);
private:
    u32 endFrame = 0;
    std::function<bool(const State&)> condition = [](const State& s){return true;};
};
