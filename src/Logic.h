#pragma once
#include "Types.h"
#include "State.h"
#include <vector>
#include <tuple>

class Logic {
public:
    Logic();
    void onMemoryChange(u32 pos, u32 value, s16 player = -1);

private:
    State s;
    std::vector<std::tuple<u32, u32, s16>> pending;
    void changeState(u32 pos, u32 value, s16 player);
    void selectCharacter();
};
