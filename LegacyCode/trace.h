#ifndef __APOMAKU_TRACE_H
#define __APOMAKU_TRACE_H

#include "utils.h"
#include <list>

class Trace
{
    public:

    virtual Position get_pos (int time) = 0;
    virtual bool outside () = 0;

    virtual Trace* clone () = 0;
};

class LinearTrace : public Trace
{
    public:

    LinearTrace ();

    virtual Position get_pos (int time);
    virtual bool outside ();
    virtual LinearTrace added (Position a, double t) const;
    virtual LinearTrace add (Position a, double t);
    virtual Trace* clone ();

    private:

    std::list<std::pair<Position, double> > l;
};

#endif
