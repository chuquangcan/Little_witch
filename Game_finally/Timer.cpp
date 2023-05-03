#include "Timer.h"
#include "commonFunc.h"

Timer::Timer()
{
    start_tick = 0;
    pause_tick = 0;
    is_pausing = false;
    is_starting = false;
}

Timer::~Timer()
{}

void Timer::start()
{
    is_starting = true;
    is_pausing = false;
    start_tick = SDL_GetTicks(); // dem thoi gian ke tu khi tao thu vien
}

void Timer::stop()
{
    is_pausing = false;
    is_starting = false;
}

void Timer::paused()
{
    if (is_starting == true && is_pausing == false)
    {
        is_pausing = true;
        pause_tick = SDL_GetTicks()-start_tick;
    }
}

void Timer::unpaused()
{
    if (is_pausing == true)
    {
        is_pausing = false;
        start_tick = SDL_GetTicks()-pause_tick;
        pause_tick = 0;
    }
}

int Timer::get_ticks()
{
    if (is_starting == true)
    {
        if (is_pausing == true)
        {
            return pause_tick;
        }
        else
        {
            return SDL_GetTicks()-start_tick;
        }
    }
    return 0;
}

bool Timer::is_started()
{
    return is_starting;
}

bool Timer::is_paused()
{
    return is_pausing;
}

