#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include "utils.h"
#include "global.h"
#include "mmenu.h"
#include "charsel.h"
#include "game.h"

MainMenu::MainMenu () : current_item(0), n_frame(0)
{
}

enum {
    MAINMENU_GAMESTART,
    MAINMENU_PRACTICE_START,
    MAINMENU_REPLAY,
    MAINMENU_OPTIONS,
    MAINMENU_EXIT,
    MAINMENU_N_ITEM
};

const char* MAINMENU_ITEM[] =
{
    "Game Start",
    "Practice Start",
    "Replays",
    "Options",
    "Exit",
};

void MainMenu::draw_item (int pos, bool is_selected, bool is_enabled)
{
    if (is_selected)
        al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.7, 0.7, 1.0, 0.9));
    else
        al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.7, 0.7, 1.0, 0.5));
    al_draw_textf(global.font_menu, al_get_display_width() - 40, al_get_display_height() - 300 + 30 * pos, ALLEGRO_ALIGN_RIGHT, MAINMENU_ITEM[pos]);
}

void MainMenu::draw_item_background (int pos, bool is_selected, bool is_enabled)
{
    if (is_selected)
    {
        al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(1.0, 1.0, 1.0, 0.5));
        al_draw_bitmap(global.bitmap_mm_sel[n_frame % 240], al_get_display_width() - 222, al_get_display_height() - 330 + 30 * pos, 0);
    }
}

void MainMenu::run ()
{
    bool to_paint;
    ALLEGRO_EVENT event;

    while (1)
    {
        do
        {
            al_wait_for_event(global.queue, &event);
            switch (event.type)
            {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    Utils::terminate();
                    break;
                case ALLEGRO_EVENT_TIMER:
                    to_paint = true;
                    n_frame ++;
                    break;
                case ALLEGRO_EVENT_KEY_DOWN:
                case ALLEGRO_EVENT_KEY_REPEAT:
                    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ||
                        event.keyboard.keycode == ALLEGRO_KEY_X)
                    {
                        if (current_item == MAINMENU_N_ITEM - 1)
                            return;
                        else
                            current_item = MAINMENU_N_ITEM - 1;
                    }
                    else if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                    {
                        current_item = (current_item + MAINMENU_N_ITEM - 1) % MAINMENU_N_ITEM;
                    }
                    else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                    {
                        current_item = (current_item + 1) % MAINMENU_N_ITEM;
                    }
                    else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER ||
                        event.keyboard.keycode == ALLEGRO_KEY_Z)
                    {
                        switch (current_item)
                        {
                            case MAINMENU_GAMESTART:
                                {
                                    CharacterSelection cs;

                                    if (!cs.run())
                                        break;

                                    Game game (cs.get_character());

                                    game.run ();
                                }
                                break;
                            case MAINMENU_EXIT:
                                Utils::terminate();
                        }
                    }
            };
        } while (!al_event_queue_is_empty(global.queue));
        if (to_paint)
        {
            al_clear_to_color(global.color_black);
            al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));
            al_draw_bitmap(global.bitmap_main_menu, 0, 0, 0);
            al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.7, 0.7, 1.0, 0.9));
            al_draw_textf(global.font_menu_title, al_get_display_width() - 20, 20, ALLEGRO_ALIGN_RIGHT, "Placeholder");

            for (int i = 0; i < MAINMENU_N_ITEM; i ++)
                draw_item_background (i, i == current_item, false);
            for (int i = 0; i < MAINMENU_N_ITEM; i ++)
                draw_item (i, i == current_item, false);

            al_flip_display();
        }
    }
}
