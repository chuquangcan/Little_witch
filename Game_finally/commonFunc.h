#ifndef COMONFUNC_H
#define COMONFUNC_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FPS = 20;

//Screen
const int SCREEN_WIDTH = 1250;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;

#define TILE_SIZE_X 50
#define TILE_SIZE_Y 50

#define MAX_MAP_X 162
#define MAX_MAP_Y 19

#define APPLE 5
#define BULLET_CHANCING 19
#define SAND 14

typedef struct Status
{
    int left;
    int right;
    int up;
    int down;
    int jump;
};

typedef struct Map
{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

namespace SDL_commonfunction
{
    bool check_collision (const SDL_Rect& obj1, const SDL_Rect& obj2);
}

#endif // COMONFUNC_H
