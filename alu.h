/*
 * ALlegro Utilities
 */

#ifndef alu_h
#define alu_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <mpreal.h>

template <int P> class real : public mpfr::mpreal
{
public:
    real() {}
    template <int Q> real(const real<Q>& u): mpfr::mpreal(u) {}
    real(const mpfr::mpreal& u): mpfr::mpreal(u) {}
    real(const mpfr_t u): mpfr::mpreal(u) {}    
    real(const mpf_t u) : mpfr::mpreal(u) {}    
    real(const mpz_t u) : mpfr::mpreal(u, P) {};
    real(const mpq_t u) : mpfr::mpreal(u, P) {};
    real(const double u) : mpfr::mpreal(u, P) {};
    real(const long double u) : mpfr::mpreal(u, P) {};
    real(const unsigned long int u) : mpfr::mpreal(u, P) {};
    real(const unsigned int u) : mpfr::mpreal(u, P) {};
    real(const long int u) : mpfr::mpreal(u, P) {};
    real(const int u) : mpfr::mpreal(u, P) {};
    real(const char* s) : mpfr::mpreal(s, P) {};
    real(const std::string& s) : mpfr::mpreal(s, P) {};
};

typedef real<32> alu_real;

#endif
