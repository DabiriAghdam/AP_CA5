#ifndef BLOCK_HPP
#define BLOCK_HPP

#define CLAY "assets/sprites/objects/bricks_blocks/clay.png"
#define BLOCK "assets/sprites/objects/bricks_blocks/block.png"

#include "rsdl.hpp"

class Game_Window;

class Block {
private:
    char type;
    Point center;
    Game_Window* gw;
public:
    Block(Point _center, char _type, Game_Window* _gw);
    int get_x();
    int get_y();
    void draw(Window* window, float scale, Point offset);
};

#endif