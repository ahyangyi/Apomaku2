#include "resource.h"

ALU_SPRITE_CLASS* APMK_RES_BG_MAIN;
ALU_SPRITE_CLASS* APMK_RES_PC[8];

void apmk_init_resource ()
{
	APMK_RES_BG_MAIN = alu_load_sprite_class_from_bitmap("image/main.png");
    APMK_RES_PC[0] = alu_load_sprite_class_from_bitmap("image/c0.png");
}
