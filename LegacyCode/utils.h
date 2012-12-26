#ifndef __APOMAKU_UTILS_H
#define __APOMAKU_UTILS_H

class Position
{
    public:

    double x, y;

    Position ();
    Position (double _x, double _y);

    Position& operator += (const Position& a);
    Position& operator -= (const Position& a);
    Position operator + (const Position& a) const;
    Position operator - (const Position& a) const;
    Position operator * (double a) const;
    Position operator / (double a) const;
    Position operator % (double a) const;        // Unified vector
    double operator / (const Position& a) const; // Distance Squared

    double angle () const;
    double norm2 () const;

    static Position direction (int dx, int dy);
};

extern Position POSITION_INVALID;

class Utils
{
    public:
    static void fatal_error (char const *format, ...);
    static void error (char const *format, ...);
    static void terminate ();
};

#endif

