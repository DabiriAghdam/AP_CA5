#ifndef RED_MUSHROOM_HPP
#define RED_MUSHROOM_HPP

#define RED_MUSHROOM "assets/sprites/objects/mushroom/red.png"

#include "rsdl.hpp"

class Game_Window;

class Red_Mushroom {
private:
    double vx;
    double vy;
    double ay;
    Point center;
    Game_Window* gw;
    bool visible;

    bool is_in_air();
    bool can_go_forward();
    bool can_go_backward();
    bool can_go_up();
    void update_x();
    void update_y(); 

public:
    Red_Mushroom(Point _center, Game_Window* _gw);
    int get_y();
    int get_x();
    bool is_visible();
    void update();
    void draw(Window* window, float scale, Point offset);
};

#endif