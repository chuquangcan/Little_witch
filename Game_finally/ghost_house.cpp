#include "ghost_house.h"

ghost_house::ghost_house()
{
    x_pos = 0;
    y_pos = 0;
    wid=0;
    hei=0;
    frameid = 0;
    is_valid = true;
}

ghost_house::~ghost_house()
{
    //dtor
}

bool ghost_house::LoadIMG (std::string path, SDL_Renderer* screen)
{
    bool res = BaseObject::LoadImg(path, screen);
    if (res)
    {
        wid = rect_.w/13;
        hei = rect_.h;
    }
    return res;
}

void ghost_house::set_clip()
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

        frame[6].x = 6*wid;
        frame[6].y = 0;
        frame[6].w = wid;
        frame[6].h = hei;

        frame[7].x = 7*wid;
        frame[7].y = 0;
        frame[7].w = wid;
        frame[7].h = hei;

        frame[8].x = 8*wid;
        frame[8].y = 0;
        frame[8].w = wid;
        frame[8].h = hei;

        frame[9].x = 9*wid;
        frame[9].y = 0;
        frame[9].w = wid;
        frame[9].h = hei;

        frame[10].x = 10*wid;
        frame[10].y = 0;
        frame[10].w = wid;
        frame[10].h = hei;

        frame[11].x = 11*wid;
        frame[11].y = 0;
        frame[11].w = wid;
        frame[11].h = hei;

        frame[12].x = 12*wid;
        frame[12].y = 0;
        frame[12].w = wid;
        frame[12].h = hei;

    }
}

void ghost_house::show(SDL_Renderer* screen)
{
    if (is_valid)
    {
        bool res = LoadIMG("PNG//ghost_house_is.png", screen);
        set_clip();
        if (res)
        {
            frameid++;
            if (frameid>=13)
            {
                frameid=0;
            }
            SDL_Rect des = {x_pos, y_pos, wid, hei};
            SDL_Rect *curr = &frame[frameid];
            SDL_RenderCopy(screen, objecttxt, curr, &des);
            //SDL_RenderPresent(screen);
        }
    }
    else
    {
        bool res = LoadIMG("PNG//ghost_house_s.png", screen);
        set_clip();
        if (res)
        {
            frameid++;
            if (frameid>=13)
            {
                frameid=0;
            }
            SDL_Rect des = {x_pos, y_pos, wid, hei};
            SDL_Rect *curr = &frame[frameid];
            SDL_RenderCopy(screen, objecttxt, curr, &des);
            //SDL_RenderPresent(screen);
        }
    }
}
