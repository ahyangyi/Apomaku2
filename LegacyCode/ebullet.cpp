#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "ebullet.h"
#include "global.h"

#define GRAZE_SIZE 16

EBullet::EBullet () : n_frames(0)
{
}

EBullet::~EBullet ()
{
}

EBCommon::EBCommon (ALLEGRO_BITMAP ** _sprite, Position start) : sprite(_sprite), cur(start)
{
}

EBCommon::~EBCommon ()
{
}

Position EBCommon::get_pos ()
{
    return cur;
}

void EBCommon::time_walk (Position player)
{
    Position dir = get_dir (player);
    cur += dir;
    previous_dir = dir;
}

void EBCommon::draw ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_ONE, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));
//    al_draw_bitmap(GAME_POS_C(cur, sprite[0]), 0);
    al_draw_rotated_bitmap(GAME_POS_CR(cur, sprite[0]), - previous_dir.angle(), 0);
}

bool EBCommon::dead ()
{
    return cur.x < -200 || cur.x > GAME_W + 200 || cur.y < -200 || cur.y > GAME_H + 200;
}

EBulletType EBCommon::get_type ()
{
    return EBT_COMMON;
}

EBCommonRound::EBCommonRound (ALLEGRO_BITMAP ** _sprite, double _radius, Position start) : EBCommon(_sprite, start), radius(_radius), grazed(false)
{
}

EBCommonRound::~EBCommonRound ()
{
}

int EBCommonRound::graze (Position player)
{
    return cur / player <= (radius + GRAZE_SIZE) * (radius + GRAZE_SIZE);
}

bool EBCommonRound::collision (Position player)
{
    return cur / player <= radius * radius;
}

EBCommonEllipse::EBCommonEllipse (ALLEGRO_BITMAP ** _sprite, double _a, double _b, Position start) : EBCommon(_sprite, start), a(_a), b(_b), grazed(false)
{
}

EBCommonEllipse::~EBCommonEllipse ()
{
}

#include <cstdio>

int EBCommonEllipse::graze (Position player)
{
    if (grazed) return 0;
    double a1, b1, c;

    a1 = (player.x - cur.x) * previous_dir.x + (player.y - cur.y) * previous_dir.y;
    b1 = (player.x - cur.x) * previous_dir.y - (player.y - cur.y) * previous_dir.x;
    c = previous_dir.norm2();
    return grazed = a1 * a1 / (a + GRAZE_SIZE) / (a + GRAZE_SIZE) / c +
        b1 * b1 / (b + GRAZE_SIZE) / (b + GRAZE_SIZE) / c <= 1;
}

bool EBCommonEllipse::collision (Position player)
{
    double a1, b1, c;

    a1 = (player.x - cur.x) * previous_dir.x + (player.y - cur.y) * previous_dir.y;
    b1 = (player.x - cur.x) * previous_dir.y - (player.y - cur.y) * previous_dir.x;
    c = previous_dir.norm2();
    return a1 * a1 / a / a / c +
        b1 * b1 / b / b / c <= 1;
}

EBLinear::EBLinear (ALLEGRO_BITMAP ** _sprite, double _a, double _b, Position start, Position speed) :
    EBCommonEllipse (_sprite, _a, _b, start), spd(speed)
{
}

EBLinear::~EBLinear ()
{
}

Position EBLinear::get_dir (Position player)
{
    return spd/FPS;
}
