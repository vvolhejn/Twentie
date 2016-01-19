#include <iostream>
#include <typeinfo>

#include "SandbagAI.h"
#include "Controller.h"
#include "Logic.h"
#include "action/AllActions.h"

Action* action;

SandbagAI::SandbagAI() {
    action = NULL;
}
SandbagAI::~SandbagAI() {
    delete action;
}

void SandbagAI::decide(const State& s) {
    //std::cout << "Pos: " << s.players[0].x << " " << s.players[0].y << std::endl;
    if(action != NULL) { //action started on a previous frame
        if(action->hasEnded(s)) { //last frame of the action
            delete action;
            action = NULL;
            resetInputs();
            return;
        } else {
            action->execute(s);
            return;
        }
    }
    if(s.me.inLag()) return;

    do {
        if(s.me.actionState == ACTION::ON_HALO) { //on the spawn platform
            setStick(true, 0.5, 0);
            action = new WaitFor([](const State & s) {
                return s.me.actionState != ACTION::ON_HALO;
            });
            break;
        }
        if(s.me.hitlagLeft > 0) {
            action = new DI();
            break;
        }
        if(s.me.inTumble()) {
            if(s.me.airSpeedY + s.me.knockbackY < 0 && s.distanceToEdge(ME) > 3) {
                const float framesToLanding = -s.me.y / (s.me.airSpeedY + s.me.knockbackY);
                if(framesToLanding < 3) { //linear approximation
                    action = new Tech(s.frame);
                    break;
                }
            }
        }
        //if(s.me.vurnerability == 2) Yay, we're invurnerable!
        if(s.me.actionState == ACTION::EDGE_HANGING) {
            action = new Ledgedash(s.frame);
            break;
        } else if(s.isOffstage(ME)) {
            recover(s);
            if(action != NULL) break;
        }
    } while(false); //"cycle" allows us to break out at will and just set the action

    if(action != NULL) {
        std::cout << "New action: " << typeid(*action).name() << std::endl;
        action->execute(s);
    }
}

void SandbagAI::recover(const State& s) {
    if(s.me.hitstunLeft != 0) return; //Analog inputs have no effect during hitstun.

    auto doNotDrift = [](const State & s) {
        if(s.me.airSpeedY + s.me.airSpeedY > 0) return false; //flying up
        if(s.me.y > 30) return false; //too high
        if(s.me.y > 0 && (-s.distanceToEdge(ME) / s.me.y) < 0.15) return false; //close to the stage
        return true;
    };
    if(!doNotDrift(s)) { //we can just drift onstage
        setStick(true, s.me.toCenter(), 0.5);
        action = new WaitFor(doNotDrift);
        return;
    }
    if(s.distanceToEdge(ME) < -90) { //really far from the stage
        if(s.me.jumpsUsed < 2) {
            setButton("X", true);
            action = new WaitFor(s.frame + 1);
            return;
        }
        if(s.me.y > 0) {
            setStick(true, s.me.toCenter(), 0.5);
            action = new WaitFor([](const State & s) {
                return (s.me.actionState != ACTION::FALLING) || (s.me.y <= 0);
            });
        } else {
            action = new FoxUpB(s.frame);
            return;
        }
    }
    if(s.me.y < -15) { //too low to side-b. TODO: Account for y-speed here.
        if(s.me.jumpsUsed < 2) {
            setButton("X", true);
            action = new WaitFor(s.frame + 1);
        } else {
            action = new FoxUpB(s.frame);
        }
    } else if(s.me.y < -5) {
        action = new FoxSideB(s.frame, s.me.x < 0);
    } else {
        action = new FoxUpB(s.frame);
    }
}
