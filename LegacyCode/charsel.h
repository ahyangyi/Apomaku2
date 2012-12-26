#ifndef __APOMAKU_CHARSEL_H
#define __APOMAKU_CHARSEL_H
#include "enum.h"

class CharacterSelection
{
    public:

    CharacterSelection ();
    bool run ();
    CharacterID get_character ();

    protected:

    int n_frame;
    CharacterID character;
};

#endif
