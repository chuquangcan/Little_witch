#include "BaseObject.h"
#include <string>
#ifndef BIRD_H
#define BIRD_H


class bird : public BaseObject
{
    public:
        bird();
        ~bird();
        void set_x_pos (int x)
        {
            x_pos = x;
        }
        void set_y_pos (int y)
        {
            y_pos = y;
        }
        bool LoadIMG(std::string path, SDL_Renderer* screen);
        void set_clip();
        void show(SDL_Renderer* screen);
    private:
        int x_pos;
        int y_pos;
        int wid;
        int hei;
        SDL_Rect frame[6];
        int frameid;
};

#endif // BIRD_H
