#ifndef PIPE_HPP
#define PIPE_HPP

#define PIPE_BODY_LEFT "assets/sprites/objects/pipe/left.png"
#define PIPE_BODY_RIGHT "assets/sprites/objects/pipe/right.png"
#define PIPE_HEAD_LEFT "assets/sprites/objects/pipe/head-left.png"
#define PIPE_HEAD_RIGHT "assets/sprites/objects/pipe/head-right.png"

#include "rsdl.hpp"

#define HEAD_LEFT 'h' + 'l'
#define HEAD_RIGHT 'h' + 'r'
#define PIPE_LEFT 'p' + 'l'
#define PIPE_RIGHT 'p' + 'r'

class Game_Window;

class Pipe {
private:
    int type;
    Point center;
    Game_Window* gw;
public:
    Pipe(Point _center, int _type, Game_Window* _gw);
    int get_x();
    int get_y();
    void draw(Window* window, float scale, Point offset);
};

#endif