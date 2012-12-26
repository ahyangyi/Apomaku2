#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "utils.h"
#include "global.h"
#include "charsel.h"

CharacterSelection::CharacterSelection () : n_frame(0)
{
    character = CHAR_SIMPLETON;
}

void __character_intro_1 ();
void __character_intro_2 ();
void __character_intro_3 ();
void __character_intro_4 ();
void __character_intro_5 ();
void __character_intro_6 ();
void __character_intro_7 ();
void __character_intro_8 ();
void placeholder () {}

typedef void (*CharacterIntroductionFunction)();
const CharacterIntroductionFunction CHARACTER_INTRO[] =
{
    __character_intro_1,
    __character_intro_2,
    __character_intro_3,
    __character_intro_4,
    __character_intro_5,
    __character_intro_6,
    __character_intro_7,
    __character_intro_8,
};

bool CharacterSelection::run ()
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
                    switch (event.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_ESCAPE:
                        case ALLEGRO_KEY_X:
                            return false;
                        case ALLEGRO_KEY_LEFT:
                            character = (CharacterID)((character + N_CHARACTER - 1) % N_CHARACTER);
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            character = (CharacterID)((character + 1) % N_CHARACTER);
                            break;
                        case ALLEGRO_KEY_ENTER:
                        case ALLEGRO_KEY_Z:
                            return true;
                    }
            };
        } while (!al_event_queue_is_empty(global.queue));
        if (to_paint)
        {
            al_clear_to_color(global.color_black);
            al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(1.0, 1.0, 1.0, 0.3));
            al_draw_bitmap(global.bitmap_char_big[(int)character], 0, 0, 0);
            al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.7, 0.7, 1.0, 0.9));
            al_draw_textf(global.font_menu_title, al_get_display_width() / 2, 20, ALLEGRO_ALIGN_CENTRE, "Character Selection");
            al_draw_textf(global.font_menu_title, 80, 420, ALLEGRO_ALIGN_CENTRE, "[-");
            al_draw_textf(global.font_menu_title, 320, 420, ALLEGRO_ALIGN_CENTRE, "%d\\%d", (int)character + 1, N_NORMAL_CHARACTER);
            al_draw_textf(global.font_menu_title, 560, 420, ALLEGRO_ALIGN_CENTRE, "-]");
            CHARACTER_INTRO[(int)character]();
            al_flip_display();
        }
    }
}

CharacterID CharacterSelection::get_character ()
{
    return character;
}

void __character_intro_1 ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.7, 0.5, 0.4, 0.4));
    al_draw_textf(global.font_menu, 320, 130, ALLEGRO_ALIGN_CENTRE, "Simpleton");
    al_draw_textf(global.font_menu, 130, 180, ALLEGRO_ALIGN_LEFT, "Weapon: Simpleton,s Scatter");
    al_draw_textf(global.font_menu, 130, 210, ALLEGRO_ALIGN_LEFT, "Bomb: Simpleton,s Cloud");
    al_draw_textf(global.font_menu, 130, 240, ALLEGRO_ALIGN_LEFT, "Ability: Simpleton,s Reflection");
    al_draw_textf(global.font_menu, 130, 270, ALLEGRO_ALIGN_LEFT, "Special Ability: Simpleton,s walk");
}

void __character_intro_2 ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.9, 0.6, 0.5, 0.4));
    al_draw_textf(global.font_menu, 320, 130, ALLEGRO_ALIGN_CENTRE, "Hellfire");
    al_draw_textf(global.font_menu, 130, 180, ALLEGRO_ALIGN_LEFT, "Weapon: Hellfire");
    al_draw_textf(global.font_menu, 130, 210, ALLEGRO_ALIGN_LEFT, "Bomb: Hellfire Tide");
    al_draw_textf(global.font_menu, 130, 240, ALLEGRO_ALIGN_LEFT, "Ability: Hellfire Wave");
    al_draw_textf(global.font_menu, 130, 270, ALLEGRO_ALIGN_LEFT, "Special Ability: Annihilation");
}

void __character_intro_3 ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.4, 0.8, 0.9, 0.4));
    al_draw_textf(global.font_menu, 320, 130, ALLEGRO_ALIGN_CENTRE, "Jellyfish");
    al_draw_textf(global.font_menu, 130, 180, ALLEGRO_ALIGN_LEFT, "Weapon: Sapphire Laser");
    al_draw_textf(global.font_menu, 130, 210, ALLEGRO_ALIGN_LEFT, "Bomb: ???");
    al_draw_textf(global.font_menu, 130, 240, ALLEGRO_ALIGN_LEFT, "Ability[fast]: Space Bender");
    al_draw_textf(global.font_menu, 130, 270, ALLEGRO_ALIGN_LEFT, "Ability[slow]: Absolute Zero");
    al_draw_textf(global.font_menu, 130, 300, ALLEGRO_ALIGN_LEFT, "Special Ability: Slow Aura");
}

void __character_intro_4 ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.6, 0.7, 0.9, 0.4));
    al_draw_textf(global.font_menu, 320, 130, ALLEGRO_ALIGN_CENTRE, "Needle");
    al_draw_textf(global.font_menu, 130, 180, ALLEGRO_ALIGN_LEFT, "Weapon: ???");
    al_draw_textf(global.font_menu, 130, 210, ALLEGRO_ALIGN_LEFT, "Bomb: ???");
    al_draw_textf(global.font_menu, 130, 240, ALLEGRO_ALIGN_LEFT, "Ability: Split");
}

void __character_intro_5 ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.8, 0.8, 0.3, 0.4));
    al_draw_textf(global.font_menu, 320, 130, ALLEGRO_ALIGN_CENTRE, "Golem");
    al_draw_textf(global.font_menu, 130, 180, ALLEGRO_ALIGN_LEFT, "Weapon: ???");
    al_draw_textf(global.font_menu, 130, 210, ALLEGRO_ALIGN_LEFT, "Bomb: ???");
    al_draw_textf(global.font_menu, 130, 240, ALLEGRO_ALIGN_LEFT, "Ability: ???");
}

void __character_intro_6 ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.7, 0.6, 0.6, 0.4));
    al_draw_textf(global.font_menu, 320, 130, ALLEGRO_ALIGN_CENTRE, "Evil Eye");
    al_draw_textf(global.font_menu, 130, 180, ALLEGRO_ALIGN_LEFT, "Weapon: ???");
    al_draw_textf(global.font_menu, 130, 210, ALLEGRO_ALIGN_LEFT, "Bomb: ???");
    al_draw_textf(global.font_menu, 130, 240, ALLEGRO_ALIGN_LEFT, "Ability: ???");
}

void __character_intro_7 ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.4, 0.4, 0.8, 0.4));
    al_draw_textf(global.font_menu, 320, 130, ALLEGRO_ALIGN_CENTRE, "Enigma");
    al_draw_textf(global.font_menu, 130, 180, ALLEGRO_ALIGN_LEFT, "Weapon: ???");
    al_draw_textf(global.font_menu, 130, 210, ALLEGRO_ALIGN_LEFT, "Bomb: ???");
    al_draw_textf(global.font_menu, 130, 240, ALLEGRO_ALIGN_LEFT, "Ability: ???");
}

void __character_intro_8 ()
{
    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.4, 0.6, 0.3, 0.4));
    al_draw_textf(global.font_menu, 320, 130, ALLEGRO_ALIGN_CENTRE, "Silk of Nature");
    al_draw_textf(global.font_menu, 130, 180, ALLEGRO_ALIGN_LEFT, "Weapon: ???");
    al_draw_textf(global.font_menu, 130, 210, ALLEGRO_ALIGN_LEFT, "Bomb: ???");
    al_draw_textf(global.font_menu, 130, 240, ALLEGRO_ALIGN_LEFT, "Ability: ???");
}
