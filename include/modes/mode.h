#ifndef MODE_H
#define MODE_H

#include "app_defs.h"

#include "led/led.h"
#include "flash/flash.h"

#define mode_boot 0
#include "modes/special/boot.h"

#define mode_setup 1
#include "modes/special/setup.h"

#define mode_example 2
#include "modes/normal/example.h"

void (*const mode_init[3])();
void (*const mode_timer_event[3])();
void (*const mode_surface_event[3])(u8 p, u8 v);
void (*const mode_midi_event[3])(u8 port, u8 t, u8 ch, u8 p, u8 v);

u8 mode, mode_default;

void mode_refresh();
void mode_update(u8 x);
void mode_default_update(u8 x);

#endif