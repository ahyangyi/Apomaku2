#ifndef __APOMAKU_PBULLET_H
#define __APOMAKU_PBULLET_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "sprite.h"
#include "utils.h"

enum PBulletType
{
    PBT_COMMON,
    PBT_LASER,
};

class PBullet: public Sprite
{
    public:

    PBullet ();
    virtual ~PBullet ();

    virtual void time_walk () = 0;
    virtual void draw () = 0;
    virtual bool dead () = 0;
    virtual Position get_pos () = 0;
    virtual PBulletType get_type () = 0;

    protected:

    int n_frames;
};

class PBCommon : public PBullet
{
    public:

    PBCommon (Position _pos, Position _spd, Position _accs);
    virtual void time_walk ();
    virtual bool dead ();
    virtual Position get_pos ();
    virtual PBulletType get_type ();

    protected:

    Position pos, spd, acc;
};

class PB00 : public PBCommon
{
    public:

    PB00 (Position _pos, int _type);
    virtual void draw ();

    private:

    int type;
};

class PB10 : public PBCommon
{
    public:

    PB10 (Position _pos, int _type);
    virtual void draw ();

    private:

    int type;
};

#endif
