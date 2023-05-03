#include <iostream>
#include <SDL_ttf.h>
#include <sstream>
#include "BaseObject.h"
#include "commonFunc.h"
#include "Gamemap.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatObjects.h"
#include "explosion.h"
#include "ghost_house.h"
#include "bird.h"
#include "Boss.h"

using namespace std;


std::vector<ThreatObjects*> list_threats;


bool init()
{
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        return false;
    }
    else
    {
        cout << "T\n";
        g_window = SDL_CreateWindow("MaHi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (g_window == NULL)
        {
            return false;
        }
        else
        {
            cout << "T\n";
            g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
            if (g_screen == NULL)
            {
                return false;
            }
            else
            {
                cout << "T\n";
                IMG_Init(IMG_INIT_PNG);
            }
        }
    }
    return true;
}

BaseObject bg;

bool loadbg()
{
    bool ret = bg.LoadImg("PNG//bg.png", g_screen);
    if (ret == false)
    {
        return false;
    }
    cout << "T\n";
    return true;
}

void close()
{
    bg.Free();
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    IMG_Quit();
    SDL_Quit();
}


Boss* create_boss ()
{
    Boss* BOSS = new Boss();
    if (BOSS != NULL)
    {
        BOSS->LoadImg("PNG//BOSS.png", g_screen, 6);
        BOSS->set_clips();
        BOSS->set_x_pos(500.0);
        BOSS->set_y_pos(300.0);

        BOSS->set_status_left(1);
        BOSS->render_hp(g_screen);
    }
    return BOSS;
}

std::vector<ThreatObjects*> creatthreatlist()
{
    ThreatObjects* moving_threats = new ThreatObjects[5];

    for (int i=0; i<5; i++)
    {
            ThreatObjects* p_threat = (moving_threats + i);
            if (p_threat != NULL)
            {
                p_threat->LoadImg("PNG//T1_Left.png", g_screen, 10);
                p_threat->set_clips();
                p_threat->set_type_move(ThreatObjects::MOVE_THREAT);
                p_threat->set_x_pos(150.0+i*300);
                p_threat->set_y_pos(100.0);

                int pos1 = p_threat->get_x_pos()-120;
                int pos2 = p_threat->get_x_pos()+60;
                p_threat->set_border_pos(pos1,pos2);
                p_threat->set_status_left(1);

                BulletObject* p_bullets = new BulletObject();
                p_threat->initbullet(p_bullets, g_screen);
                p_threat->render_hp(g_screen);

                list_threats.push_back(p_threat);
            }
    }

    /*
    ThreatObjects* threats_obj = new ThreatObjects[5];


    for (int i=0; i<5; i++)
    {
        ThreatObjects* threats = (threats_obj + i);
        if (threats != NULL)
        {
            threats->LoadImg("PNG/T1_Left.png", g_screen, 10);
            threats->set_clips();
            threats->set_x_pos(1000.0+i*300.0);
            threats->set_y_pos(250.0);
            threats->set_type_move(ThreatObjects::STATIC_THREAT);
            //threats->set_status_left(1);

            BulletObject* p_bullets = new BulletObject();
            threats->initbullet(p_bullets, g_screen);
            threats->render_hp(g_screen);

            list_threats.push_back(threats);
        }
    }*/
    return list_threats;
}

int main(int argc, char* args[])
{
    int nums_of_house = 0;
    int nums_of_enemy = 0;
    bool is_lose = false;
    TTF_Init();
    SDL_Texture* enemy_txt = NULL;
    TTF_Font* gFont = NULL;
    gFont = TTF_OpenFont( "joystix monospace.otf", 72);
    SDL_Color textColor = { 255, 255, 255 };
    // tao main
    if (!init())
        return -1;
    SDL_Surface* newsurface = NULL;
    newsurface = IMG_Load("PNG//bg01.png");
    SDL_Texture* newtxt = NULL;
    newtxt = SDL_CreateTextureFromSurface(g_screen, newsurface);
    SDL_Rect play_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(g_screen, newtxt, NULL, &play_rect);
    SDL_FreeSurface(newsurface);
    newsurface = NULL;
    SDL_DestroyTexture(newtxt);
    newtxt = NULL;

    newsurface = IMG_Load("PNG//start_button.png");
    newtxt = SDL_CreateTextureFromSurface(g_screen, newsurface);
    play_rect = {500, 200, 238, 100};
    SDL_RenderCopy(g_screen, newtxt, NULL, &play_rect);

    SDL_FreeSurface(newsurface);
    newsurface = NULL;
    SDL_DestroyTexture(newtxt);
    newtxt = NULL;

    SDL_Surface* newsurfaceguide;
    newsurfaceguide = IMG_Load("PNG//guide_button_1.png");
    SDL_Texture* newtxtguide;
    newtxtguide = SDL_CreateTextureFromSurface(g_screen, newsurfaceguide);
    SDL_Rect guide_rect = {500, 325, 238, 100};
    SDL_RenderCopy(g_screen, newtxtguide, NULL, &guide_rect);

    SDL_FreeSurface(newsurfaceguide);
    newsurfaceguide = NULL;
    SDL_DestroyTexture(newtxtguide);
    newtxtguide = NULL;

    SDL_Surface* newsurfaceexit;
    newsurfaceexit = IMG_Load("PNG//start_exit.png");
    SDL_Texture* newtxtexit;
    newtxtexit = SDL_CreateTextureFromSurface(g_screen, newsurfaceexit);
    SDL_Rect exit_rect = {500, 450, 238, 100};
    SDL_RenderCopy(g_screen, newtxtexit, NULL, &exit_rect);

    SDL_FreeSurface(newsurfaceexit);
    newsurfaceexit = NULL;
    SDL_DestroyTexture(newtxtexit);
    newtxtexit = NULL;

    bool quit_game = false, running_game = false, guide_running = false;

    SDL_RenderPresent(g_screen);
    while(!quit_game && !running_game && !guide_running)
    {
        while(SDL_PollEvent(&g_event)!=0)
        {
            if (g_event.type == SDL_QUIT)
                {
                    quit_game = true;
                    return 0;
                }
                SDL_Rect mouse_rect;
                int x, y;
                SDL_GetMouseState(&x, &y);
                mouse_rect = {x, y, 1, 1};
                bool check_collisions_play = SDL_commonfunction::check_collision(play_rect, mouse_rect);
                bool check_collisions_exit = SDL_commonfunction::check_collision(exit_rect, mouse_rect);
                bool check_collisions_guide = SDL_commonfunction::check_collision(guide_rect, mouse_rect);
                SDL_RenderClear(g_screen);

                newsurface = IMG_Load("PNG//bg01.png");
                newtxt = SDL_CreateTextureFromSurface(g_screen, newsurface);
                SDL_RenderCopy(g_screen, newtxt, NULL, NULL);

                SDL_FreeSurface(newsurface);
                SDL_DestroyTexture(newtxt);
                newsurface = NULL;
                newtxt = NULL;

            if (check_collisions_play)
                {
                    newsurface = IMG_Load("PNG//motion_button.png");
                    newtxt = SDL_CreateTextureFromSurface(g_screen, newsurface);
                    SDL_RenderCopy(g_screen, newtxt, NULL, &play_rect);

                    SDL_FreeSurface(newsurface);
                    SDL_DestroyTexture(newtxt);
                    newsurface = NULL;
                    newtxt = NULL;
                    if (g_event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        running_game = true;
                        newsurface = IMG_Load("PNG//press_button.png");
                        newtxt = SDL_CreateTextureFromSurface(g_screen, newsurface);
                        SDL_RenderCopy(g_screen, newtxt, NULL, &play_rect);
                        SDL_RenderPresent(g_screen);
                        SDL_Delay(100);
                        SDL_RenderClear(g_screen);

                        SDL_FreeSurface(newsurface);
                        SDL_DestroyTexture(newtxt);
                        newsurface = NULL;
                        newtxt = NULL;
                        break;
                    }
                }
            else
                {
                    newsurface = IMG_Load("PNG//start_button.png");
                    newtxt = SDL_CreateTextureFromSurface(g_screen, newsurface);
                    SDL_RenderCopy(g_screen, newtxt, NULL, &play_rect);

                    SDL_FreeSurface(newsurface);
                    SDL_DestroyTexture(newtxt);
                    newsurface = NULL;
                    newtxt = NULL;
                }
            if (check_collisions_exit)
                {
                    newsurfaceexit = IMG_Load("PNG//motion_exit.png");
                    newtxtexit = SDL_CreateTextureFromSurface(g_screen, newsurfaceexit);
                    SDL_RenderCopy(g_screen, newtxtexit, NULL, &exit_rect);

                    SDL_FreeSurface(newsurfaceexit);
                    SDL_DestroyTexture(newtxtexit);
                    newsurfaceexit = NULL;
                    newtxtexit = NULL;
                    if (g_event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        quit_game = true;
                        newsurfaceexit = IMG_Load("PNG//press_exit.png");
                        newtxtexit = SDL_CreateTextureFromSurface(g_screen, newsurfaceexit);
                        SDL_RenderCopy(g_screen, newtxtexit, NULL, &exit_rect);
                        SDL_RenderPresent(g_screen);
                        SDL_Delay(100);
                        SDL_RenderClear(g_screen);

                        SDL_FreeSurface(newsurfaceexit);
                        SDL_DestroyTexture(newtxtexit);
                        newsurfaceexit = NULL;
                        newtxtexit = NULL;
                        break;
                    }
                }
            else
                {
                    newsurfaceexit = IMG_Load("PNG//start_exit.png");
                    newtxtexit = SDL_CreateTextureFromSurface(g_screen, newsurfaceexit);
                    SDL_RenderCopy(g_screen, newtxtexit, NULL, &exit_rect);
                    SDL_FreeSurface(newsurfaceexit);
                    SDL_DestroyTexture(newtxtexit);
                    newsurfaceexit = NULL;
                    newtxtexit = NULL;
                }


            if (check_collisions_guide)
                {
                    newsurfaceguide = IMG_Load("PNG//guide_button_2.png");
                    newtxtguide = SDL_CreateTextureFromSurface(g_screen, newsurfaceguide);
                    SDL_RenderCopy(g_screen, newtxtguide, NULL, &guide_rect);

                    SDL_FreeSurface(newsurfaceguide);
                    SDL_DestroyTexture(newtxtguide);
                    newsurfaceguide = NULL;
                    newtxtguide = NULL;
                    if (g_event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        guide_running = true;
                        newsurfaceguide = IMG_Load("PNG//guide_button_3.png");
                        newtxtguide = SDL_CreateTextureFromSurface(g_screen, newsurfaceguide);
                        SDL_RenderCopy(g_screen, newtxtguide, NULL, &guide_rect);
                        SDL_RenderPresent(g_screen);
                        SDL_Delay(100);
                        SDL_RenderClear(g_screen);

                        SDL_FreeSurface(newsurfaceguide);
                        SDL_DestroyTexture(newtxtguide);
                        newsurfaceguide = NULL;
                        newtxtguide = NULL;
                        break;
                    }
                }
            else
                {
                    newsurfaceguide = IMG_Load("PNG//guide_button_1.png");
                    newtxtguide = SDL_CreateTextureFromSurface(g_screen, newsurfaceguide);
                    SDL_RenderCopy(g_screen, newtxtguide, NULL, &guide_rect);

                    SDL_FreeSurface(newsurfaceguide);
                    SDL_DestroyTexture(newtxtguide);
                    newsurfaceguide = NULL;
                    newtxtguide = NULL;
                }
            }
            while (guide_running)
            {
                SDL_Surface* guide_surface = IMG_Load("PNG//bg01.png");
                SDL_Texture* guide_texture = SDL_CreateTextureFromSurface(g_screen, guide_surface);
                SDL_RenderCopy(g_screen, guide_texture, NULL, NULL);
                SDL_FreeSurface(guide_surface);
                guide_surface = NULL;
                SDL_DestroyTexture(guide_texture);
                guide_texture = NULL;


                guide_surface = IMG_Load("PNG//GUIDE.png");
                guide_texture = SDL_CreateTextureFromSurface(g_screen, guide_surface);
                SDL_RenderCopy(g_screen, guide_texture, NULL, NULL);
                SDL_RenderPresent(g_screen);
                SDL_FreeSurface(guide_surface);
                guide_surface = NULL;
                SDL_DestroyTexture(guide_texture);
                guide_texture = NULL;
                while(SDL_PollEvent(&g_event)!=0)
                {
                    if (g_event.type == SDL_KEYDOWN)
                    {
                        guide_running = false;
                    }
                }
            }
            SDL_RenderPresent(g_screen);
    }
    int HP;
    int boss_check = 0;
    while (running_game)
    {
        Timer fps_timer;
        /*if (!init())
            return -1;*/
        int check_newhouse=1;
        int x_start_house;
        int y_start_house;
        if (!loadbg())
            return -1;
        Gamemap game_map;
        game_map.LoadMap("PNG//map.dat");
        game_map.LoadTile(g_screen);


        MainObject player;
        player.LoadImg("PNG//RunRight.png", g_screen);
        player.setclips();
        std::vector <ThreatObjects*> g_threat_list = creatthreatlist();
        Boss* g_boss = create_boss();
        int nums_of_threats = 0;
        int count_nums = 100;

        int count_check[g_threat_list.size()];
        for (int i=0; i<g_threat_list.size(); i++)
        {
                ThreatObjects* p_threat = g_threat_list.at(i);
                if(p_threat != NULL)
                {
                   p_threat->set_x_pos(1150);
                   p_threat->set_y_pos(470);
                   p_threat->set_up_hp(5);
                }
                count_check[i]=0;
        }


        ghost_house house[5];
        int house_x[5];
        int house_y[5];
        for (int i=0; i<5; i++)
        {
            house_x[i] = 1150*i+1150;
            house_y[i] = 360;
            if (i==1)
                house_x[i]+=150;
            else if (i==2)
                house_x[i]+=200;
            else if (i==3)
                house_x[i]+=280;
            else if (i==4)
                house_x[i]+=300;
        }

        g_boss->set_x_pos(house_x[4]);
        g_boss->set_y_pos(house_y[4]);

        int boder_A = g_boss->get_x_pos() - 100;
        int boder_B = g_boss->get_x_pos() + 100;

        g_boss->set_border_pos(boder_A, boder_B);

        bird supportor;
        int x_bird = 10;
        int y_bird = 10;

        bool quit = false;
        while(!quit && running_game)
        {
            fps_timer.start();
            while (SDL_PollEvent(&g_event)!=0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    quit = true;
                    running_game = false;
                    return 0;
                }
                player.HandleAction(g_event, g_screen);
            }
            SDL_RenderClear(g_screen);

            bg.Render(g_screen);

            Map map_data = game_map.getmap();

            player.handlebullet(g_screen);
            player.SetMapXY(map_data.start_x, map_data.start_y);
            player.conditionplayer(map_data);
            player.render_HP(g_screen);
            player.Show(g_screen);

            if (player.get_HP()<=0)
            {
                is_lose = true;
                running_game = false;
            }

            game_map.SetMap(map_data);
            game_map.DrawMap(g_screen);

            HP = player.get_HP();
            if (nums_of_threats>=g_threat_list.size())
            {
                nums_of_threats = g_threat_list.size();
                count_nums = 0;
            }
            else
            {
                count_nums++;
                nums_of_threats = count_nums/100;
            }

            if(nums_of_house > 3)
            {
                if (g_boss->get_status_valid())
                {
                    g_boss->set_status_valid(true);
                    g_boss->set_x_val(0.0);
                    g_boss->set_y_val(0.0);
                    g_boss->setmapxy(map_data.start_x, map_data.start_y);
                    g_boss->handle_move(g_screen, player.get_x_pos());
                    g_boss->Moving(map_data);
                    g_boss->render_hp(g_screen);
                    g_boss->show(g_screen);
                }
                else
                {
                    boss_check++;
                    if (boss_check >= 10)
                    {
                        g_boss->set_status_valid(true);
                        g_boss->set_x_pos(house_x[4]);
                        g_boss->set_y_pos(house_y[4]);

                        int boder_A = g_boss->get_x_pos() - 400;
                        int boder_B = g_boss->get_x_pos() + 400;

                        g_boss->set_border_pos(boder_A, boder_B);
                    }
                }
            }

            for (int i=0; i<nums_of_threats; i++)
            {
                ThreatObjects* p_threat = g_threat_list.at(i);
                if(p_threat != NULL)
                {
                    if (count_check[i]>=100)
                    {
                        p_threat->set_status_valid(true);
                        p_threat->set_x_pos(house_x[nums_of_house]);
                        p_threat->set_y_pos(house_y[nums_of_house]);
                        count_check[i]=0;
                    }
                    if (p_threat->get_status_valid())
                    {
                        int pos1 = p_threat->get_x_pos()-420;
                        int pos2 = p_threat->get_x_pos()+420;
                        p_threat->set_border_pos(pos1,pos2);
                        p_threat->setmapxy(map_data.start_x, map_data.start_y);
                        p_threat->handle_move(g_screen);
                        p_threat->Moving(map_data);
                        p_threat->createbullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                        p_threat->render_hp(g_screen);
                        p_threat->show(g_screen);
                    }
                    else
                    {
                        count_check[i]++;

                        p_threat->set_x_pos(-10);
                        p_threat->set_y_pos(-10);
                        p_threat->SetRect(-10, -10);
                    }
                }
            }
            std::vector <BulletObject*> bullet_list = player.get_bullet();

            for (int k=0; k<bullet_list.size(); k++)
            {
                BulletObject* bullet = bullet_list.at(k);
                if (bullet != NULL)
                {
                    Map mp = game_map.getmap();
                    int x1=0;
                    int x2=0;
                    int y1=0;
                    int y2=0;

                    int map_x = 0;
                    int map_y = 0;

                    map_x = mp.start_x/TILE_SIZE_X;

                    x1 = (mp.start_x%TILE_SIZE_X)*(-1);
                    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE_X);

                    map_y = mp.start_y/TILE_SIZE_Y;

                    y1 = (mp.start_y%TILE_SIZE_Y)*(-1);
                    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE_Y);

                    for (int i=y1; i<y2; i+= TILE_SIZE_Y)
                    {
                        map_x = mp.start_x/TILE_SIZE_X;
                        for (int j=x1; j<x2; j+=TILE_SIZE_X)
                        {
                            int val = mp.tile[map_y][map_x];
                            if (val>0)
                            {
                                SDL_Rect maprect = {j, i, 45, 48};
                                SDL_Rect bulletrect = bullet->GetRect();

                                bool is_collision = SDL_commonfunction::check_collision(bulletrect, maprect);

                                if (is_collision)
                                {
                                    player.removebullet(k);
                                }
                            }
                            map_x++;
                        }
                        map_y++;
                    }
                }
            }

            for (int i=0; i<bullet_list.size(); i++)
            {
                BulletObject* bullet = bullet_list.at(i);
                if (bullet != NULL)
                {
                    SDL_Rect bullet_rect = bullet->GetRect();
                    SDL_Rect house_rect;
                    for (int j=0; j<5; j++)
                    {
                        house_rect.x = house[j].get_x_pos();
                        house_rect.y = house[j].get_y_pos();
                        house_rect.w = house[j].GetRect().w/13;
                        house_rect.h = house[j].GetRect().h;
                        bool is_collision = SDL_commonfunction::check_collision(bullet_rect, house_rect);

                        if (is_collision)
                        {
                            house[j].set_is_valid(false);
                            player.removebullet(i);
                            check_newhouse = 0;
                        }
                    }
                }
            }

            for (int i=0; i<bullet_list.size(); i++)
            {
                BulletObject* bullet = bullet_list.at(i);
                if (bullet != NULL)
                {
                    for (int j = 0; j<nums_of_threats; ++j)
                    {
                        ThreatObjects* obj_threat = g_threat_list[j];
                        if (obj_threat != NULL)
                        {

                            if (obj_threat->get_status_valid())
                            {
                                SDL_Rect threatrect;
                                threatrect.x = obj_threat->GetRect().x;
                                threatrect.y = obj_threat->GetRect().y;
                                threatrect.w = obj_threat->get_width_frame();
                                threatrect.h = obj_threat->get_height_frame();

                                SDL_Rect bulletrect = bullet->GetRect();

                                bool is_collision = SDL_commonfunction::check_collision(bulletrect, threatrect);

                                if (is_collision)
                                {
                                    int x;
                                    if (player.get_type_bullet()==0)
                                        x = 1;
                                    else
                                        x = 5;
                                    player.removebullet(i);
                                    obj_threat->set_hp(x);
                                    if (obj_threat->get_hp()<=0)
                                    {
                                        int x = obj_threat->GetRect().x-50;
                                        int y = obj_threat->GetRect().y-30;
                                        explosion Ex;
                                        Ex.set_pos(x,y);
                                        Ex.show(g_screen,1,10);
    //                                    obj_threat->Free();
    //                                    g_threat_list.erase(g_threat_list.begin()+j);
                                        obj_threat->set_status_valid(false);
                                        obj_threat->set_up_hp(5);
                                        //SDL_RenderPresent(g_screen);
                                        nums_of_enemy++;
                                    }
                                }

                            }
                        }
                    }
                    SDL_Rect boss_rect = {g_boss->GetRect().x, g_boss->GetRect().y, g_boss->get_width_frame(), g_boss->get_height_frame()};
                    bool check_collision_player_boss = SDL_commonfunction::check_collision(bullet->GetRect(), boss_rect);
                    if (check_collision_player_boss)
                    {
                        int x;
                        if (player.get_type_bullet()==0)
                            x = 1;
                        else
                            x = 5;
                        player.removebullet(i);
                        g_boss->set_hp(x);
                        if (g_boss->get_hp()<=0)
                        {
                            g_boss->set_status_valid(false);
                        }
                    }
                }
            }

            {
                SDL_Rect boss_rect = {g_boss->GetRect().x, g_boss->GetRect().y, g_boss->get_width_frame(), g_boss->get_height_frame()};
                SDL_Rect play_rect_ = {player.GetRect().x, player.GetRect().y, player.get_width_frame(), player.get_heigh_frame()};
                bool check_collision_Boss = SDL_commonfunction::check_collision(boss_rect, play_rect_);
                if (check_collision_Boss)
                {
                    player.set_HP(0);
                    if (player.get_HP()<=0)
                    {
                        player.Free();
                        is_lose = true;
                        quit = true;
                        running_game = false;
                    }
                }
            }

            for (int j = 0; j<nums_of_threats; j++)
            {
                ThreatObjects* obj_threat = g_threat_list.at(j);
                if (obj_threat != NULL )
                {
                    if (obj_threat->get_status_valid())
                    {
                        std::vector<BulletObject*> Bullet_list_of_threat = obj_threat->get_bullet_list();
                        for (int i = 0; i<Bullet_list_of_threat.size(); i++)
                        {
                            SDL_Rect bulletrect = Bullet_list_of_threat.at(i)->GetRect();
                            SDL_Rect playerrect;
                            playerrect.x = player.GetRect().x;
                            playerrect.y = player.GetRect().y;
                            playerrect.w = player.get_width_frame();
                            playerrect.h = player.get_heigh_frame();
                            bool is_collision = SDL_commonfunction::check_collision(bulletrect, playerrect);
                            if (is_collision)
                            {
                                int x = 1;
                                obj_threat->removebullet(i);
                                player.set_HP(x);
                                if (player.get_HP()<=0)
                                {
                                    player.Free();
                                    is_lose = true;
                                    quit = true;
                                    running_game = false;
                                }
                            }
                        }
                    }
                }
            }
            stringstream noe;
            noe << nums_of_enemy << '/' << 9;

            SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, (noe.str()).c_str(), textColor);
            enemy_txt = SDL_CreateTextureFromSurface(g_screen, textSurface);
            SDL_FreeSurface(textSurface);
            textSurface = NULL;
            SDL_Rect des = {10, 10, 100, 50};
            SDL_RenderCopy(g_screen, enemy_txt, NULL, &des);

            SDL_DestroyTexture(enemy_txt);
            enemy_txt = NULL;

            for (int i=0; i<5; i++)
            {
                int a=house_x[i]-map_data.start_x;
                int b=house_y[i]-map_data.start_y;
                house[i].set_pos(a, b);
                house[i].show(g_screen);
            }
            while (house[nums_of_house].get_is_valid()!=true && nums_of_house<5)
            {
                nums_of_house++;
            }

            if (check_newhouse == 0)
            {
                for (int i=0; i<g_threat_list.size(); i++)
                {
                    ThreatObjects* p_threat = g_threat_list.at(i);
                    if (p_threat != NULL)
                    {
                        p_threat->set_x_pos(house_x[nums_of_house]);
                        p_threat->set_y_pos(house_y[nums_of_house]);
                        p_threat->set_up_hp(5);
                        p_threat->set_status_valid(false);
//                        x_start_house = house_x[nums_of_house];
//                        y_start_house = house_y[nums_of_house];
                    }
                }
                check_newhouse = 1;
            }

            if ( nums_of_house > 3)
            {
                for (int i=0; i<g_threat_list.size(); i++)
                {
                    ThreatObjects* p_threat = g_threat_list.at(i);
                    if (p_threat!=NULL)
                    {
                        p_threat->Free();
                        p_threat = NULL;
                    }
                }
                //running_game = false;
                g_threat_list.clear();
                check_newhouse = 1;
            }
            cout << nums_of_house << endl;
            if (nums_of_house > 4)
            {
                running_game = false;
                g_boss->Free();
                g_boss == NULL;
            }

            if(abs(player.GetRect().x - x_bird) !=30)
            {
                x_bird = player.GetRect().x-30;
            }
            if (abs(player.GetRect().y - y_bird) !=50)
            {
                y_bird = player.GetRect().y-50;
            }
            supportor.set_x_pos(x_bird);
            supportor.set_y_pos(y_bird);
            supportor.show(g_screen);

            SDL_RenderPresent(g_screen);

            int real_time = fps_timer.get_ticks();

            int time_of_one_frame = 1000/FPS;

            if (real_time < time_of_one_frame)
            {
                SDL_Delay(time_of_one_frame-real_time);
            }
        }
        for (int i=0; i<g_threat_list.size(); i++)
        {
            ThreatObjects* p_threat = g_threat_list.at(i);
            if (p_threat)
            {
                p_threat->Free();
                p_threat == NULL;
            }
        }
        g_threat_list.clear();
        supportor.Free();
        player.Free();
        g_boss->Free();
        g_boss == NULL;
        if (!running_game)
        {
            SDL_Surface* quit_game_sur = NULL;
            if (is_lose)
            {
                 quit_game_sur = IMG_Load("PNG//quit_bg.png");
            }
            else if (nums_of_house > 4 && !is_lose)
            {
                quit_game_sur =IMG_Load("PNG//win_bg.png");
            }
            else
            {
                return 0;
            }

            SDL_Texture* quit_game_txt = SDL_CreateTextureFromSurface(g_screen, quit_game_sur);

            SDL_RenderCopy(g_screen, quit_game_txt, NULL, NULL);

            SDL_FreeSurface(quit_game_sur);
            quit_game_sur = NULL;

            SDL_DestroyTexture(quit_game_txt);
            quit_game_txt = NULL;


            stringstream noe;
            noe << "YOUR POINT: " << nums_of_enemy;

            SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, (noe.str()).c_str(), textColor);
            enemy_txt = SDL_CreateTextureFromSurface(g_screen, textSurface);
            SDL_FreeSurface(textSurface);
            textSurface = NULL;
            SDL_Rect des = {530, 120, 200, 60};
            SDL_RenderCopy(g_screen, enemy_txt, NULL, &des);

            SDL_DestroyTexture(enemy_txt);
            enemy_txt = NULL;

                while(!quit_game && !running_game && !guide_running)
                {
                    while(SDL_PollEvent(&g_event)!=0)
                    {
                        SDL_Surface* quit_game_sur = NULL;
                        if (is_lose)
                        {
                             quit_game_sur = IMG_Load("PNG//quit_bg.png");
                        }
                        else if (nums_of_house > 4 && !is_lose)
                        {
                            quit_game_sur =IMG_Load("PNG//win_bg.png");
                        }
                        else
                        {
                            return 0;
                        }

                        SDL_Texture* quit_game_txt = SDL_CreateTextureFromSurface(g_screen, quit_game_sur);

                        SDL_RenderCopy(g_screen, quit_game_txt, NULL, NULL);

                        SDL_FreeSurface(quit_game_sur);
                        quit_game_sur = NULL;

                        SDL_DestroyTexture(quit_game_txt);
                        quit_game_txt = NULL;

                        textSurface = TTF_RenderText_Solid( gFont, (noe.str()).c_str(), textColor);
                        enemy_txt = SDL_CreateTextureFromSurface(g_screen, textSurface);
                        SDL_FreeSurface(textSurface);
                        textSurface = NULL;
                        SDL_RenderCopy(g_screen, enemy_txt, NULL, &des);

                        SDL_DestroyTexture(enemy_txt);
                        enemy_txt = NULL;

                        if (g_event.type == SDL_QUIT)
                            {
                                quit_game = true;
                                return 0;
                            }

                            SDL_Rect mouse_rect;
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            mouse_rect = {x, y, 1, 1};
                            bool check_collisions_play = SDL_commonfunction::check_collision(play_rect, mouse_rect);
                            bool check_collisions_exit = SDL_commonfunction::check_collision(exit_rect, mouse_rect);
                            bool check_collisions_guide = SDL_commonfunction::check_collision(guide_rect, mouse_rect);

                            SDL_RenderCopy(g_screen, quit_game_txt, NULL, NULL);
                        if (check_collisions_play)
                            {
                                newsurface = IMG_Load("PNG//GUIDE (9).png");
                                newtxt = SDL_CreateTextureFromSurface(g_screen, newsurface);
                                SDL_RenderCopy(g_screen, newtxt, NULL, &play_rect);
                                newsurface = NULL;
                                newtxt = NULL;
                                if (g_event.type == SDL_MOUSEBUTTONDOWN)
                                {
                                    nums_of_house = 0;
                                    running_game = true;
                                    quit_game = false;
                                    quit = false;
                                    newsurface = IMG_Load("PNG//GUIDE (10).png");
                                    newtxt = SDL_CreateTextureFromSurface(g_screen, newsurface);
                                    SDL_RenderCopy(g_screen, newtxt, NULL, &play_rect);
                                    SDL_RenderPresent(g_screen);
                                    SDL_Delay(100);
                                    break;
                                }
                            }
                        else
                            {
                                newsurface = IMG_Load("PNG//GUIDE (8).png");
                                newtxt = SDL_CreateTextureFromSurface(g_screen, newsurface);
                                SDL_RenderCopy(g_screen, newtxt, NULL, &play_rect);
                                newsurface = NULL;
                                newtxt = NULL;
                            }
                        if (check_collisions_exit)
                            {
                                newsurfaceexit = IMG_Load("PNG//motion_exit.png");
                                newtxtexit = SDL_CreateTextureFromSurface(g_screen, newsurfaceexit);
                                SDL_RenderCopy(g_screen, newtxtexit, NULL, &exit_rect);
                                newsurfaceexit = NULL;
                                newtxtexit = NULL;
                                if (g_event.type == SDL_MOUSEBUTTONDOWN)
                                {
                                    quit_game = true;
                                    newsurfaceexit = IMG_Load("PNG//press_exit.png");
                                    newtxtexit = SDL_CreateTextureFromSurface(g_screen, newsurfaceexit);
                                    SDL_RenderCopy(g_screen, newtxtexit, NULL, &exit_rect);
                                    SDL_RenderPresent(g_screen);
                                    SDL_Delay(100);
                                    break;
                                }
                            }
                        else
                            {
                                newsurfaceexit = IMG_Load("PNG//start_exit.png");
                                newtxtexit = SDL_CreateTextureFromSurface(g_screen, newsurfaceexit);
                                SDL_RenderCopy(g_screen, newtxtexit, NULL, &exit_rect);
                                newsurfaceexit = NULL;
                                newtxtexit = NULL;
                            }


                        if (check_collisions_guide)
                            {
                                newsurfaceguide = IMG_Load("PNG//guide_button_2.png");
                                newtxtguide = SDL_CreateTextureFromSurface(g_screen, newsurfaceguide);
                                SDL_RenderCopy(g_screen, newtxtguide, NULL, &guide_rect);
                                newsurfaceguide = NULL;
                                newtxtguide = NULL;
                                if (g_event.type == SDL_MOUSEBUTTONDOWN)
                                {
                                    guide_running = true;
                                    newsurfaceguide = IMG_Load("PNG//guide_button_3.png");
                                    newtxtguide = SDL_CreateTextureFromSurface(g_screen, newsurfaceguide);
                                    SDL_RenderCopy(g_screen, newtxtguide, NULL, &guide_rect);
                                    SDL_RenderPresent(g_screen);
                                    SDL_Delay(100);
                                    break;
                                }
                            }
                        else
                            {
                                newsurfaceguide = IMG_Load("PNG//guide_button_1.png");
                                newtxtguide = SDL_CreateTextureFromSurface(g_screen, newsurfaceguide);
                                SDL_RenderCopy(g_screen, newtxtguide, NULL, &guide_rect);
                                newsurfaceguide = NULL;
                                newtxtguide = NULL;
                            }

                        }
                        while (guide_running)
                        {
                            SDL_Surface* guide_surface = NULL;
                            if (is_lose)
                                guide_surface = IMG_Load("PNG//quit_bg.png");
                            else
                                guide_surface = IMG_Load("PNG//win_bg.png");
                            SDL_Texture* guide_texture = SDL_CreateTextureFromSurface(g_screen, guide_surface);
                            SDL_RenderCopy(g_screen, guide_texture, NULL, NULL);
                            SDL_FreeSurface(guide_surface);
                            guide_surface = NULL;
                            SDL_DestroyTexture(guide_texture);
                            guide_texture = NULL;


                            guide_surface = IMG_Load("PNG//GUIDE.png");
                            guide_texture = SDL_CreateTextureFromSurface(g_screen, guide_surface);
                            SDL_RenderCopy(g_screen, guide_texture, NULL, NULL);
                            SDL_RenderPresent(g_screen);
                            SDL_FreeSurface(guide_surface);
                            guide_surface = NULL;
                            SDL_DestroyTexture(guide_texture);
                            guide_texture = NULL;
                            while(SDL_PollEvent(&g_event)!=0)
                            {
                                if (g_event.type == SDL_KEYDOWN)
                                {
                                    guide_running = false;
                                }
                            }
                            SDL_RenderPresent(g_screen);
                        }
                    SDL_RenderPresent(g_screen);
                }
            }

            if (!running_game)
            {
                close();
                SDL_Quit();
                return 0;
            }
        }
    }
