#include "modes/custom/snake.h"

void snake_init() {}
void snake_timer_event() {}

void snake_surface_event(u8 p, u8 v, u8 x, u8 y) {
  if (p == 0) { // Enter Setup mode
    if (v != 0) mode_update(mode_setup);

  }
}

void snake_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {}
void snake_aftertouch_event(u8 v) {}
void snake_poly_event(u8 p, u8 v) {}
