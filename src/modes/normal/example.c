#include "modes/normal/example.h"

u8 example_screen[100] = {};

void example_led(u8 p, u8 v, u8 s) {
	palette_led(0, p, v);
	if (s) example_screen[p] = v;
}

void example_init() {
	for (u8 i = 0; i < 100; i++) {
		example_led(i, example_screen[i], 0);
	}
	
	if (!example_screen[98]) rgb_led(99, mode_example_r, mode_example_g, mode_example_b); // Example Mode LED
}

void example_timer_event() {}

void example_surface_event(u8 p, u8 v) {
	if (p == 0) { // Enter Setup mode
		if (v != 0) mode_update(mode_setup);
				
	} else { // Send MIDI input to DAW
		hal_send_midi(USBSTANDALONE, (v == 0)? 0x80 : 0x90, p, v);
	}
}

void example_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {
	if (port == USBSTANDALONE && ch == 0x0) {
		switch (t) { // Draw MIDI output from DAW
			case 0x8: // Note off
				v = 0; // We cannot assume a note off will come with velocity 0! Note, there is no break statement here!
			
			case 0x9: // Note on
				example_led(p, v, 1);
				break;
		}
	}
}