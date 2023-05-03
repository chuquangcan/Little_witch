#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include <vector>
#include "commonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ThreatObjects.h"

#define gravity 5
#define MAX_FALL_SPEED 6
#define PLAYER_SPEED 5
#define JUMP_VAL 18

class MainObject : public BaseObject
{
    public:
        MainObject();
        virtual ~MainObject();

        enum WalkType {walk_right = 0, walk_left = 1};

        virtual bool LoadImg(std::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* screen);
        void HandleAction(SDL_Event events, SDL_Renderer* screen);
        void setclips();
        void conditionplayer(Map& map_data);
        void Check_collision_map(Map& map_data);
        void SetMapXY(const int mapx, const int mapy)
        {
            map_x = mapx;
            map_y = mapy;
        }
        void CenterOnMap(Map& map_data);
        void update_player (SDL_Renderer* screen);
        void setupbullet(std::vector<BulletObject*> bullets)
        {
            player_bullets = bullets;
        }
        std::vector<BulletObject*> get_bullet() {return player_bullets;}
        void handlebullet(SDL_Renderer* screen);
        void removebullet(const int& index);
        int get_type_bullet() {return checkbullet;}
        void set_HP(int val){HP = HP - val;}
        int get_HP(){return HP;}
        void render_HP(SDL_Renderer* screen);
        int get_width_frame() {return width_frame;}
        int get_heigh_frame() {return height_frame;}
        float get_x_val() {return x_val;}
        float get_y_val() {return y_val;}
        float get_x_pos() {return x_pos;}

    private:
        int bullet_count;
        std::vector<BulletObject*> player_bullets;
        // vi tri
        float x_val;
        float y_val;
        // vi tri hien tai
        float x_pos;
        float y_pos;
        // kich thuoc cua frame
        int width_frame;
        int height_frame;
        // rect cua frame
        SDL_Rect Rec_frame[12];
        // kieu trang thai
        Status status_type;
        // chi so frame
        int frame_id;
        // trang thai trai || phai
        int status;
        bool on_ground;
        int map_x;
        int map_y;
        bool checkmoving;
        int come_back_time;
        int checkbullet;
        int sandcheck;
        int check_firing;
        int HP;
};

#endif // MAINOBJECT_H
