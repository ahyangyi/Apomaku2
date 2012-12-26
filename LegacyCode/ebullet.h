#ifndef __APOMAKU_EBULLET_H
#define __APOMAKU_EBULLET_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "sprite.h"
#include "utils.h"

enum EBulletType
{
    EBT_COMMON,
    EBT_AREA,
};

class EBullet: public Sprite
{
    public:

    EBullet ();
    virtual ~EBullet ();

    virtual void time_walk (Position player) = 0;
    virtual void draw () = 0;
    virtual bool dead () = 0;
    virtual int graze (Position player) = 0;
    virtual bool collision (Position player) = 0;
    virtual Position get_pos () = 0;
    virtual EBulletType get_type () = 0;

    protected:

    int n_frames;
};

class EBCommon : public EBullet
{
    public:

    EBCommon (ALLEGRO_BITMAP ** _sprite, Position start);
    virtual ~EBCommon ();

    virtual void time_walk (Position player);
    virtual void draw ();
    virtual bool dead ();
    virtual int graze (Position player) = 0;
    virtual bool collision (Position player) = 0;
    virtual Position get_pos ();
    virtual Position get_dir (Position player) = 0;
    virtual EBulletType get_type ();

    protected:

    ALLEGRO_BITMAP ** sprite;
    Position cur, previous_dir;
};

class EBCommonRound : public EBCommon
{
    public:

    EBCommonRound (ALLEGRO_BITMAP ** _sprite, double _radius, Position start);
    virtual ~EBCommonRound ();

    virtual int graze (Position player);
    virtual bool collision (Position player);

    private:

    double radius;
    bool grazed;
};

class EBCommonEllipse : public EBCommon
{
    public:

    EBCommonEllipse (ALLEGRO_BITMAP ** _sprite, double _a, double _b, Position start);
    virtual ~EBCommonEllipse ();

    virtual int graze (Position player);
    virtual bool collision (Position player);

    private:

    double a, b;
    bool grazed;
};

class EBLinear : public EBCommonEllipse
{
    public:

    EBLinear (ALLEGRO_BITMAP ** _sprite, double _a, double _b, Position start, Position speed);
    virtual ~EBLinear ();

    virtual Position get_dir (Position player);

    private:

    Position spd;
};

#endif
