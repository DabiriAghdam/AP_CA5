#include "Game_Window.hpp"

Game_Window::Game_Window(std:: string _map_address, int _width, int _height, std::string _title)
: event_handler(this) , mario(Point(0, 0), this), window(_width, _height, _title), physic(this), mario_initial_pos(0 , 0)
{
    width = _width;
    height = _height;
    title = _title;
    map_address = _map_address;
    map_width = 0;
    map_height = 0;
    map_offset = 0;
    animation_frame = 0;
    scale = SCALE;
    running = false;
}

void Game_Window::increase_map_offset(float offset)  
{   
    map_offset += offset;    
}

Physics_Handler* Game_Window::get_physic()   
{   
    return  &physic;  
}


float Game_Window::get_scale() 
{
    return scale;   
}

int Game_Window::get_width() 
{
    return width;   
}

int Game_Window::get_height() 
{  
    return height;    
}

int Game_Window::get_map_width() 
{   
    return map_width;  
}

int Game_Window::get_flag_x()    
{
    return flag[0].get_x();    
}

std::vector<Gomba>* Game_Window::get_gombas() 
{   
    return &gombas; 
}

std::vector<Koopa>* Game_Window::get_koopas() 
{   
    return &koopas; 
}

std::vector<Brick>* Game_Window::get_bricks()    
{    
    return &bricks;  
}

std::vector<Block> Game_Window::get_blocks()    
{   
    return blocks; 
}

std::vector<Pipe> Game_Window::get_pipes()  
{   
    return pipes;  
}

std::vector<Flag> Game_Window::get_flag()    
{   
    return flag;    
}

std::vector<Health_Mushroom>* Game_Window::get_health_mushrooms()
{
    return &health_mushrooms;
}

Map Game_Window::get_map() 
{ 
    return map;  
}

float Game_Window::get_x_offset()
{
    return map_offset * map_width * scale * SPRITE_SIZE;
}

void Game_Window::set_map_offset(float offset)
{
    map_offset = offset;
}

void Game_Window::restart_game()
{
    window.play_music(MAIN_THEME_MUSIC);
    mario.set_x(mario_initial_pos.x);
    mario.set_y(mario_initial_pos.y);
    map_offset = 0;
}

void Game_Window::read_map()
{
    map = map_handler.read_map(map_address);
    map_height = map.size();
    map_width = map[0].size();
    int count = width / (scale * SPRITE_SIZE); 
    int y_offset = height - scale * SPRITE_SIZE * map_height;

    for (int i = 0; i < map.size(); i++)
    {
        for(int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == PIPE)
            {
                if (i - 1 > 0 && map[i - 1][j] == PIPE)
                {
                    Pipe p1(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), PIPE_LEFT, this);
                    pipes.push_back(p1);
                    j++;
                    Pipe p2(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), PIPE_RIGHT, this);
                    pipes.push_back(p2);
                }
                else
                {
                    Pipe p1(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), HEAD_LEFT, this);
                    pipes.push_back(p1);
                    j++;
                    Pipe p2(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), HEAD_RIGHT, this);                    
                    pipes.push_back(p2);
                }  
            }
            else if (map[i][j] == FLAG && i - 1 > 0)
            {
                if (map[i - 1][j] != FLAG)
                {
                    Flag f(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), HEAD, this);
                    flag.push_back(f);
                }
                else if (map[i - 1][j] == FLAG)
                {
                    Flag f(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), BODY, this);
                    flag.push_back(f);
                }
            }
            else if (map[i][j] == _BLOCK)
            {
                Block b(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), _BLOCK, this);
                blocks.push_back(b);
            }
             else if (map[i][j] == _CLAY)
            {
                Block b(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), _CLAY, this);
                blocks.push_back(b);
            }
            else if (map[i][j] == _BRICK)
            {
                Brick b(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), _BRICK, this);
                bricks.push_back(b);
            }
            else if (map[i][j] == COIN_BRICK)
            {
                Brick b(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), COIN_BRICK, this);
                bricks.push_back(b);
            }            
            else if (map[i][j] == HEALTH_BRICK)
            {
                Brick b(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), HEALTH_BRICK, this);
                bricks.push_back(b);
            }
            else if (map[i][j] == MUSHROOM_BRICK)
            {
                Brick b(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), MUSHROOM_BRICK, this);
                bricks.push_back(b);
            }
            else if (map[i][j] == GOMBA)
            {
                Gomba g(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), this);
                gombas.push_back(g);
            }
            else if (map[i][j] == KOOPA)
            {
                Koopa k(Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE), this);
                koopas.push_back(k);
            }
            else if (map[i][j] == MARIO)
            {
                Point p1 = Point((j + 0.5) * scale * SPRITE_SIZE, y_offset + (i + 0.5) * scale * SPRITE_SIZE);
                mario_initial_pos = p1;
                mario.set_x(p1.x);
                mario.set_y(p1.y);
            }  
        }
    }
}

void Game_Window::show()
{
    read_map();
    running = true;
    window.play_music(MAIN_THEME_MUSIC);
    while(running)
    {
        running = event_handler.process_event();
        update_objects();
        draw_objects();
        window.update_screen();
        delay(50);
        if (animation_frame > 1)
            animation_frame = 0;
        else
            animation_frame++;
    }
}

void Game_Window::update_objects()
{
    int x_offset = get_x_offset();
    mario.update();
    for (int i = 0;i < gombas.size(); i++)
    {
        if (gombas[i].get_x() >= x_offset && gombas[i].get_x() <= x_offset + width + 2 * SPRITE_SIZE * scale
            && !gombas[i].is_dead())
            gombas[i].update();
    }
    for (int i = 0;i < koopas.size(); i++)
    {
        if (koopas[i].get_x() >= x_offset && koopas[i].get_x() <= x_offset + width + 2 * SPRITE_SIZE * scale 
            && !koopas[i].is_dead())
           koopas[i].update();
        
    }
    for (int i = 0;i < health_mushrooms.size(); i++)
    {
        if (health_mushrooms[i].get_x() >= x_offset && health_mushrooms[i].get_x() <= x_offset + width + 2 * SPRITE_SIZE * scale 
            && health_mushrooms[i].is_visible())
           health_mushrooms[i].update();
        
    }
}

void Game_Window::draw_objects()
{
    draw_background();
    draw_header();
    draw_map();
    draw_mario();
}

void Game_Window::finish_game()
{
    window.stop_music();
    window.play_sound_effect(WIN_SOUND);
    window.clear();
    window.show_text(WIN_TEXT, Point(width / 7, height / 2.5), WHITE, FONT, 3.25 * FONT_SIZE);
    window.update_screen();
    delay(5000);
    exit(EXIT_SUCCESS);
}

void Game_Window::game_over()
{
    window.stop_music();
    window.play_sound_effect(GAME_OVER_SOUND);
    window.clear();
    window.show_text(LOSE_TEXT, Point(width / 8, height / 2.5), WHITE, FONT, 3.25 * FONT_SIZE);
    window.update_screen();
    delay(5000);
    exit(EXIT_SUCCESS);
}

Mario* Game_Window::get_mario()
{
    return &mario;
}

Window* Game_Window::get_window()
{
    return &window;
}

void Game_Window::draw_header()
{
    window.show_text(COINS_TEXT, Point(width / 3, height / 100), WHITE, FONT, FONT_SIZE);
    window.show_text(std::to_string(mario.get_coins()), Point(width / 3 + FONT_SIZE, height / 100 + FONT_SIZE), WHITE, FONT, FONT_SIZE);
    window.show_text(LIVES_TEXT, Point(width / 3 + FONT_SIZE * 6, height / 100), WHITE, FONT, FONT_SIZE);
    window.show_text(std::to_string(mario.get_lives()), Point(width / 3 + FONT_SIZE + FONT_SIZE * 6, height / 100 + FONT_SIZE), WHITE, FONT, FONT_SIZE);
}

void Game_Window::draw_background()
{
    int count = 8100 / (scale * SPRITE_SIZE);
    //int offset = get_x_offset();
    window.draw_img(BACKGROUND_ADDRESS, NULL_RECT, Rectangle(Point(map_offset * count, 380), 666, 600)); //numbers?!
}

void Game_Window::draw_mario()
{
    int x_offset = get_x_offset();
    mario.draw(&window, scale, Point(x_offset + SPRITE_SIZE / 2 * scale, 0 + SPRITE_SIZE / 2 * scale), animation_frame);
}

void Game_Window::draw_map()
{
    int x_offset = get_x_offset();

    for (int i = 0; i < gombas.size(); i++)
    {
        if (!gombas[i].is_dead() && gombas[i].get_x() >= x_offset && gombas[i].get_x() <= x_offset + width)
            gombas[i].draw(&window, scale, Point(x_offset + SPRITE_SIZE / 2 * scale, 0 + SPRITE_SIZE / 2 * scale), animation_frame);
    }
    for(int i = 0; i < koopas.size(); i++)
    {
        if (!koopas[i].is_dead() && koopas[i].get_x() >= x_offset && koopas[i].get_x() <= x_offset + width)
            koopas[i].draw(&window, scale, Point(x_offset + SPRITE_SIZE / 2 * scale, 0 + SPRITE_SIZE / 2 * scale), animation_frame);
    }
    for(int i = 0; i < blocks.size(); i++)
    {
        if (blocks[i].get_x() >= x_offset && blocks[i].get_x() <= x_offset + width)
           blocks[i].draw(&window, scale, Point(x_offset + SPRITE_SIZE / 2 * scale, 0 + SPRITE_SIZE / 2 * scale));
    }
    for(int i = 0; i < bricks.size(); i++)
    {
        if (bricks[i].get_x() >= x_offset && bricks[i].get_x() <= x_offset + width)
            bricks[i].draw(&window, scale, Point(x_offset + SPRITE_SIZE / 2 * scale, 0 + SPRITE_SIZE / 2 * scale), animation_frame);
    }
    for(int i = 0; i < pipes.size(); i++)
    {
        if (pipes[i].get_x() >= x_offset && pipes[i].get_x() <= x_offset + width)
            pipes[i].draw(&window, scale, Point(x_offset + SPRITE_SIZE / 2 * scale, 0 + SPRITE_SIZE / 2 * scale));
    }
    for(int i = 0; i < flag.size(); i++)
    {
        if (flag[i].get_x() >= x_offset && flag[i].get_x() <= x_offset + width)
            flag[i].draw(&window, scale, Point(x_offset + SPRITE_SIZE / 2 * scale, 0 + SPRITE_SIZE / 2 * scale));
    }
    for(int i = 0; i < health_mushrooms.size(); i++)
    {
        if (health_mushrooms[i].is_visible() && 
            health_mushrooms[i].get_x() >= x_offset && health_mushrooms[i].get_x() <= x_offset + width)
            health_mushrooms[i].draw(&window, scale, Point(x_offset + SPRITE_SIZE / 2 * scale, 0 + SPRITE_SIZE / 2 * scale));
    }
}
