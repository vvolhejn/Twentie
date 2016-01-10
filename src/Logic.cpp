#include <iostream>
#include <chrono>
#include <bitset>
#include <algorithm>
#include <stdint.h>
#include <cstring>

#include "Logic.h"
#include "Controller.h"
#include "AI.h"

//Reinterpret a u32 value as float and save to *b
inline void setFloat(float *b, u32 a) {
    char* aPointer = (char*)&a, *bPointer = (char*)b;
    memcpy(bPointer, aPointer, sizeof(a));
}

//Debugging function used to find out how the values are encoded
void binaryPrint(u32 x) {
    std::bitset<32> b(x);
    std::cout << b << " " << x << std::endl;
}

Logic::Logic() {
}

//The absolute menu value changes between installations for some reason, although the relative difference is constant.
//To fix this, we save the value for character select and calculate the values off of that.
//However, this means that the bot has to be started before Melee in Dolphin.
u32 menuOffset = 0;
AI ai;

void Logic::onMemoryChange(u32 pos, u32 val, s16 player) {
    if(pos == A_FRAME) {
        s.frame = val;
        switch(s.curMenu) {
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
        case MENU::IN_GAME:
            ai.decide(s);
            break;
        }
    } else {
        changeState(pos, val, player);
    }
}

void Logic::changeState(u32 pos, u32 val, s16 player) {
    if(player == -1) {
        switch(pos) { //Global values
        case A_CUR_MENU:
            if(val != s.curMenu) {
                if(!menuOffset) menuOffset = val;
            }
            s.curMenu = val - menuOffset;
            return;
        case A_P1_CURSOR_X:
            setFloat(&s.players[0].cursorX, val);
            return;
        case A_P1_CURSOR_Y:
            setFloat(&s.players[0].cursorY, val);
            return;

        //These values are "per-player", but they are not in the normal static block
        //and so we have to treat them individually
        case A_P2_CURSOR_X:
            setFloat(&s.players[1].cursorX, val);
            return;
        case A_P2_CURSOR_Y:
            setFloat(&s.players[1].cursorY, val);
            return;
        case A_P1_CHARACTER:
            s.players[0].character = (val >> 24);
            return;
        case A_P2_CHARACTER:
            s.players[1].character = (val >> 24);
            return;
        }
        for(u32 i = 0; i < 4; i++) { //Static values, but for each player
            //switch doesn't work here because the values aren't considered constant
            if(pos == A_PLAYER_BLOCKS[i] + A_X) {
                setFloat(&s.players[i].x, val);
                return;
            } else if(pos == A_PLAYER_BLOCKS[i] + A_Y) {
                setFloat( &s.players[i].y, val);
                return;
            } else if (pos == A_PLAYER_BLOCKS[i] + A_PERCENT) {
                s.players[i].percent = (u16)(val >> 16);
                return;
            } else if (pos == A_PLAYER_BLOCKS[i] + A_PERCENT) {

            }
        }
    } else {
        switch(pos) {
        case A_FACING_DIRECTION:
            s.players[player].facingRight = !(val & (1 << 31));
            return;
        case A_IN_AIR:
            s.players[player].inAir = val;
            return;
        case A_AIR_SPEED_X:
            setFloat(&s.players[player].airSpeedX, val);
            return;
        case A_AIR_SPEED_Y:
            setFloat(&s.players[player].airSpeedY, val);
            return;
        case A_KNOCKBACK_X:
            setFloat(&s.players[player].knockbackX, val);
            return;
        case A_KNOCKBACK_Y:
            setFloat(&s.players[player].knockbackY, val);
            return;
        case A_ACTION_STATE:
            s.players[player].actionState = val;
            return;
        case A_ACTION_STATE_FRAME:
            setFloat(&s.players[player].actionStateFrame, val);
            return;
        case A_HITSTUN_LEFT:
            //this value can mean more things, needs more testing.
            setFloat(&s.players[player].hitstunLeft, val);
            return;
        case A_HITLAG_LEFT: //the "freeze frames", such as on knee
            setFloat(&s.players[player].hitlagLeft, val);
            return;
        }
    }
    //The unrecognized value is printed as float, binary and int.
    float x;
    setFloat(&x, val);
    std::cout << "Unrecognized memory value: " << pos << " to " << val << " (P " << player << "): " << x << std::endl;
    binaryPrint(val);

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

