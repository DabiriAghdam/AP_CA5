#ifndef PHYSICS_HANDLER_HPP
#define PHYSICS_HANDLER_HPP

#include "rsdl.hpp"

class Game_Window;

class Physics_Handler {
private:
    Game_Window* gw;

public:
    Physics_Handler(Game_Window* _gw);
    bool do_collide_vertically(Point p1, Point p2);
    bool do_collide_horizontally(Point p1, Point p2);
    int get_ground_y(Point center);
};

#endif