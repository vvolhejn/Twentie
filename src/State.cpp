#include "State.h"
#include <bitset>
#include <iostream>
#include <cstring>
#include <algorithm>

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


void State::update(u32 pos, u32 val, s16 player) {
    if(player == -1) {
        switch(pos) { //Global values
        case A_CUR_MENU:
            if(val != curMenu) {
                if(!menuOffset) menuOffset = val;
            }
            curMenu = val - menuOffset;
            return;
        case A_P1_CURSOR_X:
            setFloat(&players[0].cursorX, val);
            return;
        case A_P1_CURSOR_Y:
            setFloat(&players[0].cursorY, val);
            return;

        //These values are "per-player", but they are not in the normal static block
        //and so we have to treat them individually
        case A_P2_CURSOR_X:
            setFloat(&players[1].cursorX, val);
            return;
        case A_P2_CURSOR_Y:
            setFloat(&players[1].cursorY, val);
            return;
        case A_P1_CHARACTER:
            players[0].character = (val >> 24);
            return;
        case A_P2_CHARACTER:
            players[1].character = (val >> 24);
            return;
        }
        for(u32 i = 0; i < 4; i++) { //Static values, but for each player
            //switch doesn't work here because the values aren't considered constant
            if(pos == A_PLAYER_BLOCKS[i] + A_X) {
                setFloat(&players[i].x, val);
                //if(!i) std::cout<<players[i].x<<std::endl;
                return;
            } else if(pos == A_PLAYER_BLOCKS[i] + A_Y) {
                setFloat( &players[i].y, val);
                //if(!i) std::cout<<players[i].y<<std::endl;
                return;
            } else if (pos == A_PLAYER_BLOCKS[i] + A_PERCENT) {
                players[i].percent = (u16)(val >> 16);
                return;
            } else if (pos == A_PLAYER_BLOCKS[i] + A_PERCENT) {

            }
        }
    } else {
        switch(pos) {
        case A_FACING_DIRECTION:
            players[player].facingRight = !(val & (1 << 31));
            return;
        case A_IN_AIR:
            players[player].inAir = val;
            return;
        case A_AIR_SPEED_X:
            setFloat(&players[player].airSpeedX, val);
            return;
        case A_AIR_SPEED_Y:
            setFloat(&players[player].airSpeedY, val);
            return;
        case A_KNOCKBACK_X:
            setFloat(&players[player].knockbackX, val);
            return;
        case A_KNOCKBACK_Y:
            setFloat(&players[player].knockbackY, val);
            return;
        case A_ACTION_STATE:
            players[player].actionState = (ACTION) val;
            updateHitstun(player);
            //if(player==0)std::cout<<val<<std::endl;
            return;
        case A_ACTION_STATE_FRAME:
            setFloat(&players[player].actionStateFrame, val);
            return;
        case A_HITSTUN_LEFT: //this value can mean more things
            players[player].rawHitstunI = val;
            setFloat(&players[player].rawHitstunF, val);
            updateHitstun(player);
            return;
        case A_HITLAG_LEFT: //the "freeze frames", such as on knee
            float temp;
            setFloat(&temp, val);
            players[player].hitlagLeft = lroundf(temp);
            return;
        case A_JUMPS_USED:
            players[player].jumpsUsed = (val >> 24);
            return;
        case A_VURNERABILITY:
            players[player].vurnerability = val;
            return;
        }
    }
    //The unrecognized value is printed as float, binary and int.
    float x;
    setFloat(&x, val);
    std::cout << "Unrecognized memory value: " << pos << " to " << val << " (P " << player << "): " << x << std::endl;
    binaryPrint(val);

}


void State::updateHitstun(u16 player) {
    //whether it is a "damage" type state
    if(players[player].inTumble()) {
        players[player].hitstunLeft = lroundf(players[player].rawHitstunF);
    } else {
        players[player].hitstunLeft = 0;
    }
}

bool State::isOffstage(u16 p) const {
    return players[p].inAir && fabs(players[p].x) >= 87.4857;
}

float State::distanceToEdge(u16 p) const { //positive is on-stage, negative off-stage
    return 87.4857 - fabs(players[p].x);
}

//player

float Player::toCenter() const {
    return (x < 0) ? 1.0 : 0.1;
}

bool Player::inTumble() const {
    return actionState >= DAMAGE_HIGH_1 && actionState <= DAMAGE_FLY_ROLL;
}

bool Player::inLag() const {
    if(actionState>ACTION::MAXIMUM_STATE) return true;
    switch(actionState) {
    //obviously some stuff is missing, needs reseatch
    case 0: //dead, basically
    case ENTRY: //game start
    case ENTRY_START:
    case ENTRY_END:
    case PASSIVE: //techs
    case PASSIVE_CEIL:
    case PASSIVE_STAND_B:
    case PASSIVE_STAND_F:
    case PASSIVE_WALL:
    case PASSIVE_WALL_JUMP:
    case EDGE_CATCHING:
    case LANDING_SPECIAL:
    case AIRDODGE:
    case SPOTDODGE:
    //edge options
    case EDGE_GETUP_SLOW:
    case EDGE_GETUP_QUICK:
    case EDGE_ATTACK_SLOW:
    case EDGE_ATTACK_QUICK:
    case EDGE_ROLL_SLOW:
    case EDGE_ROLL_QUICK:
    //fox-specific
    case SIDE_B:
    case SIDE_B_END:
        return true;
    default:
        return false;
    }
}
