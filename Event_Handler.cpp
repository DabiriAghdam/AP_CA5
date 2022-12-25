#include "Event_Handler.hpp"
#include "Game_Window.hpp"
#include "Mario.hpp"

Event_Handler::Event_Handler(Game_Window* _gw)
{
  gw = _gw;
}

bool Event_Handler::process_event() 
{
  while(gw->get_window()->has_pending_event())
  {
    Event event = gw->get_window()->poll_for_event();
    Mario* m = gw->get_mario();
    switch (event.get_type()) {
    case Event::QUIT:
      return false;
    case Event::KEY_PRESS:
      m->handle_key_press(event.get_pressed_key());
      break;
    case Event::KEY_RELEASE:
      m->handle_key_release(event.get_pressed_key());
      break;
    default:
      break;
    }
  }
  return true;
}