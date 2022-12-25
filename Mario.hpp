#ifndef MARIO_HPP
#define MARIO_HPP


#define JUMP_SOUND "assets/sounds/sound_effects/jump-small.wav"
#define DEAD_SOUND "assets/sounds/sound_effects/mario-death.wav"
#define MARIO_NORMAL_JUMPING_LEFT "assets/sprites/mario/normal/jumping-left.png"
#define MARIO_NORMAL_JUMPING_RIGHT "assets/sprites/mario/normal/jumping-right.png"
#define MARIO_NORMAL_SLIDING_LEFT "assets/sprites/mario/normal/sliding-left.png"
#define MARIO_NORMAL_SLIDING_RIGHT "assets/sprites/mario/normal/sliding-right.png"
#define MARIO_NORMAL_STANDING_LEFT "assets/sprites/mario/normal/standing-left.png"
#define MARIO_NORMAL_STANDING_RIGHT "assets/sprites/mario/normal/standing-right.png"
#define MARIO_NORMAL_WALKING_LEFT_1 "assets/sprites/mario/normal/walking-left-1.png"
#define MARIO_NORMAL_WALKING_LEFT_2 "assets/sprites/mario/normal/walking-left-2.png"
#define MARIO_NORMAL_WALKING_LEFT_3 "assets/sprites/mario/normal/walking-left-3.png"
#define MARIO_NORMAL_WALKING_RIGHT_1 "assets/sprites/mario/normal/walking-right-1.png"
#define MARIO_NORMAL_WALKING_RIGHT_2 "assets/sprites/mario/normal/walking-right-2.png"
#define MARIO_NORMAL_WALKING_RIGHT_3 "assets/sprites/mario/normal/walking-right-3.png"
#define MARIO_DEAD "assets/sprites/mario/normal/dead.png"

#define INITIAL_LIVES 3
#define INITIAL_COINS 0
#define IDLE 'i'
#define DEAD 666

#include "rsdl.hpp"

class Game_Window;

class Mario{
protected:
    Point center;
    double vx;
    double vy;
    double ay;
    int lives;
    int coins;
    int state;
    std::string walking_left_frames[3];
    std::string walking_right_frames[3];
    Game_Window* gw;

    bool does_win();
    bool is_in_air();
    bool can_go_forward();
    bool can_go_backward();
    bool can_go_up();
    void update_x();
    void update_y();
    int get_ground_y();
    int get_ceiling_y();
    void inc_coins(int count);
public:
    Mario(Point _center, Game_Window* _gw);
    void draw(Window* window, float scale, Point offset, int frame);
    void handle_key_press(char ch);
    void handle_key_release(char ch);
    int get_lives();
    int get_coins();
    void inc_lives(int count);
    void update();
    void set_x(int _x);
    void set_y(int _y);
    Point get_center();
    void die();
};

#endif