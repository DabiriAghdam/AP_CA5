#ifndef FLAG_HPP
#define FLAG_HPP

#define FLAG_BODY "assets/sprites/objects/flag/body.png"
#define FLAG_HEAD "assets/sprites/objects/flag/head.png"

#include "rsdl.hpp"

#define HEAD 'h' 
#define BODY 'b'

class Game_Window;

class Flag {
private:
    char type;
    Point center;
    Game_Window* gw;
public:
    Flag(Point _center, char _type, Game_Window* _gw);
    int get_x();
    int get_y();
    void draw(Window* window, float scale, Point offset);
};

#endif