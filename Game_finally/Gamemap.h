#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "commonFunc.h"
#include "BaseObject.h"

class Tilemap : public BaseObject
{
    public:
        Tilemap(){;}
        virtual ~Tilemap(){;}
};

class Gamemap
{
    public:
        Gamemap(){;}
        ~Gamemap(){;}

        void LoadMap(char* name);
        void LoadTile(SDL_Renderer* screen);
        void DrawMap(SDL_Renderer* screen);
        Map getmap(){return game_map;}
        void SetMap(Map& map_data)
        {
            game_map = map_data;
        }
        Tilemap gettilemap(){return tile_map[50];}
    private:
        Map game_map;
        Tilemap tile_map[50];
};

#endif // GAMEMAP_H
