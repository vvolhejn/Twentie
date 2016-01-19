#pragma once
#include <vector>
#include <tuple>

#include "Types.h"
#include "State.h"
#include "ai/AI.h"

class Logic {
public:
    Logic();
    virtual ~Logic();
    void onMemoryChange(u32 pos, u32 value, s16 player = -1);
private:
    State s;
    AI *ai;
    void selectCharacter();
};
