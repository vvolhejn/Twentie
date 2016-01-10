#pragma once
#include "Types.h"
#include "State.h"

//In the future, this should be an abstract class, but for now one AI will do
class AI {
public:
    AI();
    void decide(const State &s);
private:
    bool teching = false;
};
