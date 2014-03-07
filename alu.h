/*
 * ALlegro Utilities
 */

#ifndef alu_h
#define alu_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <boost/multiprecision/mpfr.hpp>

namespace mp = boost::multiprecision;     // Reduce the typing a bit later...

typedef mp::number<mp::mpfr_float_backend<32> > alu_real;

#endif
