#include "commonFunc.h"

bool SDL_commonfunction::check_collision (const SDL_Rect& obj1, const SDL_Rect& obj2)
{
    int left_1 = obj1.x;
    int right_1 = obj1.x + obj1.w;
    int top_1 = obj1.y;
    int bottom_1 = obj1.y + obj1.h;

    int left_2 = obj2.x;
    int right_2 = obj2.x + obj2.w;
    int top_2 = obj2.y;
    int bottom_2 = obj2.y + obj2.h;

    // th1: obj1 > obj2
    if (left_1 > left_2 && left_1 < right_2)
    {
        if (top_1 > top_2 && top_1 < bottom_2)
        {
            return true;
        }
    }

    if (left_1 > left_2 && left_1 < right_2)
    {
        if (bottom_1 > top_2 && bottom_1 < bottom_2)
        {
            return true;
        }
    }

    if (right_1 > left_2 && right_1 < right_2)
    {
        if (top_1 > top_2 && top_1 < bottom_2)
        {
            return true;
        }
    }

    if (right_1 > left_2 && right_1 < right_2)
    {
        if (bottom_1 > top_2 && bottom_1 < bottom_2)
        {
            return true;
        }
    }

    // th2 obj1 < obj 2
    if (left_2 > left_1 && left_2 < right_1)
    {
        if (top_2 > top_1 && top_2 < bottom_1)
        {
            return true;
        }
    }

    if (left_2 > left_1 && left_2 < right_1)
    {
        if (bottom_2 > top_1 && bottom_2 < bottom_1)
        {
            return true;
        }
    }

    if (right_2 > left_1 && right_2 < right_1)
    {
        if (top_2 > top_1 && top_2 < bottom_1)
        {
            return true;
        }
    }

    if (right_2 > left_1 && right_2 < right_1)
    {
        if (bottom_2 > top_1 && bottom_2 < bottom_1)
        {
            return true;
        }
    }

    //th3 : obj1 = obj2
    if (top_1 == top_2 && right_1 == right_2 && bottom_1 == bottom_2)
    {
        return true;
    }
    return false;
}
