#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <string>
#include <vector>
#include "Event_Handler.hpp"
#include "Map_Handler.hpp"
#include "Mario.hpp"
#include "Gomba.hpp"
#include "Koopa.hpp"
#include "Block.hpp"
#include "Flag.hpp"
#include "Brick.hpp"
#include "Health_Mushroom.hpp"
#include "Pipe.hpp"
#include "Red_Mushroom.hpp"
#include "Physics_Handler.hpp"


#define GRAVITY 10
#define WIDTH 1000
#define HEIGHT 650
#define FONT_SIZE 40
#define SPRITE_SIZE 16
#define MUSHROOM_VX 5
#define KOOPA_VX 2.5
#define GOMBA_VX 2.5
#define MARIO_VX 10
#define SCALE 2.25

#define FONT "assets/SuperMario256.ttf"
#define TITLE "Super Mario Bros Clone"
#define COINS_TEXT "COINS"
#define LIVES_TEXT "LIVES"
#define WIN_TEXT "You Win!"
#define LOSE_TEXT "You Lose!"
#define BACKGROUND_ADDRESS "assets/background_image.png"
#define WIN_SOUND "assets/sounds/sound_effects/level-clear.wav"
#define GAME_OVER_SOUND "assets/sounds/sound_effects/gameover.wav"
#define MAIN_THEME_MUSIC "assets/sounds/main_theme.ogg"
#define MUSHROOM_SOUND "assets/sounds/sound_effects/powerup.wav"


class Game_Window {
private:
    std::string title;
    std::string map_address;
    Window window;
    Event_Handler event_handler;
    Map_Handler map_handler;
    Physics_Handler physic;
    Mario mario;
    Point mario_initial_pos;
    int width;
    int height;
    int map_width;
    int map_height;
    int animation_frame;
    float map_offset;
    float scale;
    bool running;
    Map map;

    std::vector<Gomba> gombas;
    std::vector<Koopa> koopas;
    std::vector<Block> blocks;
    std::vector<Flag> flag;
    std::vector<Brick> bricks;
    std::vector<Health_Mushroom> health_mushrooms;
    std::vector<Red_Mushroom> red_mushrooms;//
    std::vector<Pipe> pipes;

    void read_map();
    void find_set_mario_pos();
    void update_objects();
    void draw_objects();
    
public:
    Game_Window(std::string _map_address,
     int _width = WIDTH, int _height = HEIGHT, std::string _title = TITLE);
    void show();
    void draw_background();
    void draw_header();
    void draw_map();
    void draw_mario();
    void increase_map_offset(float offset);
    float get_x_offset();
    float get_scale();
    int get_width();
    int get_height();
    int get_map_width();
    int get_flag_x();
    std::vector<Gomba>* get_gombas();
    std::vector<Koopa>* get_koopas();
    std::vector<Brick>* get_bricks();
    std::vector<Health_Mushroom>* get_health_mushrooms();
    std::vector<Block> get_blocks();
    std::vector<Pipe> get_pipes();
    std::vector<Flag> get_flag();
    Map get_map();
    void set_map_offset(float offset);
    void game_over();
    void finish_game();
    Mario* get_mario();
    Window* get_window();
    Physics_Handler* get_physic();
    void restart_game();
};

#endif