#ifndef __APOMAKU_GAME_H
#define __APOMAKU_GAME_H
#include "enum.h"

#define MAX_PLAYER_BULLETS 1024
#define MAX_ENEMY_BULLETS 16384
#define MAX_ENEMIES 1024

#define HP_PER_LIFE 5
#define INVINCIBLE_TIME (FPS*2)

class PBullet; // forward declaration
class EBullet; // forward declaration
class Enemy; // forward declaration

class GameData
{
    public:

    CharacterID character;
    Position cur_pos;

    int power, hp, graze;

    // Pbullets

    PBullet * pbullet[MAX_PLAYER_BULLETS];
    int n_pbullet;

    // Ebullets

    EBullet * ebullet[MAX_ENEMY_BULLETS];
    int n_ebullet;

    // Enemies

    Enemy * enemy[MAX_ENEMIES];
    int n_enemy;

    // Flags

    bool fl_shooting, fl_invincible;
    int shootframe, invincible_count;
};

class Game
{
    public:

    Game (CharacterID _character);
    void run ();

    GameData gamedata;

    private:

    bool paused;
    int n_frame, d_frame;
    void time_walk ();
};

#endif

