#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

#include "BaseObject.h"
#include "commonFunc.h"

class BulletObject : public BaseObject
{
    public:
        BulletObject();
        ~BulletObject();

        enum BULLET_DIR
        {
            DIR_LEFT = 20,
            DIR_RIGHT = 30,
        };

        enum BULLET_TYPES
        {
            BALL_BULLET = 50,
            LASER_BULLET = 60,
            BALL_VIP = 70
        };

        void set_x_val(const int& xVal)
        {
            x_val = xVal;
        }
        void set_y_val(const int& yVal)
        {
            y_val = yVal;
        }
        int get_x_val() {return x_val;}
        int get_y_val() {return y_val;}

        void set_is_move(const bool& ismoving)
        {
            is_move = ismoving;
        }
        bool get_is_move() {return is_move;}

        void handlemove(const float& x_border, const float& y_border);

        void set_bullet_dir(int dir)
        {
            bullet_direction = dir;
        }
        int get_bullet_dir() {return bullet_direction;}

        void set_bullet_type(const int& type)
        {
            bullet_type = type;
        }
        int get_bullet_type() {return bullet_type;}
        bool LoadImg_Bullet(SDL_Renderer* screen);

    private:
        int x_val;
        int y_val;
        bool is_move;
        int bullet_direction;
        int bullet_type;
};

#endif // BULLETOBJECT_H
