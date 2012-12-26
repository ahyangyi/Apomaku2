#ifndef __APOMAKU_MOVIE_H
#define __APOMAKU_MOVIE_H
#include <allegro5/allegro_image.h>

class Movie
{
    public:
        Movie ();
        virtual void time_walk () = 0;
        virtual void time_walk (int steps) = 0;
        virtual void reset () = 0;
        virtual void jump (int action) = 0;
        virtual ALLEGRO_BITMAP * get_content () = 0;
};

class SingleFrameMovie : public Movie
{
    public:
        SingleFrameMovie (const char* filename);
        void time_walk ();
        void time_walk (int steps);
        void reset ();
        void jump (int action);
        ALLEGRO_BITMAP * get_content ();
    protected:
        ALLEGRO_BITMAP * bitmap;
};

class ConfiguredMovie : public Movie
{
    public:
        ConfiguredMovie (const char* filename);
        void time_walk ();
        void time_walk (int steps);
        void reset ();
        void jump (int _action);
        ALLEGRO_BITMAP * get_content ();
    protected:
        int action, n_frame;
        ALLEGRO_BITMAP ** bitmaps;
        int* entry_list;
        int* entry_label;
        int* entry_length;
        int* entry_jump;
};

#endif
