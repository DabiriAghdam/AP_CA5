#include "Flag.hpp"
#include "Game_Window.hpp"

Flag::Flag(Point _center, char _type, Game_Window* _gw) : center(_center) 
{  
    gw = _gw; 
    type = _type;
}


void Flag::draw(Window* win, float scale, Point offset)
{
    if (type == HEAD)
        win->draw_img(FLAG_HEAD, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    else if (type == BODY)
        win->draw_img(FLAG_BODY, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
}

int Flag::get_x()  
{   
    return center.x;   
}

int Flag::get_y()  
{   
    return center.y;   
}