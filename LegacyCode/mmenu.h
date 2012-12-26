#ifndef __APOMAKU_MMENU_H
#define __APOMAKU_MMENU_H

class MainMenu
{
    public:

    MainMenu ();
    void run ();

    private:

    int current_item;
    int n_frame;
    void draw_item (int pos, bool is_selected, bool is_enabled);
    void draw_item_background (int pos, bool is_selected, bool is_enabled);
};

#endif
