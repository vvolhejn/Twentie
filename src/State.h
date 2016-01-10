#pragma once
#include "Types.h"

//global
const u32 A_FRAME = 0x804d7420;
const u32 A_CUR_MENU = 0x00479d30;
//I have no idea how to get the cursor addresses in a more logical way.
const u32 A_P1_CURSOR_X = 0x81118DEC;
const u32 A_P1_CURSOR_Y = 0x81118DF0;
const u32 A_P2_CURSOR_X = 0x0111826C;
const u32 A_P2_CURSOR_Y = 0x01118270;
const u32 A_P1_CHARACTER = 0x803F0E0A;
const u32 A_P2_CHARACTER = 0x803F0E2E;

//player - static
const u32 A_PLAYER_BLOCKS[] = {0x80453080, 0x80453F10, 0x80454DA0, 0x80455C30};
const u32 A_STOCKS = 0x8E;
const u32 A_PERCENT = 0x60;
const u32 A_X = 0x10;
const u32 A_Y = 0x14;

//player structure
const u32 A_PLAYER_DATA_POINTERS[] = {0x00453130, 0x00453FC0};
const u32 A_FACING_DIRECTION = 0x8C;
const u32 A_IN_AIR = 0x140;
const u32 A_AIR_SPEED_X = 0xE0;
const u32 A_AIR_SPEED_Y = 0xE4;
const u32 A_KNOCKBACK_X = 0xEC;
const u32 A_KNOCKBACK_Y = 0xF0;
const u32 A_ACTION_STATE = 0x70;
const u32 A_ACTION_STATE_FRAME = 0x8F4;
const u32 A_HITSTUN_LEFT = 0x23A0;
const u32 A_HITLAG_LEFT = 0x19BC;

struct Player {
    u16 percent;
    u8 stock;
    bool facingRight, inAir;
    float x, y;
    float airSpeedX, airSpeedY;
    float knockbackX, knockbackY;
    float cursorX, cursorY;
    u8 character;
    u32 actionState;
    float actionStateFrame;
    float hitstunLeft, hitlagLeft;
};

struct State {
    Player players[4];
    u32 frame;
    u32 curMenu;
};

enum MENU {
    CHARACTER_SELECT = 0,
    STAGE_SELECT = 1,
    IN_GAME = 2,
    POSTGAME_SCORES = 4
};

enum CHARACTER {
    DR_MARIO = 0,
    MARIO = 1,
    LUIGI = 2,
    BOWSER = 3,
    PEACH = 4,
    YOSHI = 5,
    DK = 6,
    C_FALCON = 7,
    GANONDORF = 8,
    FALCO = 9,
    FOX = 10,
    NESS = 11,
    ICE_CLIMBERS = 12,
    KIRBY = 13,
    SAMUS = 14,
    ZELDA = 15,
    LINK = 16,
    YOUNG_LINK = 17,
    PICHU = 18,
    PIKACHU = 19,
    JIGGLYPUFF = 20,
    MEWTWO = 21,
    MR_GAME_AND_WATCH = 22,
    MARTH = 23,
    ROY = 24
};

//from the cpu-level-11 project. currently unused.
enum ACTION {
    ON_HALO = 0x0d,
    STANDING = 0x0e,
    WALK_SLOW = 0x0f,
    WALK_MIDDLE = 0x10,
    WALK_FAST = 0x11,
    TURNING = 0x12,
    TURNING_RUN = 0x13,
    DASHING = 0x14,
    RUNNING = 0x15,
    KNEE_BEND = 0x18, //pre-jump animation.
    JUMPING_FORWARD = 0x19,
    JUMPING_BACKWARD = 0x1A,
    JUMPING_ARIAL_FORWARD = 0x1b,
    JUMPING_ARIAL_BACKWARD = 0x1c,
    FALLING = 0x1D,	//The "wait" state of the air.
    CROUCH_START = 0x27, //Going from stand to crouch
    CROUCHING = 0x28,
    CROUCH_END = 0x29, //Standing up from crouch
    LANDING = 0x2a, //Can be canceled. Not stunned
    LANDING_SPECIAL = 0x2b, //Landing special, like from wavedash. Stunned.
    NEUTRAL_ATTACK_1 = 0x2c,
    NEUTRAL_ATTACK_2 = 0x2d,
    NEUTRAL_ATTACK_3 = 0x2e,
    DASH_ATTACK = 0x32,
    FTILT_HIGH = 0x33,
    FTILT_HIGH_MID = 0x34,
    FTILT_MID = 0x35,
    FTILT_LOW_MID = 0x36,
    FTILT_LOW = 0x37,
    UPTILT = 0x38,
    DOWNTILT = 0x39,
    FSMASH_MID = 0x3c,
    UPSMASH = 0x3f,
    DOWNSMASH = 0x40,
    NAIR = 0x41,
    FAIR = 0x42,
    BAIR = 0x43,
    UAIR = 0x44,
    DAIR = 0x45,
    NAIR_LANDING  = 0x46,
    FAIR_LANDING  = 0x47,
    BAIR_LANDING  = 0x48,
    UAIR_LANDING  = 0x49,
    DAIR_LANDING  = 0x4a,
    DAMAGE_HIGH_1 = 0x4b,
    DAMAGE_HIGH_2 = 0x4c,
    DAMAGE_HIGH_3 = 0x4d,
    DAMAGE_NEUTRAL_1 = 0x4e,
    DAMAGE_NEUTRAL_2 = 0x4f,
    DAMAGE_NEUTRAL_3 = 0x50,
    DAMAGE_LOW_1 = 0x51,
    DAMAGE_LOW_2 = 0x52,
    DAMAGE_LOW_3 = 0x53,
    DAMAGE_AIR_1 = 0x54,
    DAMAGE_AIR_2 = 0x55,
    DAMAGE_AIR_3 = 0x56,
    DAMAGE_FLY_HIGH = 0x57,
    DAMAGE_FLY_NEUTRAL = 0x58,
    DAMAGE_FLY_LOW = 0x59,
    DAMAGE_FLY_TOP = 0x5a,
    DAMAGE_FLY_ROLL = 0x5b,
    SHIELD_START = 0xb2,
    SHIELD = 0xb3,
    SHIELD_RELEASE = 0xb4,
    SHIELD_STUN = 0xb5,
    SHIELD_REFLECT = 0xb6,
    GRAB = 0xd4,
    GRAB_RUNNING = 0xd6,
    ROLL_FORWARD = 0xe9,
    ROLL_BACKWARD = 0xea,
    SPOTDODGE = 0xEB,
    AIRDODGE = 0xEC,
    EDGE_TEETERING_START = 0xF5, //Starting of edge teetering
    EDGE_TEETERING = 0xF6,
    SLIDING_OFF_EDGE = 0xfb, //When you get hit and slide off an edge
    EDGE_CATCHING = 0xFC, //Initial grabbing of edge, stuck in stun here
    EDGE_HANGING = 0xFD,
    EDGE_GETUP_SLOW = 0xFE,  // >= 100% damage
    EDGE_GETUP_QUICK = 0xFF, // < 100% damage
    EDGE_ATTACK_SLOW = 0x100, // < 100% damage
    EDGE_ATTACK_QUICK = 0x101, // >= 100% damage
    EDGE_ROLL_SLOW = 0x102, // >= 100% damage
    EDGE_ROLL_QUICK = 0x103, // < 100% damage
    ENTRY = 0x142,	//Start of match. Can't move
    ENTRY_START = 0x143,	//Start of match. Can't move
    ENTRY_END = 0x144,	//Start of match. Can't move
    NEUTRAL_B_CHARGING = 0x156,
    NEUTRAL_B_ATTACKING = 0x157,
    NEUTRAL_B_CHARGING_AIR = 0x15A,
    NEUTRAL_B_ATTACKING_AIR = 0x15B,
    SWORD_DANCE_1 = 0x15d,
    SWORD_DANCE_2_HIGH = 0x15e,
    SWORD_DANCE_2_MID = 0x15f,
    SWORD_DANCE_3_HIGH = 0x160,
    SWORD_DANCE_3_MID = 0x161,
    SWORD_DANCE_3_LOW = 0x162,
    SWORD_DANCE_4_HIGH = 0x163,
    SWORD_DANCE_4_MID = 0x164,
    SWORD_DANCE_4_LOW = 0x165,
    SWORD_DANCE_1_AIR = 0x166,
    SWORD_DANCE_2_HIGH_AIR = 0x167,
    SWORD_DANCE_2_MID_AIR = 0x168,
    SWORD_DANCE_3_HIGH_AIR = 0x169,
    SWORD_DANCE_3_MID_AIR = 0x16a,
    SWORD_DANCE_3_LOW_AIR = 0x16b,
    SWORD_DANCE_4_HIGH_AIR = 0x16c,
    SWORD_DANCE_4_MID_AIR = 0x16d,
    SWORD_DANCE_4_LOW_AIR = 0x16e,
    FIREFOX_WAIT_GROUND = 0x161, //Firefox wait on the ground
    FIREFOX_WAIT_AIR = 0x162, //Firefox wait in the air
    FIREFOX_GROUND = 0x163, //Firefox on the ground
    FIREFOX_AIR = 0x164, //Firefox in the air
    DOWN_B_GROUND_START = 0x168,
    DOWN_B_GROUND = 0x169,
    DOWN_B_STUN = 0x16d, //Fox is stunned in these frames
    DOWN_B_AIR = 0x16e,
    UP_B_GROUND = 0x16f,
    UP_B = 0x170,	//The upswing of the UP-B. (At least for marth)
    MARTH_COUNTER = 0x171,
    MARTH_COUNTER_FALLING = 0x173,
};
