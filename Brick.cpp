#include "Game_Window.hpp"
#include "Brick.hpp"

Brick::Brick(Point _center, char _type, Game_Window* _gw) : center(_center) 
{
    gw = _gw; 
    type = _type;  
    animation_frames[0] = QUESTION_BRICK_1;
    animation_frames[1] = QUESTION_BRICK_2;
    animation_frames[2] = QUESTION_BRICK_3;
    state = QUESTION;
}

int Brick::get_x()  
{   
    return center.x;   
}

int Brick::get_y()  
{   
    return center.y;   
}

void Brick::become_empty() 
{   
    state = EMPTY; 
}

bool Brick::get_state()    
{   
    return state;  
}

char Brick::get_type() 
{   
    return type;    
}

void Brick::draw(Window* win, float scale, Point offset, int frame)
{
    if (type == _BRICK)
        win->draw_img(BRICK, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    else 
    {
        if (state == QUESTION)
            win->draw_img(animation_frames[frame], Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
        else if (state == EMPTY)
            win->draw_img(QUESTION_EMPTY, Rectangle(center - offset, SPRITE_SIZE * scale, SPRITE_SIZE * scale));
    }
}

void Brick::show_coin(Window* win, float scale, Point offset)
{
        win->play_sound_effect(COIN_SOUND);
        for (int i = 0; i < 3; i++)
        {
            win->draw_img(COIN, Rectangle(center - offset + Point(SPRITE_SIZE / 2 * scale,SPRITE_SIZE * scale * i - SPRITE_SIZE * scale), SPRITE_SIZE * scale, SPRITE_SIZE * scale));
            win->update_screen();
            delay(20);
        }
        become_empty();
}

void Brick::release_mushroom(Window* win, float scale, Point offset)
{
    gw->get_window()->play_sound_effect(POWER_UP_APPEAR_SOUND);
    become_empty();
    std::vector<Health_Mushroom>* health_mushrooms = gw->get_health_mushrooms();
    Health_Mushroom h(Point(center.x, center.y - scale * SPRITE_SIZE), gw);
    health_mushrooms->push_back(h);
}

void Brick::slide_a_little(Window* win, float scale, Point offset)
{
    for (int i = 0; i < 3; i++)
    {
        center.y += i;
        draw(win, scale, offset, 0);
        win->update_screen();
        delay(20);
    }
    for (int i = 0; i < 3; i++)
    {
        center.y -= i;
        draw(win, scale, offset, 0);
        win->update_screen();
        delay(20);
    }
}