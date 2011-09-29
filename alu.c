#include "alu.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory.h>
#include <string.h>

struct ALU_SPRITE_CLASS
{
	ALLEGRO_BITMAP** frame;
    int* autojump;
    int* actionjump;
    bool* predicate;
    const char** actionname;
    const char** predicatename;
    
    int startframe;
    
    int n_frame, n_aw, n_pre;
};

struct ALU_SPRITE
{
    const ALU_SPRITE_CLASS* class;
    int frame;
};

int __alu_get_action_id (const ALU_SPRITE_CLASS* sprite_class, const char* action)
{
    if (action == NULL)
        return -1;
    
    int i;
    
    for (i = 0; i < sprite_class->n_aw; i ++)
        if (strcmp(sprite_class->actionname[i], action) == 0)
            return i;
    
    return -1;
}

ALU_SPRITE* alu_create_sprite (const ALU_SPRITE_CLASS* sprite_class)
{
    ALU_SPRITE* ret = malloc(sizeof(ALU_SPRITE));
    
    ret->class = sprite_class;
    ret->frame = sprite_class->startframe;
    
    return ret;
}

ALU_SPRITE_CLASS* alu_load_sprite_class_from_bitmap(const char* filename)
{
    ALU_SPRITE_CLASS* ret = malloc(sizeof(ALU_SPRITE_CLASS));
    ret->frame = malloc(sizeof(ALLEGRO_BITMAP *));
    ret->frame[0] = al_load_bitmap(filename);
    
    ret->n_frame = 1;
    ret->n_aw = 0;
    ret->n_pre = 0;
    
    ret->startframe = 0;
    
    return ret;
}

ALLEGRO_BITMAP* alu_get_bitmap (const ALU_SPRITE* sprite)
{
    return sprite->class->frame[sprite->frame];
}

void alu_sprite_tick(ALU_SPRITE* sprite, const char* action)
{
    int actionid = __alu_get_action_id(sprite->class, action);
    int next;
    
    if (actionid == -1)
        next = sprite->class->autojump[sprite->frame];
    else
        next = sprite->class->actionjump[sprite->frame + actionid * sprite->class->n_frame];
    
    if (next == -1) next = sprite->frame + 1;
    
    sprite->frame = next;
}