#include "commonFunc.h"
#include "BaseObject.h"

#ifndef EXPLOSION_H
#define EXPLOSION_H


class explosion:public BaseObject
{
    public:
        explosion();
        bool Load_IMG(std::string path, SDL_Renderer* screen);
        void show(SDL_Renderer* screen, int start_, int end_);
        void set_pos (int x, int y)
        {
            x_pos = x;
            y_pos = y;
        }
        ~explosion();

    private:
        int x_pos;
        int y_pos;
        int wid;
        int hig;
};

#endif // EXPLOSION_H
