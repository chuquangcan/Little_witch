#ifndef THREATOBJECTS_H
#define THREATOBJECTS_H

#include "commonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "MainObject.h"

#define THREAT_FRAME_NUMS 10
#define FALL_SPEED_THREAT 5
#define THREAT_MAX_FALL_SPEED 6
#define THREAT_SPEED 3

class ThreatObjects : public BaseObject
{
    public:
        ThreatObjects();
        ~ThreatObjects();

        enum TYPEMOVE
        {
            STATIC_THREAT,
            MOVE_THREAT,
            BOSS_THREAT
        };

        void set_x_val(float x)
        {
            x_val = x;
        }
        void set_y_val(float y)
        {
            y_val = y;
        }

        void set_x_pos(float xp)
        {
            x_pos = xp;
        }
        void set_y_pos(float yp)
        {
            y_pos = yp;
        }
        float get_x_pos()
        {
            return x_pos;
        }
        float get_y_pos()
        {
            return y_pos;
        }
        void setmapxy(const int& mp_x, const int& mp_y)
        {
            map_x = mp_x;
            map_y = mp_y;
        }
        void set_clips();
        bool LoadImg(std::string path, SDL_Renderer* screen, int nums);
        void show(SDL_Renderer* screen);
        int get_width_frame()
        {
            return widF;
        }
        int get_height_frame()
        {
            return heiF;
        }
        void Moving(Map& map_data);
        void checktomap(Map& map_data);
        void set_type_move(int type)
        {
            type_moving = type;
        }
        int get_type_move()
        {
            return type_moving;
        }
        void set_border_pos(int& a, int& b)
        {
            boder_a = a;
            boder_b = b;
        }
        void set_status_left(int stleft)
        {
            status_type.left = stleft;
        }
        void handle_move(SDL_Renderer* screen);
        std::vector <BulletObject*> get_bullet_list() {return Bullets_Of_Threats_List;}
        void set_bull_list(const std::vector<BulletObject*>& bl_list)
        {
            Bullets_Of_Threats_List = bl_list;
        }
        void initbullet(BulletObject* bullets, SDL_Renderer* screen);
        void createbullet(SDL_Renderer* screen, const int& x_lim, const int& y_lim);
        //bool handle_with_player_bullet(MainObject* player);

        int get_hp() {return HP;}
        void set_hp(int val){HP=HP-val;}
        void render_hp(SDL_Renderer* screen);
        void removebullet(int index);
        void set_status_valid(bool x) {is_valid = x;}
        bool get_status_valid () {return is_valid;}
        void set_up_hp(int val)
        {
            HP=val;
        }

    private:
        int map_x;
        int map_y;

        float x_pos;
        float y_pos;
        float x_val;
        float y_val;

        bool on_ground;
        int come_back_time;

        int frame_;
        int widF;
        int heiF;
        SDL_Rect Rec_frame[THREAT_FRAME_NUMS];

        int type_moving;
        int boder_a;
        int boder_b;
        Status status_type;

        std::vector<BulletObject*> Bullets_Of_Threats_List;

        int HP;

        bool is_valid;
        bool is_changel;
        bool is_changer;
};

#endif // THREATOBJECTS_H
