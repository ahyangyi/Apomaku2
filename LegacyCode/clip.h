#ifndef __APOMAKU_CLIP_H
#define __APOMAKU_CLIP_H

#include "utils.h"

class Clip
{
    public:

    virtual void time_walk () = 0;
    virtual void draw (Position pos) = 0;
    virtual void jumpto (int x) = 0;
};

class SingleClip : public Clip
{
    public:

    virtual void time_walk () = 0;
    virtual void draw (Position pos) = 0;
    virtual void jumpto (int x) = 0;
};

class MovieClip : public Clip
{
    public:

    virtual void time_walk () = 0;
    virtual void draw (Position pos) = 0;
    virtual void jumpto (int x) = 0;
};

#endif
