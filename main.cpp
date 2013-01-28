#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>

#include "resource.h"

ALLEGRO_DISPLAY *display = NULL;

int initialize ()
{
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    
    display = al_create_display(640, 480);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    if (!al_install_keyboard())
        fprintf(stderr, "Error installing keyboard.\n");
    
    apmk_init_resource();
}

void on_finale ()
{
    
    al_rest(10.0);
    
    al_destroy_display(display);
}

int main(int argc, char **argv)
{
    initialize ();
/*    
    ALU_SPRITE* sprite = alu_create_sprite(APMK_RES_PC[0]);
    
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;

    timer = al_create_timer(1.0 / 60.0);
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    al_start_timer(timer);

    int turn = 0;
    
    while (1)
    {
        ALLEGRO_EVENT event;
        
        do
        {
            al_wait_for_event(queue, &event);
            switch (event.type)
            {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    return 1;
                    break;
            }
            
        } while (!al_event_queue_is_empty(queue));

        turn += 5;
        
        if (true)
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            
            al_draw_bitmap(alu_get_bitmap(sprite)
                           , turn % (544 * 2) >= 544? 544*2-1 - turn % (544 * 2) : turn % (544 * 2)
                           , turn % (384 * 2) >= 384? 384*2-1 - turn % (384 * 2) : turn % (384 * 2)
                           , 0);
 
            al_flip_display();
        }
    }
*/
    on_finale ();
    
    return 0;
}
