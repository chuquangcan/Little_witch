#include "BaseObject.h"
#ifndef GHOST_HOUSE_H
#define GHOST_HOUSE_H


class ghost_house : public BaseObject
{
    public:
        ghost_house();
        ~ghost_house();
        bool LoadIMG(std::string path, SDL_Renderer* screen);
        void set_clip();
        void show(SDL_Renderer* screen);
        void set_pos (int x, int y)
        {
            x_pos=x;
            y_pos=y;
        }
        int get_x_pos() {return x_pos;};
        int get_y_pos() {return y_pos;};

        void set_is_valid (bool x)
        {
            is_valid = x;
        }
        bool get_is_valid ()
        {
            return is_valid;
        }
    private:
        int x_pos;
        int y_pos;
        int wid;
        int hei;
        SDL_Rect frame[13];
        int frameid;
        bool is_valid;
};

#endif // GHOST_HOUSE_H
