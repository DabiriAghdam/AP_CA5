#ifndef MAP_HANDLER_HPP
#define MAP_HANDLER_HPP

#include <string>
#include <vector>

#define EMPTY_SPACE '.'
#define _BRICK 'b'
#define COIN_BRICK '?'
#define MUSHROOM_BRICK 'm'
#define HEALTH_BRICK 'h'
#define _BLOCK '@'
#define _CLAY '#'
#define MARIO 'M'
#define GOMBA 'l'
#define KOOPA 'k'
#define PIPE '|'
#define FLAG 'f'

typedef std::vector<std::vector<char>> Map;
class Map_Handler {
private:
public:
    Map read_map(std::string address);
};

#endif