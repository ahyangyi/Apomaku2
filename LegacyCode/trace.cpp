#include "trace.h"
#include <cstdio>

using namespace std;

LinearTrace::LinearTrace ()
{
}

Position LinearTrace::get_pos (int time)
{
    if (l.size() == 0)
        return Position (-500, -500);
    while (l.size() > 1 && (++l.begin())->second < time)
        l.pop_front ();

    if (l.size() == 1)
        return l.front().first;

    list<pair<Position, double> >::iterator it, jt;

    it = l.begin ();
    jt = it; jt ++;

    return it -> first * ((time - jt -> second) / (double) (it -> second - jt -> second)) +
        jt -> first * ((time - it -> second) / (double) (jt -> second - it -> second));
}

bool LinearTrace::outside ()
{
    return (l.size() <= 1);
}

LinearTrace LinearTrace::added (Position a, double t) const
{
    LinearTrace re;
    re.l.push_back(make_pair(a,t));

    return re;
}

LinearTrace LinearTrace::add (Position a, double t)
{
    l.push_back(make_pair(a,t));

    return *this;
}

Trace* LinearTrace::clone ()
{
    return new LinearTrace (*this);
}
