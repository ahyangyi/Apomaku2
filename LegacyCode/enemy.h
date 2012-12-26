#ifndef __APOMAKU_ENEMY_H
#define __APOMAKU_ENEMY_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <list>
#include "sprite.h"
#include "utils.h"
#include "trace.h"

#define    ET_COMMON   0x0
#define    ET_BOSS     0x100
#define    ET_DEFORMED 0x200

typedef int EnemyType;

class Enemy: public Sprite
{
    public:

    Enemy ();
    virtual ~Enemy ();

    virtual bool take_damage (int damage); // returns true if it dies.
    virtual Position get_pos ();

    virtual void time_walk () = 0;
    virtual void draw () = 0;
    virtual bool dead () = 0;
    virtual bool collision_player (Position player) = 0;
    virtual double get_radius () = 0;
    virtual std::list<std::pair<Position, double> > get_pos_list () = 0;
    virtual int priority () = 0;
    virtual EnemyType get_type () = 0;

    protected:

    int n_frames, hp;
    Position pos;
};

class EnemyCommon: public Enemy
{
    public:

    EnemyCommon (double _radius);
    virtual ~EnemyCommon ();

    virtual bool collision_player (Position player);
    virtual EnemyType get_type ();
    virtual int priority ();
    virtual double get_radius ();
    virtual std::list<std::pair<Position, double> > get_pos_list ();

    virtual void time_walk () = 0;
    virtual void draw () = 0;
    virtual bool dead () = 0;

    protected:

    double radius;
};

class EnemyGlobal1: public EnemyCommon
{
    public:

    EnemyGlobal1 (Trace* _trace);
    virtual ~EnemyGlobal1 ();

    void time_walk ();
    void draw ();
    bool dead ();

    protected:

    Trace * trace;
    Position spd;
};

#endif
