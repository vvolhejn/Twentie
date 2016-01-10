#include "AI.h"
#include "Controller.h"

AI::AI() {}

//It is possibly more clean to have the AI return a vector of actions to be performed?

//This is a very basic tech bot.
//It techs in a random direction before hitting the ground. Does not recover.
void AI::decide(const State &s) {
    if(s.players[1].inAir && s.players[1].y < 3
            && (s.players[1].airSpeedY + s.players[1].knockbackY < 0)) {
        if(!teching) {
            setAnalogButton("L", 1.0);
            int dir = rand() % 3;
            setStick(true, 0.5 * dir, 0.5);
            teching = true;
        }
    } else {
        setAnalogButton("L", 0.0);
        setStick(true, 0.5, 0.5);
        teching = false;
    }
}
