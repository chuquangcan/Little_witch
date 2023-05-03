#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "commonFunc.h"

class BaseObject
{
    public:
        BaseObject();
        ~BaseObject();

        void SetRect(const int& x, const int& y){rect_.x = x; rect_.y = y;}
        SDL_Rect GetRect() const {return rect_;}
        SDL_Texture* GetObject() const {return objecttxt;}

        bool LoadImg(std::string path, SDL_Renderer* screen);
        void Render(SDL_Renderer* screen);
        void Free();
    protected:
        SDL_Texture* objecttxt;
        SDL_Rect rect_;

};

#endif // BASEOBJECT_H
