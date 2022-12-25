#include "Mario.hpp"
#include "Game_Window.hpp"

Mario::Mario(Point _center, Game_Window* _gw) : center(_center)
{
    gw = _gw;
    coins = INITIAL_COINS;
    lives = INITIAL_LIVES;
    vx = 0;
    vy = 0;
    ay = GRAVITY;
    state = IDLE + RIGHT;
    walking_left_frames[0] = MARIO_NORMAL_WALKING_LEFT_1;
    walking_left_frames[1] = MARIO_NORMAL_WALKING_LEFT_2;
    walking_left_frames[2] = MARIO_NORMAL_WALKING_LEFT_3;
    walking_right_frames[0] = MARIO_NORMAL_WALKING_RIGHT_1;
    walking_right_frames[1] = MARIO_NORMAL_WALKING_RIGHT_2;
    walking_right_frames[2] = MARIO_NORMAL_WALKING_RIGHT_3;
}

int Mario::get_coins()
{
    return coins;
}

int Mario::get_lives()
{
    return lives;
}

Point Mario::get_center()  
{   
    return center; 
}

void Mario::inc_coins(int count)
{
    coins += count;
}

void Mario::inc_lives(int count)
{
    lives += count;
}

void Mario::set_x(int _x)
{
    center.x = _x;
}
    
void Mario::set_y(int _y)
{
    center.y = _y;
}

void Mario::update_x()
{
    int x_offset = gw->get_x_offset();

    if (vx > 0 && can_go_forward())
    { 
        if (center.x > (x_offset + gw->get_width()) / 2 - gw->get_scale() * SPRITE_SIZE)
        {
            gw->increase_map_offset(0.0012);
        }
        center.x += vx;
        if (does_win())
            gw->finish_game();
    }
    else if (vx < 0 && can_go_backward())
    {
        center.x += vx;
    }
}

bool Mario::does_win()
{
    return center.x >= gw->get_flag_x();
}

void Mario::update_y()
{
    int tile_width = SPRITE_SIZE * gw->get_scale();
    int ground_y = get_ground_y();
    int ceiling_y = get_ceiling_y();
    vy += ay;
    if (vy < 0 && can_go_up()) 
        center.y += vy;
    else if (vy > 0 && is_in_air())
        center.y += vy;
    if (center.y > gw->get_height())
        die();
    else if (vy < 0 && ceiling_y != 0 && !can_go_up())
    {
        center.y = ceiling_y + tile_width / 2;
        vy = 0;
    }
    else if (vy > 0 && ground_y != gw->get_height() && !is_in_air())
    {
        center.y = ground_y - tile_width / 2;
        vy = 0;
    }
}

void Mario::die()
{
    gw->get_window()->pause_music();
    gw->get_window()->play_sound_effect(DEAD_SOUND);
    int x_offset = gw->get_x_offset();
    float scale = gw->get_scale();
    state = DEAD;
    lives--;
    gw->draw_background();
    gw->draw_header();
    gw->draw_map();
    gw->draw_mario();
    gw->get_window()->update_screen();
    delay(2250);
    if (lives > 0)
    {
        state = IDLE + RIGHT;
        gw->restart_game();
    }
    else 
        gw->game_over();
    
}

void Mario::update()
{
    update_x();
    update_y();  
}

void Mario::draw(Window* window, float scale, Point offset, int frame) //buggy
{
    if (state == DEAD)
    {
        window->draw_img(MARIO_DEAD,Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else if (state == LEFT)
    {
        window->draw_img(walking_left_frames[frame],
         Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else if (state == RIGHT)
    {
        window->draw_img(walking_right_frames[frame],
         Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else if (state == LEFT + JUMP)
    {
        window->draw_img(MARIO_NORMAL_JUMPING_LEFT,
         Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else if (state == RIGHT + JUMP)
    {
        window->draw_img(MARIO_NORMAL_JUMPING_RIGHT,
         Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else if (state == IDLE + RIGHT)
    {
        window->draw_img(MARIO_NORMAL_STANDING_RIGHT,
         Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else if (state == IDLE + LEFT)
    {
        window->draw_img(MARIO_NORMAL_STANDING_LEFT,
         Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else if (state == IDLE + JUMP + RIGHT)
    {
        window->draw_img(MARIO_NORMAL_JUMPING_RIGHT,
         Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else if (state == IDLE + JUMP + LEFT)
    {
        window->draw_img(MARIO_NORMAL_JUMPING_LEFT,
         Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
    else
    {
        window->draw_img(MARIO_NORMAL_STANDING_RIGHT,
         Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
}

bool Mario::is_in_air()
{
    int tile_width = SPRITE_SIZE * gw->get_scale();
    return center.y + tile_width / 2 < get_ground_y();
}

bool Mario::can_go_up()
{
    int tile_width = SPRITE_SIZE * gw->get_scale();
    return center.y - tile_width / 2 > get_ceiling_y();
}

bool Mario::can_go_forward()
{
    std::vector<Gomba>* gombas = gw->get_gombas();
    std::vector<Koopa>* koopas = gw->get_koopas();
    std::vector<Brick> bricks = *(gw->get_bricks());
    std::vector<Block> blocks = gw->get_blocks();
    std::vector<Pipe> pipes = gw->get_pipes();
    std::vector<Flag> flag = gw->get_flag();
	Physics_Handler* physic = gw->get_physic();
    Window* window = gw->get_window();
    float scale =  gw->get_scale();
    int width = gw->get_width();
    int x_offset = gw->get_x_offset();

    for (int i = 0; i < gombas->size(); i++)
    {
        if (!(*gombas)[i].is_dead())
        {
            Point p1((*gombas)[i].get_x(), (*gombas)[i].get_y());
            Point p2 = center;
            if (p1.x > p2.x && physic->do_collide_horizontally(p1, p2))
            {
                die();
                return false;
            }
        }
    }
    for(int i = 0; i < koopas->size(); i++)
    {
        if (!(*koopas)[i].is_dead())
        {
            Point p1((*koopas)[i].get_x(), (*koopas)[i].get_y());
            Point p2 = center;
            if (p1.x > p2.x && physic->do_collide_horizontally(p1, p2))
            {
                die();
                return false;
            }
        }
    }
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
    return true;
}

bool Mario::can_go_backward()
{
    std::vector<Gomba>* gombas = gw->get_gombas();
    std::vector<Koopa>* koopas = gw->get_koopas();
    std::vector<Brick> bricks = *(gw->get_bricks());
    std::vector<Block> blocks = gw->get_blocks();
    std::vector<Pipe> pipes = gw->get_pipes();
    std::vector<Flag> flag = gw->get_flag();
	Physics_Handler* physic = gw->get_physic();
    Window* window = gw->get_window();
    float scale =  gw->get_scale();
    int width = gw->get_width();
    int x_offset = gw->get_x_offset();

    for (int i = 0; i < gombas->size(); i++)
    {
        if (!(*gombas)[i].is_dead())
        {
            Point p1((*gombas)[i].get_x(), (*gombas)[i].get_y());
            if (p1.x < center.x && physic->do_collide_horizontally(center, p1))
            {
                die();
                return false;
            }
        }
    }
    for(int i = 0; i < koopas->size(); i++)
    {
        if (!(*koopas)[i].is_dead())
        {
            Point p1((*koopas)[i].get_x(), (*koopas)[i].get_y());
            if (p1.x < center.x && physic->do_collide_horizontally(center, p1))
            {
                die();
                return false;
            }
        }
    }
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
        Point p1(flag[i].get_x(), flag[i].get_y());
        if (p1.x < center.x && physic->do_collide_horizontally(center, p1))
            return false;
    }
    return true;
}

int Mario::get_ceiling_y()
{
    std::vector<Gomba>* gombas = gw->get_gombas();
    std::vector<Koopa>* koopas = gw->get_koopas();
    std::vector<Brick>* bricks = gw->get_bricks();
    std::vector<Block> blocks = gw->get_blocks();
    std::vector<Pipe> pipes = gw->get_pipes();
    std::vector<Flag> flag = gw->get_flag();
    Window* window = gw->get_window();
    float scale =  gw->get_scale();
    int width = gw->get_width();
	Physics_Handler* physic = gw->get_physic();
    int tile_half_width = SPRITE_SIZE / 2 * gw->get_scale();
    int ceiling_y = 0;

    for (int i = 0; i < blocks.size(); i++)
    {
        if (center.x <= blocks[i].get_x() + tile_half_width && center.x >= blocks[i].get_x() - tile_half_width)
        {
            if (blocks[i].get_y() <= center.y && ceiling_y < blocks[i].get_y() + tile_half_width)
                ceiling_y = blocks[i].get_y() + tile_half_width;
        }
    }
    for (int i = 0; i < bricks->size(); i++)
    {
        if (center.x <= (*bricks)[i].get_x() + tile_half_width && center.x >= (*bricks)[i].get_x() - tile_half_width)
        {
             if ((*bricks)[i].get_y() <= center.y && ceiling_y < (*bricks)[i].get_y() + tile_half_width)
            {
                ceiling_y = (*bricks)[i].get_y() + tile_half_width;
                Point p1((*bricks)[i].get_x(), (*bricks)[i].get_y());
                if ((*bricks)[i].get_state() != EMPTY && physic->do_collide_vertically(p1, center))
                {   if ((*bricks)[i].get_type() == COIN_BRICK)
                    {
                        coins++;
                        (*bricks)[i].show_coin(gw->get_window(), scale, Point(gw->get_x_offset() + SPRITE_SIZE * scale, 0 + SPRITE_SIZE * scale));
                    }
                    else if((*bricks)[i].get_type() == HEALTH_BRICK)
                    {
                        (*bricks)[i].release_mushroom(window, scale, Point(gw->get_x_offset() + SPRITE_SIZE * scale, 0 + SPRITE_SIZE * scale));
                    }
                }
            }
        }
    }
    for (int i = 0; i < pipes.size(); i++)
    {
        if (center.x <= pipes[i].get_x() + tile_half_width && center.x >= pipes[i].get_x() - tile_half_width)
        {
             if (pipes[i].get_y() <= center.y && ceiling_y < pipes[i].get_y() + tile_half_width)
                ceiling_y = pipes[i].get_y() + tile_half_width;
        }
    }
    return ceiling_y;

}

int Mario::get_ground_y()
{
    std::vector<Gomba>* gombas = gw->get_gombas();
    std::vector<Koopa>* koopas = gw->get_koopas();
    std::vector<Brick> bricks = *(gw->get_bricks());
    std::vector<Block> blocks = gw->get_blocks();
    std::vector<Pipe> pipes = gw->get_pipes();
    std::vector<Flag> flag = gw->get_flag();
    Window* window = gw->get_window();
	Physics_Handler* physic = gw->get_physic();
    float scale =  gw->get_scale();
    int width = gw->get_width();
    int tile_half_width = SPRITE_SIZE / 2 * gw->get_scale();
    int ground_y = gw->get_height();

    for (int i = 0; i < blocks.size(); i++)
    {
        if (center.x <= blocks[i].get_x() + tile_half_width && center.x >= blocks[i].get_x() - tile_half_width)
        {
            if (blocks[i].get_y() >= center.y && ground_y > blocks[i].get_y() - tile_half_width)
                ground_y = blocks[i].get_y() - tile_half_width;
        }
    }
    for (int i = 0; i < bricks.size(); i++)
    {
        if (center.x <= bricks[i].get_x() + tile_half_width && center.x >= bricks[i].get_x() - tile_half_width)
        {
             if (bricks[i].get_y() >= center.y && ground_y > bricks[i].get_y() - tile_half_width)
                ground_y = bricks[i].get_y() - tile_half_width;
        }
    }
    for (int i = 0; i < pipes.size(); i++)
    {
        if (center.x <= pipes[i].get_x() + tile_half_width && center.x >= pipes[i].get_x() - tile_half_width)
        {
             if (pipes[i].get_y() >= center.y && ground_y > pipes[i].get_y() - tile_half_width)
                ground_y = pipes[i].get_y() - tile_half_width;
        }
    }
    for (int i = 0; i < gombas->size(); i++)
    {
        if (!(*gombas)[i].is_dead() && 
            center.x <= (*gombas)[i].get_x() + tile_half_width && center.x >= (*gombas)[i].get_x() - tile_half_width)
        {
            if ((*gombas)[i].get_y() >= center.y)
            {
                Point p1((*gombas)[i].get_x(), (*gombas)[i].get_y());
                if (ground_y > (*gombas)[i].get_y() - tile_half_width
                    && physic->do_collide_vertically(p1, center))
                {
                    (*gombas)[i].die();
                    ground_y = (*gombas)[i].get_y() - tile_half_width;
                }
            }
        }
    }
    for (int i = 0; i < koopas->size(); i++)
    {
        if (!(*koopas)[i].is_dead() && 
            center.x <= (*koopas)[i].get_x() + tile_half_width && center.x >= (*koopas)[i].get_x() - tile_half_width)
        {
            if ((*koopas)[i].get_y() >= center.y)
            {
                Point p1((*koopas)[i].get_x(), (*koopas)[i].get_y());                
                if (ground_y > (*koopas)[i].get_y() - tile_half_width
                     && physic->do_collide_vertically(p1, center))
                {
                    (*koopas)[i].die();
                    ground_y = (*koopas)[i].get_y() - tile_half_width;
                }
            }
        }
    }
    return ground_y;
}

void Mario::handle_key_press(char ch)
{
    if (ch == RIGHT)
    {
        state = RIGHT;
        vx = MARIO_VX;
        update();
    }
    else if (ch == LEFT)
    {
        state = LEFT;
        int x_offset = gw->get_x_offset();
        if (center.x + vx > x_offset + gw->get_scale() * SPRITE_SIZE / 2)
        {
            vx = -MARIO_VX;
            update(); 
        }
    }
    else if (ch == JUMP)
    {
        state += JUMP;
        if (!is_in_air())
        {
          gw->get_window()->play_sound_effect(JUMP_SOUND);
          vy = -65;
          update(); 
        }
    }
}

void Mario::handle_key_release(char ch)
{
    if (ch == RIGHT)
    {
        vx = 0;
        state = IDLE + RIGHT;
    }
    else if (ch == LEFT)
    {
        vx = 0;
        state = IDLE + LEFT;
    }
}