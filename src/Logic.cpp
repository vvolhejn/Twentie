#include <iostream>
#include <bitset>
#include <algorithm>
#include <stdint.h>
#include <cstring>

#include "Logic.h"
#include "Controller.h"
#include "ai/SandbagAI.h"


Logic::Logic() {
    ai = new SandbagAI();
}

Logic::~Logic() {
    delete ai;
}

void Logic::onMemoryChange(u32 pos, u32 val, s16 player) {
    if(pos == A_FRAME) {
        s.frame = val;
        switch(s.curMenu) {
        case MENU::IN_GAME:
            ai->decide(s);
            break;
        case MENU::CHARACTER_SELECT:
            selectCharacter();
            break;
        case MENU::STAGE_SELECT:
            //leave this to the player
            //(because I don't know where the pointer coordinates are saved)
            break;
        case MENU::POSTGAME_SCORES:
            setButton("START", s.frame % 2);
            break;
        }
    } else {
        s.update(pos, val, player);
    }
}


//Always selects Fox. I haven't found out how to detect whether the character is selected or only hovered over.
void Logic::selectCharacter() {
    const float EPS = 1.5;
    const float FOX_X = -23;
    const float FOX_Y = 11;
    setButton("START", false);
    float xv = 0.5, yv = 0.5;
    if(s.players[1].cursorX < FOX_X - EPS) xv = 1;
    else if (s.players[1].cursorX > FOX_X + EPS) xv = 0;
    if(s.players[1].cursorY < FOX_Y - EPS) yv = 1;
    else if (s.players[1].cursorY > FOX_Y + EPS) yv = 0;

    //The character was selected from a previous match; no action necessary
    if(s.players[1].character == CHARACTER::FOX && s.players[1].cursorY < 0) return;

    setButton("A", xv == 0.5 && yv == 0.5);
    setStick(true, xv, yv);
}

