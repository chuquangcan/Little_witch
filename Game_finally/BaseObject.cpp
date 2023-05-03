#include "BaseObject.h"

BaseObject::BaseObject()
{
    objecttxt = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    Free();
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL)
    {
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    objecttxt = new_texture;
    return (objecttxt != NULL);
}

void BaseObject::Render(SDL_Renderer* screen)
{
    SDL_RenderCopy(screen, objecttxt, NULL, &rect_);
}

void BaseObject::Free()
{
    SDL_DestroyTexture(objecttxt);
    objecttxt = NULL;
    rect_.w = rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}
