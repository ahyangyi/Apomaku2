#ifndef apmk_resource_h
#define apmk_resource_h

#include "alu.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ALU_SPRITE_CLASS* APMK_RES_BG_MAIN;
extern ALU_SPRITE_CLASS* APMK_RES_PC[8];
    
void apmk_init_resource();

#ifdef __cplusplus
}
#endif

#endif
