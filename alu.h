/*
 * ALlegro Utilities
 */

#ifndef alu_h
#define alu_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#ifdef __cplusplus
   extern "C" {
#endif

typedef struct ALU_SPRITE_CLASS ALU_SPRITE_CLASS;
typedef struct ALU_SPRITE ALU_SPRITE;

ALU_SPRITE_CLASS* alu_load_sprite_class(const char* filename);
ALU_SPRITE_CLASS* alu_load_sprite_class_from_bitmap(const char* filename);
void alu_destroy_sprite_class(ALU_SPRITE_CLASS* sprite);

ALU_SPRITE* alu_create_sprite (const ALU_SPRITE_CLASS* sprite_class);
void alu_destroy_sprite (ALU_SPRITE* sprite);
       
void alu_sprite_tick(ALU_SPRITE* sprite, const char* action);
bool alu_sprite_predicate(ALU_SPRITE* sprite, const char* predicate);
ALLEGRO_BITMAP* alu_get_bitmap (const ALU_SPRITE* sprite);

#ifdef __cplusplus
   }
#endif

#endif
