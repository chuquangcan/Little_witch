#include "Boss.h"

Boss::Boss()
{
    x_pos=0.0;
    y_pos=0.0;
    x_val=0.0;
    y_val=0.0;

    frame_=0;
    widF=0;
    heiF=0;

    boder_a = 0;
    boder_b = 0;
    status_type.left = 0;
    status_type.right = 0;
    HP = 5;
    is_moving = true;
    is_valid = true;
    attack = false;
}


bool Boss::LoadImg(std::string path, SDL_Renderer* screen, int nums)
{
    bool ret = BaseObject::LoadImg(path,screen);
    if (ret)
    {
        widF = rect_.w/nums;
        heiF = rect_.h;
    }
    return ret;
}

void Boss::set_clips()
{
    if(widF>0 && heiF>0)
    {
        Rec_frame[0].x = 0;
        Rec_frame[0].y = 0;
        Rec_frame[0].w = widF;
        Rec_frame[0].h = heiF;

        Rec_frame[1].x = widF;
        Rec_frame[1].y = 0;
        Rec_frame[1].w = widF;
        Rec_frame[1].h = heiF;

        Rec_frame[2].x = 2*widF;
        Rec_frame[2].y = 0;
        Rec_frame[2].w = widF;
        Rec_frame[2].h = heiF;

        Rec_frame[3].x = 3*widF;
        Rec_frame[3].y = 0;
        Rec_frame[3].w = widF;
        Rec_frame[3].h = heiF;

        Rec_frame[4].x = 4*widF;
        Rec_frame[4].y = 0;
        Rec_frame[4].w = widF;
        Rec_frame[4].h = heiF;

        Rec_frame[5].x = 5*widF;
        Rec_frame[5].y = 0;
        Rec_frame[5].w = widF;
        Rec_frame[5].h = heiF;

        Rec_frame[6].x = 6*widF;
        Rec_frame[6].y = 0;
        Rec_frame[6].w = widF;
        Rec_frame[6].h = heiF;

        Rec_frame[7].x = 7*widF;
        Rec_frame[7].y = 0;
        Rec_frame[7].w = widF;
        Rec_frame[7].h = heiF;

        Rec_frame[8].x = 8*widF;
        Rec_frame[8].y = 0;
        Rec_frame[8].w = widF;
        Rec_frame[8].h = heiF;

        Rec_frame[9].x = 9*widF;
        Rec_frame[9].y = 0;
        Rec_frame[9].w = widF;
        Rec_frame[9].h = heiF;

        Rec_frame[10].x = 10*widF;
        Rec_frame[10].y = 0;
        Rec_frame[10].w = widF;
        Rec_frame[10].h = heiF;
    }
}

void Boss::show(SDL_Renderer* screen)
{
    set_clips();
    rect_.x = x_pos - map_x;
    rect_.y = y_pos - map_y;
    frame_ ++;
    if (attack)
    {
        if (frame_ >= 11)
        {
            frame_ = 0;
        }

        SDL_Rect* currentClip = &Rec_frame[frame_];
        SDL_Rect des = {rect_.x, rect_.y, widF, heiF};
        if (status_type.right == 1)
            SDL_RenderCopyEx(screen, objecttxt, currentClip, &des, 0.0, NULL, SDL_FLIP_HORIZONTAL);
        else
            SDL_RenderCopy(screen, objecttxt, currentClip, &des);
    }
    else
    {
        if (frame_ >= 6)
        {
            frame_ = 0;
        }

        SDL_Rect* currentClip = &Rec_frame[frame_];
        SDL_Rect des = {rect_.x, rect_.y, widF, heiF};
        SDL_RenderCopy(screen, objecttxt, currentClip, &des);
    }
}

void Boss::Moving(Map& map_data)
{
        x_val = 0;
        if (status_type.left == 1 && is_moving)
        {
            x_val -= THREAT_SPEED;
        }
        else if (status_type.right == 1 && is_moving)
        {
            x_val += THREAT_SPEED;
        }
        checktomap(map_data);
}

void Boss::checktomap(Map& map_data)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;
    // check va cham ngang
    int height_min = heiF < TILE_SIZE_Y ? heiF : TILE_SIZE_Y;
    x1 = (x_pos + x_val)/TILE_SIZE_X;
    x2 = (x_pos + x_val + widF - 1)/TILE_SIZE_X;

    y1 = (y_pos + y_val)/TILE_SIZE_Y;
    y2 = (y_pos + height_min - 1)/TILE_SIZE_Y;

    if (x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if (x_val > 0) // di chuyen phai
        {
            if ((map_data.tile[y1][x2]!=0 && map_data.tile[y1][x2]!=APPLE) || (map_data.tile[y2][x2]!=0 && map_data.tile[y2][x2]!=APPLE))
            {
                x_pos = x2*TILE_SIZE_X;
                x_pos -= widF + 1;
                x_val = 0;
            }
        }
        else if (x_val < 0)
        {
            if ((map_data.tile[y1][x1]!=0 && map_data.tile[y1][x1]!=APPLE) || (map_data.tile[y2][x1]!=0 && map_data.tile[y2][x1]!=APPLE))
            {
                x_pos = (x1+1)*TILE_SIZE_X;
                x_val = 0;
            }
        }
    }
    //check va cham doc
//    int width_min = widF < TILE_SIZE_X ? widF : TILE_SIZE_X;
//    x1 = (x_pos)/TILE_SIZE_X;
//    x2 = (x_pos + width_min)/TILE_SIZE_X;
//
//    y1 = (y_pos + y_val)/ TILE_SIZE_Y;
//    y2 = (y_pos + y_val + heiF - 1)/TILE_SIZE_Y;
//    if (x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
//    {
//        if (y_val>0)
//        {
//            if ((map_data.tile[y2][x1]!=0 && map_data.tile[y2][x1]!=APPLE)|| (map_data.tile[y2][x2]!=0 && map_data.tile[y2][x2]!=APPLE) || type_moving == BOSS_THREAT)
//            {
//                y_pos = y2*TILE_SIZE_Y;
//                y_pos -=(heiF+1);
//                y_val = 0;
//                on_ground = true;
//            }
//        }
//        else if (y_val<0)
//        {
//            if ((map_data.tile[y1][x1]!=0 && map_data.tile[y1][x1]!=APPLE)|| (map_data.tile[y1][x2]!=0 && map_data.tile[y1][x2]!=APPLE))
//            {
//                y_pos = (y1+1)*TILE_SIZE_Y;
//                y_val = 0;
//            }
//        }
//    }

    if(is_moving)
        x_pos += x_val;
    //y_pos += y_val;

    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos + widF > map_data.max_x)
    {
        x_pos = map_data.max_x - widF - 1;
    }
}

void Boss::handle_move(SDL_Renderer* screen, float player_x)
{
    if ((x_pos - player_x >= 300.0)||(player_x- x_pos >=500.0))
    {
        attack = false;
        if (x_pos > boder_b)
        {
            status_type.left = 1;
            status_type.right = 0;
            LoadImg("PNG//BOSS.png", screen, 6);
        }
        else if (x_pos < boder_a)
        {
            status_type.left = 0;
            status_type.right = 1;
            LoadImg("PNG//BOSSR.png", screen, 6);
        }
        else
        {
            if (status_type.left == 1)
            {
                LoadImg("PNG//BOSS.png", screen, 6);
            }
        }
    }
    else
    {
        attack = true;
        if (x_pos < player_x)
        {
            is_moving = true;
            status_type.left = 0;
            status_type.right = 1;
            LoadImg("PNG//demon-attackR.png", screen, 11);
        }
        else if (x_pos - player_x >= 10.0)
        {
            is_moving = true;
            status_type.left = 1;
            status_type.right = 0;
            LoadImg("PNG//demon-attackR.png", screen, 11);

        }
        else
        {
            is_moving = false;
            status_type.left = 1;
            status_type.right = 0;
            LoadImg("PNG//demon-attackR.png", screen, 11);
        }
    }
}

void Boss::render_hp(SDL_Renderer* screen)
{
    SDL_Surface* img = NULL;
    switch (HP)
    {
        case 1:
            img = IMG_Load("PNG//HP_1.png");
            if (img!=NULL)
            {
                SDL_Texture* newtxt = SDL_CreateTextureFromSurface(screen, img);
                SDL_FreeSurface(img);
                img = NULL;
                SDL_Rect hprect = {rect_.x, rect_.y - 10, 50, 10};
                SDL_RenderCopy(screen, newtxt, NULL, &hprect);
                SDL_DestroyTexture(newtxt);
                newtxt = NULL;
            }
            break;
        case 2:
            img = IMG_Load("PNG//HP_2.png");
            if (img!=NULL)
            {
                SDL_Texture* newtxt = SDL_CreateTextureFromSurface(screen, img);
                SDL_FreeSurface(img);
                img = NULL;
                SDL_Rect hprect = {rect_.x, rect_.y - 10, 50, 10};
                SDL_RenderCopy(screen, newtxt, NULL, &hprect);
                SDL_DestroyTexture(newtxt);
                newtxt = NULL;
            }
            break;
        case 3:
            img = IMG_Load("PNG//HP_3.png");
            if (img!=NULL)
            {
                SDL_Texture* newtxt = SDL_CreateTextureFromSurface(screen, img);
                SDL_FreeSurface(img);
                img = NULL;
                SDL_Rect hprect = {rect_.x, rect_.y - 10, 50, 10};
                SDL_RenderCopy(screen, newtxt, NULL, &hprect);
                SDL_DestroyTexture(newtxt);
                newtxt = NULL;
            }
            break;
        case 4:
            img = IMG_Load("PNG//HP_4.png");
            if (img!=NULL)
            {
                SDL_Texture* newtxt = SDL_CreateTextureFromSurface(screen, img);
                SDL_FreeSurface(img);
                img = NULL;
                SDL_Rect hprect = {rect_.x, rect_.y - 10, 50, 10};
                SDL_RenderCopy(screen, newtxt, NULL, &hprect);
                SDL_DestroyTexture(newtxt);
                newtxt = NULL;
            }
            break;
        case 5:
            img = IMG_Load("PNG//HP_5.png");
            if (img!=NULL)
            {
                SDL_Texture* newtxt = SDL_CreateTextureFromSurface(screen, img);
                SDL_FreeSurface(img);
                img = NULL;
                SDL_Rect hprect = {rect_.x + 8, rect_.y - 10, 50, 10};
                SDL_RenderCopy(screen, newtxt, NULL, &hprect);
                SDL_DestroyTexture(newtxt);
                newtxt = NULL;
            }
            break;
    }
}




