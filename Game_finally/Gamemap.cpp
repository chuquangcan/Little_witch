#include "Gamemap.h"
#include <fstream>
#include <iostream>
#include <sstream>

void Gamemap::LoadMap(char* name)
{
    std::ifstream fp;
    fp.open(name);
    if (!fp.is_open())
    {
        return;
    }
    game_map.max_x = 0;
    game_map.max_y = 0;
    for (int i=0; i<MAX_MAP_Y; i++)
    {
        for (int j=0; j<MAX_MAP_X; j++)
        {
            int x;
            fp >> x;
            game_map.tile[i][j] = x;

            int val = game_map.tile[i][j];

            if (val>=0)
            {
                if (j>game_map.max_x)
                {
                    game_map.max_x = j;
                }
                if (i>game_map.max_y)
                {
                    game_map.max_y = i;
                }
            }
            //std::cout << game_map.tile[i][j] << " ";
        }
        //std::cout << "\n";

    }

    game_map.max_x = (game_map.max_x+1)*TILE_SIZE_X;
    game_map.max_y = (game_map.max_y+1)*TILE_SIZE_Y;

    game_map.start_x = 0;
    game_map.start_y = 0;

    game_map.file_name = name;
    fp.close();
}

void Gamemap::LoadTile(SDL_Renderer* screen)
{
    for (int i=0; i<50; i++)
    {
        std::stringstream ss;
        ss << "PNG/" << i << ".png";
        tile_map[i].LoadImg(ss.str(), screen);
    }
}

void Gamemap::DrawMap(SDL_Renderer* screen)
{
    int x1=0;
    int x2=0;
    int y1=0;
    int y2=0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map.start_x/TILE_SIZE_X;

    x1 = (game_map.start_x%TILE_SIZE_X)*(-1);
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE_X);

    map_y = game_map.start_y/TILE_SIZE_Y;

    y1 = (game_map.start_y%TILE_SIZE_Y)*(-1);
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE_Y);

    for (int i=y1; i<y2; i+= TILE_SIZE_Y)
    {
        map_x = game_map.start_x/TILE_SIZE_X;
        for (int j=x1; j<x2; j+=TILE_SIZE_X)
        {
            int val = game_map.tile[map_y][map_x];
            if (val>0)
            {
                tile_map[val].SetRect(j, i);
                tile_map[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
