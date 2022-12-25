#include "Game_Window.hpp"
#include "Pipe.hpp"

Pipe::Pipe(Point _center, int _type, Game_Window* _gw) : center(_center) 
{  
    gw = _gw; 
    type = _type;
}

void Pipe::draw(Window* win, float scale, Point offset)
{
    if (type == HEAD_LEFT)
        win->draw_img(PIPE_HEAD_LEFT, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale)); // - Point(SPRITE_SIZE / 2 * scale, SPRITE_SIZE / 2 * scale)
    else if (type == HEAD_RIGHT)
        win->draw_img(PIPE_HEAD_RIGHT, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale)); // - Point(SPRITE_SIZE / 2 * scale, SPRITE_SIZE / 2 * scale)
    else if (type == PIPE_LEFT)
        win->draw_img(PIPE_BODY_LEFT, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale)); // - Point(SPRITE_SIZE / 2 * scale, SPRITE_SIZE / 2 * scale)
    else if (type == PIPE_RIGHT)
        win->draw_img(PIPE_BODY_RIGHT, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale)); // - Point(SPRITE_SIZE / 2 * scale, SPRITE_SIZE / 2 * scale)
}

int Pipe::get_x()  
{   
    return center.x;   
}

int Pipe::get_y()  
{   
    return center.y;   
}