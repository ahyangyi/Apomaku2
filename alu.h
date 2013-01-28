/*
 * ALlegro Utilities
 */

#ifndef alu_h
#define alu_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <mpreal.h>


class float_32 : public mpfr::mpreal
{
public:
    float_32() {}
    float_32(const float_32& u): mpfr::mpreal(u) {}
    float_32(const mpfr::mpreal& u): mpfr::mpreal(u) {}
    float_32(const mpfr_t u): mpfr::mpreal(u) {}    
    float_32(const mpf_t u) : mpfr::mpreal(u) {}    
    float_32(const mpz_t u) : mpfr::mpreal(u, 32) {};
    float_32(const mpq_t u) : mpfr::mpreal(u, 32) {};
    float_32(const double u) : mpfr::mpreal(u, 32) {};
    float_32(const long double u) : mpfr::mpreal(u, 32) {};
    float_32(const unsigned long int u) : mpfr::mpreal(u, 32) {};
    float_32(const unsigned int u) : mpfr::mpreal(u, 32) {};
    float_32(const long int u) : mpfr::mpreal(u, 32) {};
    float_32(const int u) : mpfr::mpreal(u, 32) {};
    float_32(const char* s) : mpfr::mpreal(s, 32) {};
    float_32(const std::string& s) : mpfr::mpreal(s, 32) {};
};

//typedef mpfr::float_32 float_32;

#endif
