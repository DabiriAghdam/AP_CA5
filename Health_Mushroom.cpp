#include "Health_Mushroom.hpp"
#include "Game_Window.hpp"

Health_Mushroom::Health_Mushroom(Point _center, Game_Window* _gw) : center(_center) 
{  
	gw = _gw; 
    vx = MUSHROOM_VX;
	vy = 0; 
	ay = GRAVITY; 
    visible = true;
}

int Health_Mushroom::get_y()  
{   
    return center.y;   
}

int Health_Mushroom::get_x()  
{   
    return center.x;   
}

bool Health_Mushroom::is_visible()  
{   
    return visible;   
}

void Health_Mushroom::draw(Window* window, float scale, Point offset)
{
    window->draw_img(HEALTH_MUSHROOM, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
}

void Health_Mushroom::update()
{
    update_x();
	update_y();
}

void Health_Mushroom::update_x()
{
    int x_offset = gw->get_x_offset();

	if (vx < 0 && !can_go_backward())
		vx = -vx;
    else if (vx > 0 && !can_go_forward())
        vx = -vx;
    if (vx < 0 && can_go_backward())
    { 
        center.x += vx;
    }
    else if (vx > 0 && can_go_forward()) 
        center.x += vx;
}

void Health_Mushroom::update_y()
{
	Physics_Handler* physic = gw->get_physic();
    int tile_width = SPRITE_SIZE * gw->get_scale();
    int ground_y = physic->get_ground_y(center);
    
    vy += ay;
    if (vy > 0 && is_in_air())
        center.y += vy;
    if (center.y >= gw->get_height())
    {
        visible = false;
        vx = 0;
        vy = 0;
        ay = 0;
    }
    else if (ground_y != gw->get_height() && center.y + tile_width / 2 >= ground_y)// buggy?
    {
        center.y = physic->get_ground_y(center) - tile_width / 2;
        vy = 0;
    }  
}

bool Health_Mushroom::is_in_air()
{
	Physics_Handler* physic = gw->get_physic();
    int tile_width = SPRITE_SIZE * gw->get_scale();
    return center.y + tile_width / 2 < physic->get_ground_y(center);
}

bool Health_Mushroom::can_go_forward()
{
    std::vector<Block> blocks = gw->get_blocks();
    std::vector<Brick> bricks = *(gw->get_bricks());
    std::vector<Pipe> pipes = gw->get_pipes();
    std::vector<Flag> flag = gw->get_flag();
	Physics_Handler* physic = gw->get_physic();
    Window* window = gw->get_window();
    float scale =  gw->get_scale();
    int width = gw->get_width();
    int x_offset = gw->get_x_offset();

    for(int i = 0; i < blocks.size(); i++)
    {
        Point p1(blocks[i].get_x(), blocks[i].get_y());
        Point p2 = center;
        if (p1.x > p2.x && physic->do_collide_horizontally(p1, p2))
            return false;
    }
    for(int i = 0; i < bricks.size(); i++)
    {
        Point p1(bricks[i].get_x(), bricks[i].get_y());
        Point p2 = center;
        if (p1.x > p2.x && physic->do_collide_horizontally(p1, p2))
            return false;
    }
    for(int i = 0; i < pipes.size(); i++)
    {
        Point p1(pipes[i].get_x(), pipes[i].get_y());
        Point p2 = center;
        if (p1.x > p2.x && physic->do_collide_horizontally(p1, p2))
            return false;
    }
    for(int i = 0; i < flag.size(); i++)
    {
        Point p1(pipes[i].get_x(), pipes[i].get_y());
        Point p2 = center;
        if (p1.x > p2.x && physic->do_collide_horizontally(p1, p2))
            return false;
    }

    Mario* m = gw->get_mario();
    Point p1 = m->get_center();
    if (p1.x > center.x && physic->do_collide_horizontally(center, p1) && visible)
    {
        visible = false;
        vx = 0;
        vy = 0;
        ay = 0;
        m->inc_lives(1);
    }
    return true;
}

bool Health_Mushroom::can_go_backward()
{
    std::vector<Block> blocks = gw->get_blocks();
    std::vector<Brick> bricks = *(gw->get_bricks());
    std::vector<Pipe> pipes = gw->get_pipes();
    std::vector<Flag> flag = gw->get_flag();
	Physics_Handler* physic = gw->get_physic();
    Window* window = gw->get_window();
    float scale =  gw->get_scale();
    int width = gw->get_width();
    int x_offset = gw->get_x_offset();

    for(int i = 0; i < blocks.size(); i++)
    {
        Point p1(blocks[i].get_x(), blocks[i].get_y());
        if (p1.x < center.x && physic->do_collide_horizontally(center, p1))
            return false;
    }
    for(int i = 0; i < bricks.size(); i++)
    {
        Point p1(bricks[i].get_x(), bricks[i].get_y());
        if (p1.x < center.x && physic->do_collide_horizontally(center, p1))
            return false;
    }
    for(int i = 0; i < pipes.size(); i++)
    {
        Point p1(pipes[i].get_x(), pipes[i].get_y());
        if (p1.x < center.x && physic->do_collide_horizontally(center, p1))
            return false;
    }
    for(int i = 0; i < flag.size(); i++)
{
        Point p1(pipes[i].get_x(), pipes[i].get_y());
        if (p1.x < center.x && physic->do_collide_horizontally(center, p1))
            return false;
    }

    Mario* m = gw->get_mario();
    Point p1 = m->get_center();
    if (p1.x < center.x && physic->do_collide_horizontally(center, p1) && visible)
    {
        gw->get_window()->play_sound_effect(MUSHROOM_SOUND);
        visible = false;
        vx = 0;
        vy = 0;
        ay = 0;
        m->inc_lives(1);
    }

    return true;
}