#include <allegro5/allegro_native_dialog.h>
#include <cstdio>
#include <cmath>
#include "utils.h"
#include "global.h"

Position::Position () {x = GAME_W / 2; y = GAME_H * 7 / 8;}
Position::Position (double _x, double _y) : x(_x), y(_y) {};

Position& Position::operator += (const Position& a)
{
    x += a.x;
    y += a.y;
    return *this;
}
Position& Position::operator -= (const Position& a)
{
    x -= a.x;
    y -= a.y;
    return *this;
}

Position Position::operator + (const Position& a) const
{
    return Position(x+a.x, y+a.y);
}

Position Position::operator - (const Position& a) const
{
    return Position(x-a.x, y-a.y);
}

Position Position::operator * (double a) const
{
    return Position(x*a, y*a);
}

Position Position::operator / (double a) const
{
    return Position(x/a, y/a);
}

Position Position::operator % (double a) const
{
    double dis = sqrt(x*x + y*y);
    if (dis < 1e-6)
        return Position(0, -a);
    return Position(x*a/dis, y*a/dis);
}

double Position::operator / (const Position& a) const
{
    return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);
}

#include <cstdio>

double Position::angle () const
{
    return atan2 (-x, -y);
}

double Position::norm2 () const
{
    return x*x + y*y;
}

Position Position::direction (int dx, int dy)
{
    double dist = dx && dy? 0.625 : 1.0;
    return Position(dx * dist, dy * dist);
}

Position POSITION_INVALID (-500, -500);

void Utils::fatal_error (char const *format, ...)
{
    char str[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(str, sizeof str, format, args);
    va_end(args);

    al_show_native_message_box("Error", "We meet an error!", str, NULL, 0);
    exit(1);
}

void Utils::error (char const *format, ...)
{
    char str[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(str, sizeof str, format, args);
    va_end(args);

    al_show_native_message_box("Error", "We meet an error!", str, NULL, 0);
}

void Utils::terminate ()
{
    exit(0);
}
