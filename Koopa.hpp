#ifndef KOOPA_HPP
#define KOOPA_HPP

#define KOOPA_WALKING_RIGHT_1 "assets/sprites/enemies/koopa_troopa/walking-right-1.png"
#define KOOPA_WALKING_RIGHT_2 "assets/sprites/enemies/koopa_troopa/walking-right-2.png"
#define KOOPA_WALKING_LEFT_1 "assets/sprites/enemies/koopa_troopa/walking-left-1.png"
#define KOOPA_WALKING_LEFT_2 "assets/sprites/enemies/koopa_troopa/walking-left-2.png"
#define KOOPA_DEAD "assets/sprites/enemies/koopa_troopa/dead.png"
#define DIE_SOUND "assets/sounds/sound_effects/enemy-stomp.wav"

#include "rsdl.hpp"

class Game_Window;

class Koopa {
    double vx;
    double vy;
    double ay;
    bool dead;
    int state;
    Point center;
    Game_Window* gw;
    std::string walking_left_frames[2];
    std::string walking_right_frames[2];

    bool is_in_air();
    bool can_go_forward();
    bool can_go_backward();
    bool can_go_up();
    void update_x();
    void update_y(); 
public:
    Koopa(Point _center, Game_Window* _gw);
    int get_x();
    int get_y();
    bool is_dead();
    void update();
    void draw(Window* window, float scale, Point offset, int frame);
    void die();
};
#endif