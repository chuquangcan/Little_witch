#include "ThreatObjects.h"

ThreatObjects::ThreatObjects()
{
    x_pos=0.0;
    y_pos=0.0;
    x_val=0.0;
    y_val=0.0;

    on_ground=false;
    come_back_time=0;

    frame_=0;
    widF=0;
    heiF=0;

    boder_a = 0;
    boder_b = 0;
    status_type.left = 0;
    status_type.right = 0;
    type_moving = STATIC_THREAT;
    HP = 5;
    is_valid = true;
    is_changel = false;
    is_changer = false;
}

ThreatObjects::~ThreatObjects()
{}

bool ThreatObjects::LoadImg(std::string path, SDL_Renderer* screen, int nums)
{
    bool ret = BaseObject::LoadImg(path,screen);
    if (ret)
    {
        widF = rect_.w/nums;
        heiF = rect_.h;
    }
    return ret;
}

void ThreatObjects::set_clips()
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
    }
}

void ThreatObjects::show(SDL_Renderer* screen)
{
    if (come_back_time == 0 && is_valid)
    {
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        frame_ ++;
        if (type_moving == BOSS_THREAT)
        {
            if (frame_ >= 6)
            {
                frame_ = 0;
            }
        }
        else
        {
            if (frame_ >= 8)
            {
                frame_ = 0;
            }
        }

        SDL_Rect* currentClip = &Rec_frame[frame_];
        SDL_Rect des = {rect_.x, rect_.y, widF, heiF};
        SDL_RenderCopy(screen, objecttxt, currentClip, &des);
    }
}

void ThreatObjects::Moving(Map& map_data)
{
    if (come_back_time == 0 && is_valid)
    {
        x_val = 0;
        y_val += FALL_SPEED_THREAT;
        if (y_val >= THREAT_MAX_FALL_SPEED)
        {
            y_val = THREAT_MAX_FALL_SPEED;
        }

        if (status_type.left == 1)
        {
            x_val -= THREAT_SPEED;
        }
        else if (status_type.right == 1)
        {
            x_val += THREAT_SPEED;
        }
        checktomap(map_data);
    }
    else if(come_back_time>0)
    {
        come_back_time --;
        if (come_back_time == 0)
        { // init threats
            x_val = 0;
            y_val = 0;
            if (x_pos > 90)
            {
                boder_a -= 90;
                boder_b -= 90;
                x_pos -= 90;
            }
            y_pos = 0;
            come_back_time = 0;
            status_type.left = 1;
        }
    }
}

void ThreatObjects::checktomap(Map& map_data)
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
            if ((map_data.tile[y1][x2]!=0 && map_data.tile[y1][x2]!=APPLE) || (map_data.tile[y2][x2]!=0 && map_data.tile[y2][x2]!=APPLE) || map_data.tile[y1+1][x2] == 0 || map_data.tile[y2+1][x2] == 0)
            {
                is_changel = true;
                is_changer = false;
                x_pos = x2*TILE_SIZE_X;
                x_pos -= widF + 1;
                //x_val = 0;
            }
        }
        else if (x_val < 0)
        {
            if ((map_data.tile[y1][x1]!=0 && map_data.tile[y1][x1]!=APPLE) || (map_data.tile[y2][x1]!=0 && map_data.tile[y2][x1]!=APPLE) || map_data.tile[y1+1][x1] == 0 || map_data.tile[y2+1][x1] ==0)
            {
                is_changer = true;
                is_changel = false;
                x_pos = (x1+1)*TILE_SIZE_X;
                //x_val = 0;
            }
        }
    }
    //check va cham doc
    int width_min = widF < TILE_SIZE_X ? widF : TILE_SIZE_X;
    x1 = (x_pos)/TILE_SIZE_X;
    x2 = (x_pos + width_min)/TILE_SIZE_X;

    y1 = (y_pos + y_val)/ TILE_SIZE_Y;
    y2 = (y_pos + y_val + heiF - 1)/TILE_SIZE_Y;
    if (x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if (y_val>0)
        {
            if ((map_data.tile[y2][x1]!=0 && map_data.tile[y2][x1]!=APPLE)|| (map_data.tile[y2][x2]!=0 && map_data.tile[y2][x2]!=APPLE) || type_moving == BOSS_THREAT)
            {
                y_pos = y2*TILE_SIZE_Y;
                y_pos -=(heiF+1);
                y_val = 0;
                on_ground = true;
            }
        }
        else if (y_val<0)
        {
            if ((map_data.tile[y1][x1]!=0 && map_data.tile[y1][x1]!=APPLE)|| (map_data.tile[y1][x2]!=0 && map_data.tile[y1][x2]!=APPLE))
            {
                y_pos = (y1+1)*TILE_SIZE_Y;
                y_val = 0;
            }
        }
    }

    if (is_valid)
    {
        x_pos += x_val;
        y_pos += y_val;
    }

    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos + widF > map_data.max_x)
    {
        x_pos = map_data.max_x - widF - 1;
    }

    if (y_pos > map_data.max_y)
    {
        is_valid = false;
        y_pos = -10;
    }
}

void ThreatObjects::handle_move(SDL_Renderer* screen)
{
    if (type_moving == STATIC_THREAT)
    {
        ;
    }
    else
    {
        if (on_ground == true)
        {
            if (x_pos > boder_b)
            {
                if (type_moving == STATIC_THREAT)
                {
                    status_type.left = 1;
                    status_type.right = 0;
                    LoadImg("PNG//T2_Left.png", screen, 10);
                }
                else if (type_moving == MOVE_THREAT)
                {
                    status_type.left = 1;
                    status_type.right = 0;
                    LoadImg("PNG//T1_Left.png", screen, 10);
                }
                is_changel = false;
            }
            else if (x_pos < boder_a || is_changer)
            {
                if (type_moving == STATIC_THREAT)
                {
                    status_type.left = 1;
                    status_type.right = 0;
                    LoadImg("PNG//T2_Right.png", screen, 10);
                }
                else if (type_moving == MOVE_THREAT)
                {
                    status_type.left = 0;
                    status_type.right = 1;
                    LoadImg("PNG//T1_Right.png", screen, 10);
                }
                is_changer = false;
            }
            if (is_changel)
            {
                status_type.left = 1;
                status_type.right = 0;
                LoadImg("PNG//T1_Left.png", screen, 10);
                is_changel = false;
            }
            else if (is_changer)
            {
                status_type.left = 0;
                status_type.right = 1;
                LoadImg("PNG//T1_Right.png", screen, 10);
                is_changer = false;
            }
        }
        else
        {
            if (status_type.left == 1)
            {
                if (type_moving == STATIC_THREAT)
                {
                    LoadImg("PNG//T2_Left.png", screen, 10);
                }
                else if (type_moving == MOVE_THREAT)
                    LoadImg("PNG//T1_Left.png", screen, 10);
            }
        }
    }
}

void ThreatObjects::initbullet(BulletObject* bullets, SDL_Renderer* screen)
{
        bullets->set_bullet_type(BulletObject::BALL_BULLET);
        bool ret = bullets->LoadImg_Bullet(screen);
        if (ret)
        {
            bullets->set_is_move(true);
            if (status_type.left == 1)
                bullets->set_bullet_dir(BulletObject::DIR_LEFT);
            else if (status_type.right == 1)
                bullets->set_bullet_dir(BulletObject::DIR_RIGHT);
            bullets->SetRect(rect_.x + 5, rect_.y + 18);
            bullets->set_x_val(20);
            Bullets_Of_Threats_List.push_back(bullets);
        }
}
void ThreatObjects::createbullet(SDL_Renderer* screen, const int& x_lim, const int& y_lim)
{
    for (int i=0; i<Bullets_Of_Threats_List.size(); i++)
    {
        BulletObject* bullets = Bullets_Of_Threats_List.at(i);
        if (status_type.left == 1)
            bullets->set_bullet_dir(BulletObject::DIR_LEFT);
        else if (status_type.right == 1)
            bullets->set_bullet_dir(BulletObject::DIR_RIGHT);
        if (bullets!=NULL)
        {
            if (bullets->get_bullet_dir() == BulletObject::DIR_LEFT)
            {

                //bullets->set_bullet_dir(BulletObject::DIR_LEFT);
                if (bullets->get_is_move())
                {
                    int bullet_max = rect_.x - bullets->GetRect().x;
                    if (bullet_max < 500 && bullet_max > -500)
                    {
                        bullets->handlemove(x_lim, y_lim);
                        bullets->Render(screen);
                    }
                    else
                    {
                        bullets->set_is_move(false);
                        bullets->SetRect(rect_.x + 5, rect_.y + 18);
                    }
                }
                else
                {
                    bullets->set_is_move(true);
                    bullets->SetRect(rect_.x + 5, rect_.y + 18);
                }
            }
            else if (bullets->get_bullet_dir() == BulletObject::DIR_RIGHT)
            {
                //bullets->set_bullet_dir(BulletObject::DIR_RIGHT);
                if (bullets->get_is_move())
                {
                    int bullet_max = bullets->GetRect().x - (rect_.x);
                    if (bullet_max < 200 && bullet_max > 0)
                    {
                        bullets->handlemove(x_lim, y_lim);
                        bullets->Render(screen);
                    }
                    else
                    {
                        bullets->set_is_move(false);
                        bullets->SetRect(rect_.x + widF, rect_.y + 18);
                    }
                }
                else
                {
                    bullets->set_is_move(true);
                    bullets->SetRect(rect_.x + 5, rect_.y + 18);
                }
            }
        }
    }
}

void ThreatObjects::render_hp(SDL_Renderer* screen)
{
    SDL_Surface* img = NULL;
    if (is_valid)
    {
        switch (HP)
        {
            case 1:
                img = IMG_Load("PNG//HP_1.png");
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
            case 2:
                img = IMG_Load("PNG//HP_2.png");
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
            case 3:
                img = IMG_Load("PNG//HP_3.png");
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
            case 4:
                img = IMG_Load("PNG//HP_4.png");
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
}


void ThreatObjects::removebullet(int index)
{
    int siz = Bullets_Of_Threats_List.size();
    if (siz > 0 && index < siz)
    {
        BulletObject* bullet = Bullets_Of_Threats_List.at(index);
        if (bullet)
        {
            bullet->set_is_move(false);
        }
    }
}








