#include "Physics_Handler.hpp"
#include "Game_Window.hpp"

Physics_Handler::Physics_Handler(Game_Window* _gw)   
{   
    gw =  _gw;    
}

bool Physics_Handler::do_collide_vertically(Point p1, Point p2)
{
    int tile_half_width = SPRITE_SIZE / 2 * gw->get_scale();
   if(p1.x + tile_half_width  >= p2.x - tile_half_width && p1.x - tile_half_width <= p2.x + tile_half_width
    && p1.y + tile_half_width >= p2.y - tile_half_width && p1.y - tile_half_width <= p2.y + tile_half_width)
        return true;
    return false;
}

bool Physics_Handler::do_collide_horizontally(Point p1, Point p2)
{
     int tile_half_width = SPRITE_SIZE / 2 * gw->get_scale();
   if(p1.x + tile_half_width  > p2.x - tile_half_width && p1.x - tile_half_width < p2.x + tile_half_width
    && p1.y + tile_half_width > p2.y - tile_half_width && p1.y - tile_half_width < p2.y + tile_half_width)
        return true;
    return false;
}

int Physics_Handler::get_ground_y(Point center)
{
    std::vector<Block> blocks = gw->get_blocks();
    std::vector<Brick> bricks = *(gw->get_bricks());
    std::vector<Pipe> pipes = gw->get_pipes();
    std::vector<Flag> flag = gw->get_flag();
    Window* window = gw->get_window();
    float scale =  gw->get_scale();
    int width = gw->get_width();
    int tile_half_width = SPRITE_SIZE / 2 * gw->get_scale();
    int ground_y = gw->get_height();

    for (int i = 0; i < blocks.size(); i++)
    {
        if (center.x <= blocks[i].get_x() + tile_half_width && center.x >= blocks[i].get_x() - tile_half_width)
        {
            if (blocks[i].get_y() >= center.y && ground_y > blocks[i].get_y())
                ground_y = blocks[i].get_y() - tile_half_width;
        }
    }
    for (int i = 0; i < bricks.size(); i++)
    {
        if (center.x <= bricks[i].get_x() + tile_half_width && center.x >= bricks[i].get_x() - tile_half_width)
        {
             if (bricks[i].get_y() >= center.y && ground_y > bricks[i].get_y())
                ground_y = bricks[i].get_y() - tile_half_width;
        }
    }
    for (int i = 0; i < pipes.size(); i++)
    {
        if (center.x <= pipes[i].get_x() + tile_half_width && center.x >= pipes[i].get_x() - tile_half_width)
        {
             if (pipes[i].get_y() >= center.y && ground_y > pipes[i].get_y())
                ground_y = pipes[i].get_y() - tile_half_width;
        }
    }
    Mario* m = gw->get_mario();
    Point p1 = m->get_center();
    if (center.x <= p1.x + tile_half_width && center.x >= p1.x - tile_half_width)
    {
     if (p1.y >= center.y && ground_y > p1.y)
        ground_y = p1.y - tile_half_width;
    }
    return ground_y;
}