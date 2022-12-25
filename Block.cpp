#include "Block.hpp"
#include "Game_Window.hpp"

Block::Block(Point _center, char _type, Game_Window* _gw) : center(_center) 
{  
    gw = _gw;
    type = _type;
}

int Block::get_x() 
{   
    return center.x;   
}

int Block::get_y()  
{   
    return center.y;   
}

void Block::draw(Window* win, float scale, Point offset)
{
    if (type == _BLOCK)
        win->draw_img(BLOCK, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    else if (type == _CLAY)
        win->draw_img(CLAY, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
}