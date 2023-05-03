#include <sstream>
#include "explosion.h"

explosion::explosion()
{
    x_pos = 0;
    y_pos = 0;
    wid = 0;
    hig = 0;
}

explosion::~explosion()
{
    //dtor
}

bool explosion::Load_IMG(std::string path, SDL_Renderer* screen)
{
    bool res = BaseObject::LoadImg(path, screen);
    if (res)
    {
        wid = 168;
        hig = 100;
    }
    return res;
}

void explosion::show(SDL_Renderer* screen, int start_, int end_)
{
    for (int i=start_; i<=end_; i++)
    {
        std::stringstream ss;
        ss << "PNG//ex//";
        ss << i << ".png";
        bool res = Load_IMG(ss.str(), screen);
        std::cout << res << std::endl;
        if (res)
        {
            SDL_Rect des = {x_pos, y_pos, wid, hig};
            SDL_RenderCopy(screen, objecttxt, NULL, &des);
            //SDL_RenderPresent(screen);
        }
    }
}
