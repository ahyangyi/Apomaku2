#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "global.h"
#include "utils.h"
#include "game.h"
#include "pbullet.h"
#include "ebullet.h"
#include "enemy.h"
#include <cmath>
#include <cstdio>

double HI_SPEED[N_CHARACTER] = {
        5.0, 5.0, 4.0, 6.0, 4.0, 4.5, 3.5, 6.0
        };
double LOW_SPEED[N_CHARACTER] = {
        3.0, 2.0, 1.0, 3.0, 2.0, 2.0, 1.5, 2.0
        };

Game::Game (CharacterID _character) : paused(false), n_frame(0), d_frame(0)
{
    gamedata.character = _character;
    gamedata.cur_pos = Position ();
    for (int i = 0; i < FPS; i ++)
        global.time_previous[i] = al_current_time () - 1.0 + (i + 1) / (double) FPS;
    gamedata.n_pbullet = 0;
    gamedata.n_ebullet = 0;
    gamedata.n_enemy = 0;

    gamedata.power = 0;
    gamedata.hp = HP_PER_LIFE * 3;
    gamedata.graze = 0;

    gamedata.fl_shooting = false;
    gamedata.fl_invincible = true;
    gamedata.invincible_count = INVINCIBLE_TIME;
}

void Game::time_walk ()
{
    bool k_shift, k_z, k_x, k_c;
    int dx, dy;

    ALLEGRO_KEYBOARD_STATE kbd_state;

    al_get_keyboard_state(&kbd_state);

    k_shift = al_key_down(&kbd_state, ALLEGRO_KEY_LSHIFT);
    k_z = al_key_down(&kbd_state, ALLEGRO_KEY_Z);
    k_x = al_key_down(&kbd_state, ALLEGRO_KEY_X);
    k_c = al_key_down(&kbd_state, ALLEGRO_KEY_C);
    dx = al_key_down(&kbd_state, ALLEGRO_KEY_RIGHT) - al_key_down(&kbd_state, ALLEGRO_KEY_LEFT);
    dy = al_key_down(&kbd_state, ALLEGRO_KEY_DOWN) - al_key_down(&kbd_state, ALLEGRO_KEY_UP);

    gamedata.cur_pos +=
        Position::direction(dx, dy) * (0.625 * ((k_shift? LOW_SPEED[gamedata.character] : HI_SPEED[gamedata.character]) + 2.0));
    if (gamedata.cur_pos.x < 16)
        gamedata.cur_pos.x = 16;
    if (gamedata.cur_pos.x > GAME_W - 16)
        gamedata.cur_pos.x = GAME_W - 16;
    if (gamedata.cur_pos.y < 16)
        gamedata.cur_pos.y = 16;
    if (gamedata.cur_pos.y > GAME_H - 16)
        gamedata.cur_pos.y = GAME_H - 16;

    {
        int n_neo = 0;
        for (int i = 0; i < gamedata.n_ebullet; i ++)
        {
            gamedata.ebullet[i] -> time_walk (gamedata.cur_pos);
            if (gamedata.ebullet[i] -> graze (gamedata.cur_pos))
                gamedata.graze ++;
            bool remove = false;
            if (gamedata.ebullet[i] -> collision (gamedata.cur_pos))
            {
                remove = true;
                if (gamedata.fl_invincible)
                    ;
                else
                {
                    gamedata.hp -= HP_PER_LIFE;
                    gamedata.cur_pos = Position ();
                    gamedata.fl_invincible = true;
                    gamedata.invincible_count = INVINCIBLE_TIME;
                }
            }
            if (remove || gamedata.ebullet[i] -> dead ())
                delete gamedata.ebullet[i];
            else
            {
                gamedata.ebullet[n_neo] = gamedata.ebullet[i];
                n_neo ++;
            }
        }
        gamedata.n_ebullet = n_neo;
    }

    {
        int n_neo = 0;
        for (int i = 0; i < gamedata.n_pbullet; i ++)
        {
            gamedata.pbullet[i] -> time_walk ();
            if (gamedata.pbullet[i] -> dead ())
                delete gamedata.pbullet[i];
            else
            {
                gamedata.pbullet[n_neo] = gamedata.pbullet[i];
                n_neo ++;
            }
        }
        gamedata.n_pbullet = n_neo;
    }

    {
        int n_neo = 0;
        for (int i = 0; i < gamedata.n_enemy; i ++)
        {
            gamedata.enemy[i] -> time_walk ();
            if (gamedata.enemy[i] -> dead ())
                delete gamedata.enemy[i];
            else
            {
                gamedata.enemy[n_neo] = gamedata.enemy[i];
                n_neo ++;
            }
        }
        gamedata.n_enemy = n_neo;
    }

/*
    {
        int n_neo = 0;
        for (int i = 0; i < gamedata.n_enemy; i ++)
        {
            gamedata.enemy[i] -> time_walk (gamedata.cur_pos);
            if (gamedata.enemy[i] -> dead ())
                delete gamedata.enemy[i];
            else
            {
                gamedata.enemy[n_neo] = gamedata.enemy[i];
                n_neo ++;
            }
        }
        gamedata.n_enemy = n_neo;
    }
*/

    if (k_z && !gamedata.fl_shooting)
    {
        gamedata.fl_shooting = true;
        gamedata.shootframe = 0;
    }

    if (n_frame % 6 == 0)
    {
        Position start = Position(GAME_W / 2, - 16);
        Position direction = (Position(GAME_W / 2 * 1.10 * sin(n_frame / (double)FPS) + GAME_W / 2, GAME_H) - start) % 150;
        gamedata.ebullet[gamedata.n_ebullet ++] = new EBLinear(global.bitmap_sbr, 8, 5, start, direction);

        {
            direction = (gamedata.cur_pos - start) % 150;
            gamedata.ebullet[gamedata.n_ebullet ++] = new EBLinear(global.bitmap_sbr, 8, 5, start, direction);
        }

        if (n_frame % 30 == 0)
        {
            for (int x = 0; x < GAME_W + 1; x += GAME_W / 4)
            {
                start = Position(x, - 16);
                direction = (Position(- GAME_W / 2 * 1.35 * sin(n_frame / (double)FPS) + GAME_W / 2, GAME_H) - start) % 150;
                gamedata.ebullet[gamedata.n_ebullet ++] = new EBLinear(global.bitmap_sbr, 8, 5, start, direction);
            }
        }

        if (n_frame % 30 == 0)
        {
            LinearTrace trace;

            trace.add (Position (-10, 100), 0);
            trace.add (Position (394, 200), 180);
            gamedata.enemy[gamedata.n_enemy ++] = new EnemyGlobal1 (&trace);
        }
    }

    if (gamedata.fl_shooting)
    {
        if (gamedata.character == CHAR_SIMPLETON)
        {
            if (gamedata.shootframe % 3 == 0)
            {
                gamedata.pbullet[gamedata.n_pbullet ++] = new PB00(gamedata.cur_pos + Position(8, -8), 0);
                gamedata.pbullet[gamedata.n_pbullet ++] = new PB00(gamedata.cur_pos + Position(-8, -8), 0);
            }
        }
        else if (gamedata.character == CHAR_FIRE)
        {
            if (gamedata.shootframe % 3 == 0)
            {
                gamedata.pbullet[gamedata.n_pbullet ++] = new PB10(gamedata.cur_pos + Position(8, -8), 0);
                gamedata.pbullet[gamedata.n_pbullet ++] = new PB10(gamedata.cur_pos + Position(-8, -8), 0);
            }
        }

        gamedata.shootframe ++;
        if (gamedata.shootframe == 15)
        {
            gamedata.shootframe = 0;
            gamedata.fl_shooting = false;
        }
    }

    if (gamedata.fl_invincible)
    {
        if (gamedata.invincible_count == 0)
            gamedata.fl_invincible = false;
        else
            gamedata.invincible_count --;
    }

    n_frame ++;
}

void Game::run ()
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

                    if (!paused)
                        time_walk ();
                    break;
                case ALLEGRO_EVENT_KEY_DOWN:
                case ALLEGRO_EVENT_KEY_REPEAT:
                    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                        paused = !paused;
            };
        } while (!al_event_queue_is_empty(global.queue));

        if (to_paint)
        {
            al_clear_to_color(global.color_black);

            al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(1.0, 1.0, 1.0, 0.3));
            al_draw_bitmap(global.bitmap_bga[0], GAME_X1, n_frame - al_get_bitmap_height(global.bitmap_bgd[0]) - al_get_bitmap_height(global.bitmap_bgc[0]) - al_get_bitmap_height(global.bitmap_bgb[0]) - al_get_bitmap_height(global.bitmap_bga[0]) + GAME_H, 0);
            al_draw_bitmap(global.bitmap_bgb[0], GAME_X1, n_frame - al_get_bitmap_height(global.bitmap_bgd[0]) - al_get_bitmap_height(global.bitmap_bgc[0]) - al_get_bitmap_height(global.bitmap_bgb[0]) + GAME_H, 0);
            al_draw_bitmap(global.bitmap_bgc[0], GAME_X1, n_frame - al_get_bitmap_height(global.bitmap_bgd[0]) - al_get_bitmap_height(global.bitmap_bgc[0]) + GAME_H, 0);
            al_draw_bitmap(global.bitmap_bgd[0], GAME_X1, n_frame - al_get_bitmap_height(global.bitmap_bgd[0]) + GAME_H, 0);

            if (gamedata.fl_invincible && n_frame % 6 < 3)
            {
                al_set_blender(ALLEGRO_ALPHA, ALLEGRO_ONE, al_map_rgba_f(0.0, 0.0, 1.0, 1.0));
                al_draw_bitmap(GAME_POS_C(gamedata.cur_pos, global.bitmap_char[gamedata.character]), 0);
                al_draw_bitmap(GAME_POS_C(gamedata.cur_pos, global.bitmap_char[gamedata.character]), 0);
                al_draw_bitmap(GAME_POS_C(gamedata.cur_pos, global.bitmap_char[gamedata.character]), 0);
            }
            else
            {
/*
                if (gamedata.character == CHAR_SILK)
                {
                    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_ONE, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));
                    al_draw_bitmap(GAME_POS_C(gamedata.cur_pos, global.bitmap_char[gamedata.character]), 0);
                    al_draw_bitmap(GAME_POS_C(gamedata.cur_pos, global.bitmap_char[gamedata.character]), 0);
                }
                else
*/
                {
                    al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));
                    al_draw_bitmap(GAME_POS_C(gamedata.cur_pos, global.bitmap_char[gamedata.character]), 0);
                }
            }

            al_set_blender(ALLEGRO_ALPHA, ALLEGRO_ONE, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));
            al_draw_bitmap(GAME_POS_C(gamedata.cur_pos, global.bitmap_crd[gamedata.character]), 0);

            al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));

            for (int i = 0; i < gamedata.n_pbullet; i ++)
                gamedata.pbullet[i] -> draw ();
            for (int i = 0; i < gamedata.n_ebullet; i ++)
                gamedata.ebullet[i] -> draw ();
            for (int i = 0; i < gamedata.n_enemy; i ++)
                gamedata.enemy[i] -> draw ();

            al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(1.0, 1.0, 1.0, 1.0));
            al_draw_bitmap(global.bitmap_game, 1, 1, 0);

            al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba_f(0.7, 0.7, 1.0, 0.9));
            al_draw_textf(global.font_game, GAME_X2 + 20, GAME_Y1 + 50, ALLEGRO_ALIGN_LEFT, "HISCORE");
            al_draw_textf(global.font_game_score, SCREEN_W - 20, GAME_Y1 + 50, ALLEGRO_ALIGN_RIGHT, "0");
            al_draw_textf(global.font_game, GAME_X2 + 20, GAME_Y1 + 75, ALLEGRO_ALIGN_LEFT, "SCORE");
            al_draw_textf(global.font_game_score, SCREEN_W - 20, GAME_Y1 + 75, ALLEGRO_ALIGN_RIGHT, "0");

            al_draw_textf(global.font_game, GAME_X2 + 20, GAME_Y1 + 110, ALLEGRO_ALIGN_LEFT, "Life");
            {
                char buf[128];

                int tmp = 0, bp = 0;
                while (tmp + HP_PER_LIFE <= gamedata.hp)
                {
                    buf[bp ++] = '@';
                    tmp += HP_PER_LIFE;
                }
                while (tmp + 1 <= gamedata.hp)
                {
                    buf[bp ++] = '.';
                    tmp += HP_PER_LIFE;
                }
                buf[bp] = 0;
                al_draw_textf(global.font_game_score, GAME_X2 + 90, GAME_Y1 + 110, ALLEGRO_ALIGN_LEFT, buf);
            }
            al_draw_textf(global.font_game, GAME_X2 + 20, GAME_Y1 + 135, ALLEGRO_ALIGN_LEFT, "Power");
            al_draw_textf(global.font_game_score, GAME_X2 + 90, GAME_Y1 + 135, ALLEGRO_ALIGN_LEFT, "%d.%02d \\ 5.00", gamedata.power / 100, gamedata.power % 100);
            al_draw_textf(global.font_game, GAME_X2 + 20, GAME_Y1 + 160, ALLEGRO_ALIGN_LEFT, "Skill");
            al_draw_textf(global.font_game_score, GAME_X2 + 90, GAME_Y1 + 160, ALLEGRO_ALIGN_LEFT, "17234 \\ 1500");

            al_draw_textf(global.font_game, GAME_X2 + 20, GAME_Y1 + 195, ALLEGRO_ALIGN_LEFT, "Point");
            al_draw_textf(global.font_game_score, GAME_X2 + 90, GAME_Y1 + 195, ALLEGRO_ALIGN_LEFT, "20000");
            al_draw_textf(global.font_game, GAME_X2 + 20, GAME_Y1 + 220, ALLEGRO_ALIGN_LEFT, "Graze");
            al_draw_textf(global.font_game_score, GAME_X2 + 90, GAME_Y1 + 220, ALLEGRO_ALIGN_LEFT, "%d", gamedata.graze);

            {
                char buf[128];
                sprintf(buf, "%2.2lf", global.calculated_fps);
                al_draw_textf(global.font_game_score, SCREEN_W, SCREEN_H - 20, ALLEGRO_ALIGN_RIGHT, buf);
            }

            {
                double cur_time = al_current_time ();
                global.calculated_fps = FPS / (cur_time - global.time_previous[d_frame % FPS]);
                global.time_previous[d_frame % FPS] = cur_time;

                d_frame ++;
            }

            al_flip_display();
            to_paint = false;
        }
    }
}
