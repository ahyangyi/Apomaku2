#ifndef __APOMAKU_RESLOAD_H
#define __APOMAKU_RESLOAD_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

class ResourceLoader
{
    public:

    ResourceLoader ();
    void load_bitmap (ALLEGRO_BITMAP** bitmap, const char* filename, ...);
    void load_font (ALLEGRO_FONT** font, const char* filename, int size, int flag);
    void false_load ();

    private:

    int n_frame;
    void clear_queue ();
};

#endif


