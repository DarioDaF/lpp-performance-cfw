#include "other/tempo.h"

#define tempo_message_counter_max 96

// Listen to changes in these variables in your timer_event functions.
// You can use display_u8 to draw them to get familiar with them!
u32 tempo_counter = 0;
u8 tempo_listen = 0;
u32 tempo_timer = 0;
u8 tempo_message_counter = 0;
u32 tempo_bar = 2000;

void tempo_start() {
	tempo_counter = 0;
	tempo_listen = 1;
	tempo_timer = 0;
	tempo_message_counter = 0;
}

void tempo_midi() {
	if (tempo_listen) {
		u8 tempo_message_beat = tempo_message_counter_max >> 2;
		if ((++tempo_message_counter % tempo_message_beat) == tempo_message_beat) {
			tempo_bar = tempo_timer << 2;
			tempo_timer = 0;
		}
		if (tempo_message_counter == tempo_message_counter_max) {
			tempo_counter = 0;
			tempo_message_counter = 0;
		}
	}
}

void tempo_stop() {
	tempo_listen = 0;
}

void tempo_tick() {
	if (++tempo_counter >= tempo_bar) tempo_counter = 0;
}