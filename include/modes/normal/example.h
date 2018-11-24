#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "app.h"
#include "modes/mode.h"

#define mode_example_r 63
#define mode_example_g 63
#define mode_example_b 63

void example_init();
void example_timer_event();
void example_surface_event(u8 p, u8 v);
void example_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);

#endif