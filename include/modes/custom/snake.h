#ifndef SNAKE_H
#define SNAKE_H

#include "app.h"
#include "modes/mode.h"

#define mode_snake_r 0
#define mode_snake_g 63
#define mode_snake_b 30

void snake_init();
void snake_timer_event();
void snake_surface_event(u8 p, u8 v, u8 x, u8 y);
void snake_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void snake_aftertouch_event(u8 v);
void snake_poly_event(u8 p, u8 v);

#endif
