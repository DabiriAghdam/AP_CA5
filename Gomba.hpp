#ifndef GOMBA_HPP
#define GOMBA_HPP

#define GOMBA_WALKING_1 "assets/sprites/enemies/little_goomba/walking-1.png"
#define GOMBA_WALKING_2 "assets/sprites/enemies/little_goomba/walking-2.png"
#define GOMBA_DEAD "assets/sprites/enemies/little_goomba/dead.png"
#define DIE_SOUND "assets/sounds/sound_effects/enemy-stomp.wav"
#define WALKING 1

#include "rsdl.hpp"


class Game_Window;

class Gomba {
private:
    double vx;
    double vy;
    double ay;
    Point center;
    Game_Window* gw;
    bool dead;
    bool state;
    std::string walking_frames[2];

    bool is_in_air();
    bool can_go_forward();
    bool can_go_backward();
    bool can_go_up();
    void update_x();
    void update_y(); 

public:
    Gomba(Point _center, Game_Window* _gw);
    int get_x();
    int get_y();
    bool is_dead();
    void update();
    void draw(Window* window, float scale, Point offset, int frame);
    void die();
};
#endif