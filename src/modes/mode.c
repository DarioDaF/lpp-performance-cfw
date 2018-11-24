#include "modes/mode.h"

// Arrays of function pointers. Used to programmatically call the correct mode's function
void (*const mode_init[3])() = {
	boot_init,
	setup_init,
	example_init
};
void (*const mode_timer_event[3])() = {
	boot_timer_event,
	setup_timer_event,
	example_timer_event
};
void (*const mode_surface_event[3])(u8 p, u8 v) = {
	boot_surface_event,
	setup_surface_event,
	example_surface_event
};
void (*const mode_midi_event[3])(u8 port, u8 t, u8 ch, u8 p, u8 v) = {
	boot_midi_event,
	setup_midi_event,
	example_midi_event
};

u8 mode = mode_boot; // Starting mode
u8 mode_default = mode_example; // Starting default mode

void mode_refresh() {
	clear_led();
	(*mode_init[mode])();
}

void mode_update(u8 x) {
	clear_led();
	flash_write();
	
	mode = x;
	(*mode_init[mode])();
}

void mode_default_update(u8 x) {
	if (mode_default != x) {
		mode_default = x;
		mode_update(mode_default);
	}
}