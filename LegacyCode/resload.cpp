#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <cmath>
#include <cstdio>
#include "utils.h"
#include "global.h"
#include "resload.h"

void ResourceLoader::clear_queue ()
{
    ALLEGRO_EVENT event;
    bool to_paint = false;

    while (!al_event_queue_is_empty(global.queue))
    {
        al_wait_for_event(global.queue, &event);
        switch (event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                Utils::terminate();
            case ALLEGRO_EVENT_TIMER:
                to_paint = true;
                n_frame ++;
        };
    }

    if (to_paint)
    {
        al_clear_to_color(global.color_black);
        al_set_blender(ALLEGRO_ALPHA, ALLEGRO_ZERO, al_map_rgba_f(1, 1, 1, 1));
        al_draw_bitmap(global.bitmap_splash, 0, 0, 0);
        float r, g, b;
        al_color_hsv_to_rgb(180 + 80 * sin(n_frame * M_PI / FPS), 0.3, 1, &r, &g, &b);
        al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(r, g, b, 0.36));
        al_draw_textf(global.font_splash, 20, al_get_display_height() - 55, ALLEGRO_ALIGN_LEFT, "NOW LOADING");
        al_flip_display();
    }
}

ResourceLoader::ResourceLoader () : n_frame(0)
{
}

void ResourceLoader::load_bitmap (ALLEGRO_BITMAP** bitmap, const char* filename, ...)
{
    char str[1024];
    va_list args;
    va_start(args, filename);
    vsnprintf(str, sizeof str, filename, args);
    va_end(args);

    *bitmap = al_load_bitmap(str);
    if (!*bitmap)
    {
        Utils::error("Failed to load bitmap resource: %s.\n", str);
        *bitmap = al_create_bitmap (1,1);
        if (!*bitmap)
            Utils::error("Failed to create dummy bitmap: %s.\n", str);
    }
    clear_queue();
}

void ResourceLoader::load_font (ALLEGRO_FONT** font, const char* filename, int size, int flag)
{
    *font = al_load_font(filename, size, flag);
    clear_queue();
}

void ResourceLoader::false_load ()
{
    while (n_frame < 3 * FPS)
        clear_queue ();
}
