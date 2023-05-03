#include "MainObject.h"
#include "ThreatObjects.h"
#include <iostream>

MainObject::MainObject()
{
    frame_id = 0;
    x_pos = 0;
    y_pos = 600;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = 0;
    status_type.left = 0;
    status_type.right = 0;
    status_type.down = 0;
    status_type.up = 0;
    status_type.jump = 0;
    on_ground = false;
    map_x = 0;
    map_y = 0;
    come_back_time = 0;
    checkmoving = false;
    checkbullet = 0;
    bullet_count = 0;
    sandcheck = 5;
    check_firing = 0;
    HP = 20;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject :: LoadImg(path, screen);
    if (ret)
    {
        width_frame = rect_.w / 8;
        height_frame = rect_.h;
    }
    return ret;
}

void MainObject :: setclips()
{
    if (width_frame > 0 && height_frame > 0)
    {
        Rec_frame[0].x = 0;
        Rec_frame[0].y = 0;
        Rec_frame[0].w = width_frame;
        Rec_frame[0].h = height_frame;

        Rec_frame[1].x = width_frame;
        Rec_frame[1].y = 0;
        Rec_frame[1].w = width_frame;
        Rec_frame[1].h = height_frame;

        Rec_frame[2].x = 2*width_frame;
        Rec_frame[2].y = 0;
        Rec_frame[2].w = width_frame;
        Rec_frame[2].h = height_frame;

        Rec_frame[3].x = 3*width_frame;
        Rec_frame[3].y = 0;
        Rec_frame[3].w = width_frame;
        Rec_frame[3].h = height_frame;

        Rec_frame[4].x = 4*width_frame;
        Rec_frame[4].y = 0;
        Rec_frame[4].w = width_frame;
        Rec_frame[4].h = height_frame;

        Rec_frame[5].x = 5*width_frame;
        Rec_frame[5].y = 0;
        Rec_frame[5].w = width_frame;
        Rec_frame[5].h = height_frame;

        Rec_frame[6].x = 6*width_frame;
        Rec_frame[6].y = 0;
        Rec_frame[6].w = width_frame;
        Rec_frame[6].h = height_frame;

        Rec_frame[7].x = 7*width_frame;
        Rec_frame[7].y = 0;
        Rec_frame[7].w = width_frame;
        Rec_frame[7].h = height_frame;

        /*Rec_frame[8].x = 8*width_frame;
        Rec_frame[8].y = 0;
        Rec_frame[8].w = width_frame;
        Rec_frame[8].h = height_frame;

        Rec_frame[9].x = 9*width_frame;
        Rec_frame[9].y = 0;
        Rec_frame[9].w = width_frame;
        Rec_frame[9].h = height_frame;

        Rec_frame[10].x = 10*width_frame;
        Rec_frame[10].y = 0;
        Rec_frame[10].w = width_frame;
        Rec_frame[10].h = height_frame;

        Rec_frame[11].x = 11*width_frame;
        Rec_frame[11].y = 0;
        Rec_frame[11].w = width_frame;
        Rec_frame[11].h = height_frame;*/

    }
}

void MainObject::Show(SDL_Renderer* screen)
{
    update_player(screen);

    if (status_type.left == 1 || status_type.right == 1 || status_type.down == 1)
    {
        frame_id++;
    }
    else
    {
        frame_id = 0;
    }
    if (frame_id >= 8)
    {
        frame_id = 0;
    }
    if (come_back_time == 0)
    {
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;

        SDL_Rect currentrect = Rec_frame[frame_id];

        SDL_Rect rendersquad = {rect_.x, rect_.y, width_frame, height_frame};

        SDL_RenderCopy(screen, objecttxt, &currentrect, &rendersquad);
    }
}

void MainObject::HandleAction(SDL_Event events, SDL_Renderer* screen)
{
    BulletObject* bullet = new BulletObject();
    if (events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_RIGHT:
                status = walk_right;
                status_type.right = 1;
                status_type.left = 0;
                checkmoving = true;
                update_player(screen);
                break;
            case SDLK_LEFT:
                status = walk_left;
                status_type.left = 1;
                status_type.right = 0;
                checkmoving = true;
                update_player(screen);
                break;
            case SDLK_UP:
                status_type.jump = 1;
                update_player(screen);
                break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_RIGHT:
                status_type.right = 0;
                break;
            case SDLK_LEFT:
                status_type.left = 0;
                break;
        }
        checkmoving = false;
        status_type.down = 1;
    }
    else
    {
        checkmoving = false;
        status_type.down = 1;
    }

    if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if (bullet_count > 0)
        {
            bullet_count --;
            checkbullet = 1;
        }
        else
        {
            checkbullet = 0;
        }
        if (events.button.button == SDL_BUTTON_LEFT)
        {
            check_firing = 1;
            bullet->LoadImg_Bullet(screen);
            if(status == walk_right)
            {
                bullet -> set_bullet_dir(BulletObject::DIR_RIGHT);
                if (checkbullet == 0)
                    bullet->set_bullet_type(50);
                else
                    bullet->set_bullet_type(60);
                bullet->LoadImg_Bullet(screen);
                int type = bullet->get_bullet_type();
                if (type == BulletObject::LASER_BULLET)
                    bullet->SetRect(this->rect_.x + width_frame - 35, rect_.y + 14);
                else
                    bullet->SetRect(this->rect_.x + width_frame - 35, rect_.y + 14);
            }
            else
            {
                bullet -> set_bullet_dir(BulletObject::DIR_LEFT);
                if (checkbullet == 0)
                    bullet->set_bullet_type(50);
                else
                    bullet->set_bullet_type(60);
                bullet->LoadImg_Bullet(screen);
                int type = bullet->get_bullet_type();
                if (type == BulletObject::LASER_BULLET)
                    bullet->SetRect(this->rect_.x, rect_.y + 14);
                else
                    bullet->SetRect(this->rect_.x, rect_.y + 14);
            }


            bullet->set_x_val(20);
            bullet->set_is_move(true);

            player_bullets.push_back(bullet);
        }
    }
    else
    {
        check_firing = 0;
    }
}

void MainObject::removebullet(const int& index)
{
    int siz = player_bullets.size();
    if (siz > 0 && index < siz)
    {
        BulletObject* bullet = player_bullets.at(index);
        player_bullets.erase(player_bullets.begin() + index);
        if (bullet)
        {
            delete bullet;
            bullet = NULL;
        }
    }
}


void MainObject::handlebullet(SDL_Renderer* screen)
{
    for (int i=0; i<player_bullets.size(); i++)
    {
        BulletObject* bullet = player_bullets.at(i);
        if (bullet!=NULL)
        {
            if (bullet->get_is_move() == true)
            {
                bullet->handlemove(rect_.x+200, SCREEN_HEIGHT);
                bullet->Render(screen);
            }
            else
            {
                player_bullets.erase(player_bullets.begin()+i);
                if (bullet != NULL)
                {
                    delete bullet;
                    bullet = NULL;
                }
            }
        }
    }
}

void MainObject::conditionplayer(Map& map_data)
{
    if (come_back_time == 0)
    {
        x_val = 0;
        y_val +=0.8;
        if (y_val >= MAX_FALL_SPEED)
        {
            y_val = MAX_FALL_SPEED;
        }

        if (status_type.left == 1)
        {
            x_val -= PLAYER_SPEED;
        }
        else if(status_type.right == 1)
        {
            x_val += PLAYER_SPEED;
        }

        else if(status_type.jump == 1)
        {
            if (on_ground == true)
            {
                y_val = -JUMP_VAL;
                on_ground = false;
            }
            status_type.jump = 0;
        }
        Check_collision_map(map_data);
        CenterOnMap(map_data);
    }
    else
    {
        come_back_time = 0;
        SDL_Delay(1000);
        y_pos = 0;
        x_val = 0;
        y_val = 0;
        x_pos = x_pos - 90;
        on_ground = false;
    }
}

void MainObject::CenterOnMap(Map& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH)/2;
    if (map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if (map_data.start_x + SCREEN_WIDTH > map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }
    if (map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }

    map_data.start_y = y_pos - (SCREEN_HEIGHT)/2;
    if (map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if (map_data.start_y + SCREEN_HEIGHT > map_data.max_y)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
    if (map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
}

void MainObject::Check_collision_map(Map& map_data)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;
    // check va cham ngang
    int height_min = height_frame < TILE_SIZE_Y ? height_frame : TILE_SIZE_Y;
    x1 = (x_pos + x_val)/TILE_SIZE_X;
    x2 = (x_pos + x_val + width_frame - 1)/TILE_SIZE_X;

    y1 = (y_pos + y_val)/TILE_SIZE_Y;
    y2 = (y_pos + height_min - 1)/TILE_SIZE_Y;

    if (x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if (x_val > 0) // di chuyen phai
        {
            if (map_data.tile[y1][x2]==APPLE || map_data.tile[y2][x2]==APPLE )
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                HP++;
                if (HP>20)
                    HP=20;
            }
            if (map_data.tile[y1][x2]==BULLET_CHANCING || map_data.tile[y2][x2]==BULLET_CHANCING)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                bullet_count = bullet_count + 5;
            }

            if (map_data.tile[y1][x2]!=0 || map_data.tile[y2][x2]!=0)
            {
                x_pos = x2*TILE_SIZE_X;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
        }
        else if (x_val < 0)
        {
            if (map_data.tile[y1][x1]==APPLE || map_data.tile[y2][x1]==APPLE )
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                HP++;
                if (HP>20)
                    HP=20;
            }
            if (map_data.tile[y1][x1]==BULLET_CHANCING || map_data.tile[y2][x1]==BULLET_CHANCING)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                bullet_count = bullet_count + 5;
            }

            if (map_data.tile[y1][x1]!=0 || map_data.tile[y2][x1]!=0)
            {
                x_pos = (x1+1)*TILE_SIZE_X;
                x_val = 0;
            }
        }
    }
    //check va cham doc
    int width_min = width_frame < TILE_SIZE_X ? width_frame : TILE_SIZE_X;
    x1 = (x_pos)/TILE_SIZE_X;
    x2 = (x_pos + width_min)/TILE_SIZE_X;

    y1 = (y_pos + y_val)/ TILE_SIZE_Y;
    y2 = (y_pos + y_val + height_frame - 1)/TILE_SIZE_Y;
    if (x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if (y_val>0)
        {
            if (map_data.tile[y2][x1]==APPLE || map_data.tile[y2][x2]==APPLE )
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                HP++;
                if (HP>20)
                    HP=20;
            }

            if (map_data.tile[y2][x1]==BULLET_CHANCING || map_data.tile[y2][x2]==BULLET_CHANCING)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                bullet_count = bullet_count + 5;
            }

            else if (map_data.tile[y2][x1]==SAND || map_data.tile[y2][x2]==SAND )
            {
                sandcheck --;
                if (sandcheck == 0)
                {
                    map_data.tile[y2][x1] = 0;
                    map_data.tile[y2][x2] = 0;
                    sandcheck = 5;
                }
            }

            if (map_data.tile[y2][x1]!=0 || map_data.tile[y2][x2]!=0)
            {
                y_pos = y2*TILE_SIZE_Y;
                y_pos -=(height_frame+1);
                y_val = 0;
                on_ground = true;
            }
        }
        else if (y_val<0)
        {
            if (map_data.tile[y1][x1]==APPLE || map_data.tile[y1][x2]==APPLE )
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y1][x2] = 0;
                HP++;
                if (HP>20)
                    HP=20;
            }

            if (map_data.tile[y1][x1]==BULLET_CHANCING || map_data.tile[y1][x2]==BULLET_CHANCING )
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y1][x2] = 0;
                bullet_count += 5;
            }
            /*else if (map_data.tile[y1][x1]==SAND || map_data.tile[y1][x2]==SAND )
            {
                sandcheck --;
                if (sandcheck == 0)
                {
                    map_data.tile[y1][x1] = 0;
                    map_data.tile[y1][x2] = 0;
                    sandcheck = 5;
                }
            }*/

            if (map_data.tile[y1][x1]!=0 || map_data.tile[y1][x2]!=0)
            {
                y_pos = (y1+1)*TILE_SIZE_Y;
                y_val = 0;
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos + width_frame > map_data.max_x)
    {
        x_pos = map_data.max_x - width_frame - 1;
    }

    if (y_pos > map_data.max_y)
    {
        come_back_time = 1;
        HP=HP-5;
    }
}

void MainObject::update_player(SDL_Renderer* screen)
{
    if (on_ground == true)
    {
        if (status == walk_left)
        {
            if (checkmoving == true)
                LoadImg("PNG/RunLeft.png", screen);
            else
            {
                if (check_firing == 1)
                {
                    LoadImg("PNG/FireLeft.png", screen);
                }
                else
                {
                    LoadImg("PNG/DownLeft.png", screen);
                }
            }

        }
        else if (status == walk_right)
        {
            if (checkmoving == true)
                LoadImg("PNG/RunRight.png", screen);
            else
            {
                if (check_firing == 1)
                {
                    LoadImg("PNG/FireRight.png", screen);
                }
                else
                {
                    LoadImg("PNG/DownRight.png", screen);
                }
            }
        }
    }
    else
    {
        if (status == walk_left)
        {
            LoadImg("PNG/JumpLeft.png", screen);
        }
        else
        {
            LoadImg("PNG/JumpRight.png", screen);
        }
    }
}

void MainObject::render_HP(SDL_Renderer* screen)
{
    SDL_Surface* img = NULL;
    switch (HP)
    {
        case 1:
            img = IMG_Load("PNG/Main/M_HP_1.png");
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
            img = IMG_Load("PNG/Main/M_HP_2.png");
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
            img = IMG_Load("PNG/Main/M_HP_3.png");
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
            img = IMG_Load("PNG/Main/M_HP_4.png");
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
            img = IMG_Load("PNG/Main/M_HP_5.png");
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
        case 6:
            img = IMG_Load("PNG/Main/M_HP_6.png");
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
        case 7:
            img = IMG_Load("PNG/Main/M_HP_7.png");
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
        case 8:
            img = IMG_Load("PNG/Main/M_HP_8.png");
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
        case 9:
            img = IMG_Load("PNG/Main/M_HP_9.png");
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
        case 10:
            img = IMG_Load("PNG/Main/M_HP_10.png");
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
        case 11:
            img = IMG_Load("PNG/Main/M_HP_11.png");
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
        case 12:
            img = IMG_Load("PNG/Main/M_HP_12.png");
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
        case 13:
            img = IMG_Load("PNG/Main/M_HP_13.png");
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
        case 14:
            img = IMG_Load("PNG/Main/M_HP_14.png");
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
        case 15:
            img = IMG_Load("PNG/Main/M_HP_15.png");
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
        case 16:
            img = IMG_Load("PNG/Main/M_HP_16.png");
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
        case 17:
            img = IMG_Load("PNG/Main/M_HP_17.png");
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
        case 18:
            img = IMG_Load("PNG/Main/M_HP_18.png");
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
        case 19:
            img = IMG_Load("PNG/Main/M_HP_19.png");
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
        case 20:
            img = IMG_Load("PNG/Main/M_HP_20.png");
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
        default:
            break;
    }
}

