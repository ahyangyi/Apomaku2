#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "pbullet.h"
#include "global.h"

PBullet::PBullet () : n_frames (0)
{
}

PBullet::~PBullet ()
{
}

PBCommon::PBCommon (Position _pos, Position _spd, Position _acc) : pos(_pos), spd(_spd), acc(_acc)
{
}

void PBCommon::time_walk ()
{
    pos += spd / FPS;
    spd += acc / FPS;
}

bool PBCommon::dead ()
{
    return pos.x < -200 || pos.x > GAME_W + 200 || pos.y < -200 || pos.y > GAME_H + 200;
}

Position PBCommon::get_pos ()
{
    return pos;
}

PBulletType PBCommon::get_type ()
{
    return PBT_COMMON;
}

const Position PB00_spd[] =
{
    Position(0.0, -360.0),
};

const Position PB00_acc[] =
{
    Position(0.0, -2160.0),
};

PB00::PB00 (Position _pos, int _type) : PBCommon (_pos, PB00_spd[_type], PB00_acc[_type]), type(_type)
{
}

void PB00::draw ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_ONE, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));
    al_draw_bitmap(GAME_POS_C(pos, global.bitmap_c0b0[type]), 0);
}

const Position PB10_spd[] =
{
    Position(0.0, -1440.0),
};

const Position PB10_acc[] =
{
    Position(0.0, 0),
};

PB10::PB10 (Position _pos, int _type) : PBCommon (_pos, PB10_spd[_type], PB10_acc[_type]), type(_type)
{
}

void PB10::draw ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_ONE, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));
    al_draw_bitmap(GAME_POS_C(pos, global.bitmap_c1b0[type]), 0);
}
