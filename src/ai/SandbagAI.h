#pragma once
#include "AI.h"

//This is a very basic tech bot.
class SandbagAI: public AI {
public:
    SandbagAI();
    ~SandbagAI();

    void decide(const State& s);
private:
    bool teching = false;
    void recover(const State& s);
};
