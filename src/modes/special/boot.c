#include "modes/special/boot.h"

void boot_init() {
	mode_update(mode_example);
}

void boot_timer_event() {} // You can optionally implement a boot animation here.

void boot_surface_event(u8 p, u8 v) {}

void boot_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {}