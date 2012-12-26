#ifndef __APOMAKU_GLOBAL_H
#define __APOMAKU_GLOBAL_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "enum.h"
#include "utils.h"

#define FPS 60
#define SCREEN_H 480
#define SCREEN_W 640
#define GAME_H 448
#define GAME_W 384
#define GAME_X1 32
#define GAME_X2 (GAME_X1 + GAME_W)
#define GAME_Y1 16
#define GAME_Y2 (GAME_Y1 + GAME_H)
#define GAME_POS(x,y) (x)+GAME_X1,(y)+GAME_Y1
#define GAME_POS_F(a) GAME_POS(int((a).x),int((a).y))
#define GAME_POS_C(a, b) (b), GAME_POS(int((a).x - al_get_bitmap_width(b)/2.0),int((a).y - al_get_bitmap_height(b)/2.0))
#define GAME_POS_CR(a, b) (b), al_get_bitmap_width(b)/2.0, al_get_bitmap_height(b)/2.0, GAME_POS((a).x,(a).y)

#define GAME_PI (3.1415926535897932384626)

class Global
{
    public:

    // Bitmaps
    ALLEGRO_BITMAP *bitmap_splash;
    ALLEGRO_BITMAP *bitmap_main_menu;
    ALLEGRO_BITMAP *bitmap_game;

    // Bitmap arrays
    ALLEGRO_BITMAP *bitmap_char_big[N_CHARACTER];
    ALLEGRO_BITMAP *bitmap_char[N_CHARACTER];
    ALLEGRO_BITMAP *bitmap_crd[N_CHARACTER];
    ALLEGRO_BITMAP *bitmap_c0b0[1];
    ALLEGRO_BITMAP *bitmap_c1b0[1];
    ALLEGRO_BITMAP *bitmap_sbr[1];
    ALLEGRO_BITMAP *bitmap_bga[1];
    ALLEGRO_BITMAP *bitmap_bgb[1];
    ALLEGRO_BITMAP *bitmap_bgc[1];
    ALLEGRO_BITMAP *bitmap_bgd[1];
    ALLEGRO_BITMAP *bitmap_e[N_COMMON_ENEMY];

    // Soon-to-be clips
    ALLEGRO_BITMAP *bitmap_mm_sel[240];

    // Fonts
    ALLEGRO_FONT *font_splash;
    ALLEGRO_FONT *font_menu;
    ALLEGRO_FONT *font_menu_title;
    ALLEGRO_FONT *font_menu_bigger;
    ALLEGRO_FONT *font_game;
    ALLEGRO_FONT *font_game_score;

    ALLEGRO_COLOR color_black;

    ALLEGRO_TIMER *timer;

    ALLEGRO_DISPLAY *display;

    ALLEGRO_EVENT_QUEUE *queue;

    double time_previous[60], calculated_fps;
};

extern Global global;

#endif

