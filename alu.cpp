#include "alu.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

#define SPRITE_MAX_LINECHAR 2048

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

void __alu_parse_framelist_callback_max (int frame, void *para)
{
    if (frame > *(int *)para)
        *(int *)para = frame;
}

char * __alu_parse_framelist (char *ptr, void *para, void (*callback)(int, void*))
{
    int current = 0, previous;
    char seperator = ',';
    
    if (ptr == NULL)
        return NULL;

    while (*ptr == ' ')
        ptr ++;
    while (*ptr != ' ' && *ptr != '\0')
    {
        if (*ptr >= '0' && *ptr <= '9')
            current = current * 10 + (*ptr)-'0';
        else
        {
            if (seperator == '-')
            {
                int i;
                
                for (i = previous + 1; i <= current; i ++)
                    callback(i, para);
            }
            else
                callback(current, para);

            seperator = *ptr;
            previous = current;
        }
        ptr ++;
    }
    
    if (seperator == '-')
    {
        int i;
        
        for (i = previous + 1; i <= current; i ++)
            callback(i, para);
    }
    else
        callback(current, para);
    
    return ptr;
}

char * __alu_parse_keyword (char *ptr, char *ret)
{
    if (ptr == NULL)
    {
        *ret = 0;
        return NULL;
    }
    while (*ptr == ' ')
        ptr ++;
    while (*ptr != ' ' && *ptr != '\0')
        *(ret++) = *(ptr++);
    *ret = 0;
    
    return ptr;
}

ALU_SPRITE* alu_create_sprite (const ALU_SPRITE_CLASS* sprite_class)
{
    ALU_SPRITE* ret = malloc(sizeof(ALU_SPRITE));
    
    ret->class = sprite_class;
    ret->frame = sprite_class->startframe;
    
    return ret;
}

ALU_SPRITE_CLASS* alu_load_sprite_class(const char* filename)
{
	ALU_SPRITE_CLASS* ret = malloc(sizeof(ALU_SPRITE_CLASS));

	ret->n_frame = 0;
	ret->n_aw = 0;
	ret->n_pre = 0;

	{
		ALLEGRO_FILE* f = al_fopen(filename, "r");

		char buf[SPRITE_MAX_LINECHAR];

		while (al_fgets(f, buf, SPRITE_MAX_LINECHAR))
        {
            char* ptr = buf;
            char buf2[SPRITE_MAX_LINECHAR];
            
            ptr = __alu_parse_keyword(ptr, buf2);
            
            if (strcmp(buf2,"frame") == 0)
            {
                ptr = __alu_parse_framelist(ptr, (void *)&ret->n_frame, __alu_parse_framelist_callback_max);
            }
            else if (strcmp(buf2,"autojump") == 0)
            {
            }
            else if (strcmp(buf2,"actionword") == 0)
            {
                ret->n_aw ++;
            }
            else if (strcmp(buf2,"actionjump") == 0)
            {
            }
            else if (strcmp(buf2,"predicate") == 0)
            {
                ret->n_pre ++;
            }
        }
	}
    
    
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
