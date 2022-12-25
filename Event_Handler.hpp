#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "rsdl.hpp"

#define JUMP 'w'
#define LEFT 'a'
#define RIGHT 'd'

class Game_Window;

class Event_Handler{
private:
    Game_Window* gw;
public:
    Event_Handler(Game_Window* _gw);
    bool process_event();
};
#endif