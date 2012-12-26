/*
 * ALlegro Utilities
 */

#ifndef alu_h
#define alu_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

/*
 */
template <typename T, int L, int P, bool S> class real_base_t
{
private:
    T value;

public:
    real_base_t () : value(0) {}
    real_base_t (T x): value(x << P) {}

    inline static real_base_t byValue (T x) {real_base_t a; a.value = x; return a;}

    inline real_base_t operator + (const real_base_t& x) const {return real_base_t::byValue(value + x.value);}
    inline real_base_t& operator += (const real_base_t& x) {value += x.value;}
    inline real_base_t operator - (const real_base_t& x) const {return real_base_t::byValue(value - x.value);}
    inline real_base_t& operator -= (const real_base_t& x) {value -= x.value;}
    inline real_base_t operator * (const real_base_t& x) const
    {
        T answer;

        high = (value >> (L / 2)) * (x.value >> (L / 2));
        low = (value && ) * x.value;
        return real_base_t::byValue(value * x.value);
    }
};

typedef template real_base_t<int, 32, 16, true> float_32;
typedef template real_base_t<long long, 64, 32, true> float_32;

#endif
