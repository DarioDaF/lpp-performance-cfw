#include "led/led.h"

void rgb_led(u8 p, u8 r, u8 g, u8 b) {
	if (p == 99) {
		hal_plot_led(TYPESETUP, 0, r, g, b);
	} else {
		hal_plot_led(TYPEPAD, p, r, g, b);
	}
}

void clear_led() {
	for (u8 i = 1; i < 100; i++) rgb_led(i, 0, 0, 0);
}

void palette_led(u8 x, u8 p, u8 v) {
	rgb_led(p, palette_value(x, v, 0), palette_value(x, v, 1), palette_value(x, v, 2));
}

// Draws byte as binary. Useful when debugging!
/*
	v -> value
	d -> direction: 0 = horizontal, 1 = vertical
	x -> offset from position 0
	r, g, b -> color
*/
void display_u8(u8 v, u8 d, u8 x, u8 r, u8 g, u8 b) { 
	for (u8 i = 0; i < 8; i++) {
		u8 w = (v >> i) & 1;
		rgb_led((d == 0)? (8 - i + x * 10) : ((i + 1) * 10 + x), r * w, g * w, b * w);
	}
}