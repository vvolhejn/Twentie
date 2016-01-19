#pragma once
#include "action/Action.h"
#include "State.h"

//There is still much to be done here; DI is a complex topic.
class DI: public Action {
public:
    DI();
    ~DI();
    void execute(const State &s);
    bool hasEnded(const State& s);
private:
    //there are certain angles of the control stick which SDI inputs
    //have to cross to be considered different. See Kadano's video on advanced DI
    const float SDI_DELTA = 0.075; //from 0.745 to 0.75 (left exclusive)
    bool okFrame(const State& s);
    bool lastOk = true;
};
