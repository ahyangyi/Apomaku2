#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "utils.h"
#include "global.h"
#include "resload.h"
#include "mmenu.h"
#include "enum.h"

void parse_options (int argc, char** argv)
{
}

void initialize ()
{
    if (!al_init())
        Utils::fatal_error("Failed to init Allegro.\n");
    if (!al_init_image_addon())
        Utils::fatal_error("Failed to init IIO addon.\n");
    al_init_font_addon();
    al_init_ttf_addon();

    global.display = al_create_display(640, 480);
    if (!global.display)
        Utils::fatal_error("Error creating display.\n");
    if (!al_install_keyboard())
        Utils::fatal_error("Error installing keyboard.\n");

    global.color_black = al_map_rgba_f(0, 0, 0, 1);
}

void load ()
{
    global.font_splash = al_load_font("data/cosmic.ttf", 40, 0);
    global.bitmap_splash = al_load_bitmap("data/splash.png");

    global.timer = al_install_timer(1.0 / FPS);

    global.queue = al_create_event_queue();
    al_register_event_source(global.queue, al_get_keyboard_event_source());
    al_register_event_source(global.queue, al_get_timer_event_source(global.timer));
    al_register_event_source(global.queue, al_get_display_event_source(global.display));

    al_start_timer(global.timer);

    ResourceLoader res_load;

    res_load.load_bitmap (&global.bitmap_main_menu, "data/mainmenu.png");
    res_load.load_bitmap (&global.bitmap_game, "data/game1_alpha.png");
    for (int i = 0; i < 240; i ++)
        res_load.load_bitmap (&global.bitmap_mm_sel[i], "data/mmsel/0%03d.png", i);
    for (int i = 0; i < N_CHARACTER; i ++)
    {
        res_load.load_bitmap (&global.bitmap_char[i], "data/c%d.png", i);
        res_load.load_bitmap (&global.bitmap_char_big[i], "data/c%dbig.png", i);
    }
    res_load.load_bitmap (&global.bitmap_c1b0[0], "data/c1b0.png");
    res_load.load_bitmap (&global.bitmap_c0b0[0], "data/c0b0.png");
    res_load.load_bitmap (&global.bitmap_sbr[0], "data/s0b0.png");
    for (int i = 0; i < N_CHARACTER; i ++)
        res_load.load_bitmap (&global.bitmap_crd[i], "data/c%drd.png", i);

    res_load.load_bitmap (&global.bitmap_e[0], "data/e0.png");
    res_load.load_bitmap (&global.bitmap_bgd[0], "data/s0d.png");
    res_load.load_bitmap (&global.bitmap_bgc[0], "data/s0c.png");
    res_load.load_bitmap (&global.bitmap_bgb[0], "data/s0b.png");
    res_load.load_bitmap (&global.bitmap_bga[0], "data/s0a.png");

    res_load.load_font (&global.font_menu, "data/cosmic.ttf", 28, 0);
    res_load.load_font (&global.font_menu_title, "data/cosmic.ttf", 40, 0);
    res_load.load_font (&global.font_menu_bigger, "data/cosmic.ttf", 36, 0);
    res_load.load_font (&global.font_game, "data/cosmic.ttf", 15, 0);
    res_load.load_font (&global.font_game_score, "data/cosmic.ttf", 15, 0);

//    res_load.false_load ();
}

void mainmenu ()
{
    MainMenu main_menu;

    main_menu.run ();
}

int main (int argc, char** argv)
{
    parse_options (argc, argv);
    initialize ();
    load ();
    mainmenu ();

    return 0;
}
