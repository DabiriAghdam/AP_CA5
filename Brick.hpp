#ifndef BRICK_HPP
#define BRICK_HPP

#define BRICK "assets/sprites/objects/bricks_blocks/brick.png"
#define QUESTION_BRICK_1 "assets/sprites/objects/bricks_blocks/question-1.png"
#define QUESTION_BRICK_2 "assets/sprites/objects/bricks_blocks/question-2.png"
#define QUESTION_BRICK_3 "assets/sprites/objects/bricks_blocks/question-3.png"
#define QUESTION_EMPTY "assets/sprites/objects/bricks_blocks/question-empty.png"
#define COIN "assets/sprites/objects/coin.png"
#define COIN_SOUND "assets/sounds/sound_effects/coin.wav"
#define POWER_UP_APPEAR_SOUND "assets/sounds/sound_effects/powerup-appears.wav"

#define QUESTION 1
#define EMPTY 0

#include "rsdl.hpp"


class Health_Mushroom;

class Brick {
private:
    char type;
    Point center;
    int state;
    std::string animation_frames[3];
    Game_Window* gw;
    Health_Mushroom* hmp;
    
public:
    Brick(Point _center, char _type, Game_Window* _gw);
    int get_x();
    int get_y();
    void draw(Window* window, float scale, Point offset, int frame);
    void show_coin(Window* win, float scale, Point offset);
    void release_mushroom(Window* win, float scale, Point offset);
    void become_empty();
    bool get_state();
    char get_type();
    void slide_a_little(Window* win, float scale, Point offset);
};

#endif