#include "bird.h"

bird::bird()
{
    x_pos = 0;
    y_pos = 0;
    wid = 0;
    hei = 0;
    frameid = 0;
}

bird::~bird()
{
    //dtor
}

bool bird::LoadIMG(std::string path, SDL_Renderer* screen)
{
    bool res = BaseObject::LoadImg(path, screen);
    if (res)
    {
        wid = rect_.w/6;
        hei = rect_.h;
    }
    return res;
}

void bird::set_clip()
{
    if (wid>0 && hei>0)
    {
        frame[0].x = 0;
        frame[0].y = 0;
        frame[0].w = wid;
        frame[0].h = hei;

        frame[1].x = wid;
        frame[1].y = 0;
        frame[1].w = wid;
        frame[1].h = hei;

        frame[2].x = 2*wid;
        frame[2].y = 0;
        frame[2].w = wid;
        frame[2].h = hei;

        frame[3].x = 3*wid;
        frame[3].y = 0;
        frame[3].w = wid;
        frame[3].h = hei;

        frame[4].x = 4*wid;
        frame[4].y = 0;
        frame[4].w = wid;
        frame[4].h = hei;

        frame[5].x = 5*wid;
        frame[5].y = 0;
        frame[5].w = wid;
        frame[5].h = hei;
    }
}

void bird::show(SDL_Renderer* screen)
{
    bool res = LoadIMG("PNG//walk.png", screen);
    set_clip();
    if (res)
    {
        frameid++;
        if (frameid>=6)
        {
            frameid=0;
        }
        SDL_Rect des = {x_pos, y_pos, wid, hei};
        SDL_Rect *curr = &frame[frameid];
        SDL_RenderCopy(screen, objecttxt, curr, &des);
    }
}
