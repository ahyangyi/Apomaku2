#include <assert.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <cstdio>
#include "enemy.h"
#include "global.h"

Enemy::Enemy () : n_frames (0)
{
}

Enemy::~Enemy ()
{
}

bool Enemy::take_damage (int damage)
{
    assert (hp > 0);

    hp -= damage;
    return hp <= 0;
}

Position Enemy::get_pos ()
{
    return pos;
}

EnemyCommon::EnemyCommon (double _radius) : radius(_radius)
{
}

EnemyCommon::~EnemyCommon ()
{
}

bool EnemyCommon::collision_player (Position player)
{
    return pos / player <= radius * radius;
}

EnemyType EnemyCommon::get_type ()
{
    return ET_COMMON;
}

int EnemyCommon::priority ()
{
    return 0; // FIXME
}

double EnemyCommon::get_radius ()
{
    return radius;
}

EnemyGlobal1::EnemyGlobal1 (Trace* _trace) : EnemyCommon (32), trace(_trace -> clone())
{
    this ->pos = trace->get_pos(0);
    this ->hp = 1;
}

EnemyGlobal1::~EnemyGlobal1 ()
{
    delete trace;
}

void EnemyGlobal1::time_walk ()
{
    Position new_pos = trace -> get_pos (n_frames);

    spd = new_pos - pos;
    pos = new_pos;

    n_frames ++;
}

void EnemyGlobal1::draw ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_ONE, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));
    al_draw_rotated_bitmap(GAME_POS_CR(pos, global.bitmap_e[0]), - spd.angle(), 0);
}

bool EnemyGlobal1::dead ()
{
    return hp <= 0 || trace -> outside ();
}

std::list<std::pair<Position, double> > EnemyCommon::get_pos_list ()
{
    std::list<std::pair<Position, double> > re;
    re.push_back (std::make_pair(pos, radius));
    return re;
}
