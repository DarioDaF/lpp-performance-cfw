#include "modes/special/setup.h"

#define setup_custom_r 47
#define setup_custom_g 63
#define setup_custom_b 63

#define setup_preset_r 47
#define setup_preset_g 63
#define setup_preset_b 47

#define setup_velocity_r 31
#define setup_velocity_g 63
#define setup_velocity_b 63

#define setup_top_pro_r 63
#define setup_top_pro_g 47
#define setup_top_pro_b 63

#define setup_top_mk2_r 47
#define setup_top_mk2_g 31
#define setup_top_mk2_b 63

#define setup_performance_xy_r 63
#define setup_performance_xy_g 31
#define setup_performance_xy_b 31

#define setup_tick 33
#define setup_rainbow_length 48

const u8 setup_rainbow[setup_rainbow_length][3] = {{63, 0, 0}, {63, 7, 0}, {63, 15, 0}, {63, 23, 0}, {63, 31, 0}, {63, 39, 0}, {63, 47, 0}, {63, 55, 0}, {63, 63, 0}, {55, 63, 0}, {47, 63, 0}, {39, 63, 0}, {31, 63, 0}, {23, 63, 0}, {15, 63, 0}, {7, 63, 0}, {0, 63, 0}, {0, 63, 7}, {0, 63, 15}, {0, 63, 23}, {0, 63, 31}, {0, 63, 39}, {0, 63, 47}, {0, 63, 55}, {0, 63, 63}, {0, 55, 63}, {0, 47, 63}, {0, 39, 63}, {0, 31, 63}, {0, 23, 63}, {0, 15, 63}, {0, 7, 63}, {0, 0, 63}, {7, 0, 63}, {15, 0, 63}, {23, 0, 63}, {31, 0, 63}, {39, 0, 63}, {47, 0, 63}, {55, 0, 63}, {63, 0, 63}, {63, 0, 55}, {63, 0, 47}, {63, 0, 39}, {63, 0, 31}, {63, 0, 23}, {63, 0, 15}, {63, 0, 7}};

u8 setup_elapsed = setup_tick;
u8 setup_mode_counter = 0;
u8 setup_jump = 0;

void setup_init() {
	if (vel_sensitive) {
		rgb_led(11, setup_velocity_r, setup_velocity_g, setup_velocity_b); // Velocity sensitivity enabled
	} else {
		rgb_led(11, setup_velocity_r >> 2, setup_velocity_g >> 2, setup_velocity_b >> 2); // Velocity sensitivity disabled
	}

	rgb_led(81, mode_example_r >> 2, mode_example_g >> 2, mode_example_b >> 2); // Example mode

	switch (mode_default) {
		case 2:
			rgb_led(81, mode_example_r, mode_example_g, mode_example_b); // Performance mode selected
			break;
	}
	
	setup_elapsed = setup_tick;
}

void setup_timer_event() {
	if (++setup_elapsed >= setup_tick) {
		rgb_led(99, setup_rainbow[setup_mode_counter][0], setup_rainbow[setup_mode_counter][1], setup_rainbow[setup_mode_counter][2]); // Mode LED indicator animation
		setup_mode_counter++; setup_mode_counter %= setup_rainbow_length;
		
		setup_elapsed = 0;
	}
}

void setup_surface_event(u8 p, u8 v) {
	if (v) {
		setup_jump = 1;
		
		if (p == 0) { // Enter selected main mode
			mode_update(mode_default);
			setup_jump = 0;
		
		} else if (p == 11) { // Toggle velocity sensitivity
			vel_sensitive = (vel_sensitive)? 0 : 1;
			dirty = 1;
			mode_refresh();

		} else if (p == 81) { // Switch default mode
			mode_default = 2;
			mode_refresh();
		}
	
	} else { // Note released
		if (p == 0 && setup_jump) { // Quickly jump back to main mode
			mode_update(mode_default);
			setup_jump = 0;
		}
	}
}

void setup_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {}