#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val = 0;
    y_val = 0;
    is_move = false;
    bullet_type = BALL_BULLET;
    bullet_direction = DIR_LEFT;
}

BulletObject::~BulletObject()
{
    //dtor
}

bool BulletObject::LoadImg_Bullet(SDL_Renderer* screen)
{
    bool ret=false;
    if (bullet_type == BALL_BULLET)
    {
        ret=LoadImg("PNG//Ball_Bullet.png", screen);
    }
    else if (bullet_type == LASER_BULLET)
    {
        ret=LoadImg("PNG//Laser_Bullet.png", screen);
    }
    else
    {
        ret=LoadImg("PNG//Ball_Vip.png", screen);
    }
    return ret;
}

void BulletObject::handlemove(const float& x_border, const float& y_border)
{
    if (bullet_direction == DIR_RIGHT)
    {
        rect_.x += x_val;
        if (rect_.x>x_border)
        {
            is_move = false;
        }
    }
    else if (bullet_direction == DIR_LEFT)
    {
        rect_.x -= x_val;
        if (rect_.x<0)
        {
            is_move = false;
        }
    }
}
