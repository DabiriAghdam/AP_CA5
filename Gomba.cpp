#include "Gomba.hpp"
#include "Physics_Handler.hpp"
#include "Game_Window.hpp"

Gomba::Gomba(Point _center, Game_Window* _gw) : center(_center) 
{  
	gw = _gw; 
    vx = -GOMBA_VX;
	vy = 0; 
	ay = GRAVITY; 
    dead = false;
    state = WALKING;
    walking_frames[0] = GOMBA_WALKING_1;
    walking_frames[1] = GOMBA_WALKING_2;
}

int Gomba::get_x()  
{   
    return center.x;   
}

int Gomba::get_y()  
{   
    return center.y;   
}

bool Gomba::is_dead()  
{   
    return dead;   
}

void Gomba::draw(Window* window, float scale, Point offset, int frame)
{
    if (state == WALKING)
    {
        if (frame > 1)
            frame = 0;
        window->draw_img(walking_frames[frame], Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else if (state == DEAD)
    {
        window->draw_img(GOMBA_DEAD, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
}

void Gomba::update()
{
    update_x();
	update_y();
}

void Gomba::update_x()
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

void Gomba::update_y()
{
	Physics_Handler* physic = gw->get_physic();
    int tile_width = SPRITE_SIZE * gw->get_scale();
    int ground_y = physic->get_ground_y(center);
    Mario* m = gw->get_mario();
    Point p1 = m->get_center();

    vy += ay;
    if (vy > 0 && is_in_air())
        center.y += vy;
    if (center.y >= gw->get_height())
        dead = true;
    else if (ground_y == p1.y - tile_width / 2 && physic->do_collide_vertically(p1, center))
    {
        m->die();
    } 
    else if (ground_y != gw->get_height() && center.y + tile_width / 2 >= ground_y)// buggy?
    {
        center.y = physic->get_ground_y(center) - tile_width / 2;
        vy = 0;
    } 
}

bool Gomba::is_in_air()
{
	Physics_Handler* physic = gw->get_physic();
    int tile_width = SPRITE_SIZE * gw->get_scale();
    return center.y + tile_width / 2 < physic->get_ground_y(center);
}

bool Gomba::can_go_forward()
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
    if (p1.x > center.x && physic->do_collide_horizontally(center, p1))
        m->die();
    return true;
}

bool Gomba::can_go_backward()
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
    if (p1.x < center.x && physic->do_collide_horizontally(center, p1))
        m->die();

    return true;
}

void Gomba::die() //not working properly
{
    int x_offset = gw->get_x_offset();
    float scale = gw->get_scale();
    dead = true;
    state = DEAD;
    gw->get_window()->play_sound_effect(DIE_SOUND);
    gw->draw_background();
    gw->draw_header();
    gw->draw_map();
    gw->draw_mario();
    draw(gw->get_window(), scale, Point(x_offset + SPRITE_SIZE / 2 * scale, 0 + SPRITE_SIZE / 2 * scale), 0);
    gw->get_window()->update_screen();
}