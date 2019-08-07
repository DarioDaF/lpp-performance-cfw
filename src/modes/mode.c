#include "modes/mode.h"

/*[[[cog

import json

with open("./include/modes/mode.json", "r") as fp:
	mode_list = json.load(fp)

mode_array = []
for block in mode_list:
	mode_array.extend(block["list"])

]]]*/
//[[[end]]]

// Arrays of function pointers. Used to programmatically call the correct mode's function
/*[[[cog

# Function Pointers

def genFuncArray(suffix, ret = "void", name = "mode", params = "", l = mode_array):
	count = len(l)
	content = ", ".join(map(lambda mode: mode + suffix, l))
	return """
{ret} (*const {name}{suffix}[{count}])({params}) = {{
	{content}
}};
""".format(suffix = suffix, ret = ret, name = name, params = params, content = content, count = count)

cog.out(genFuncArray("_init"))
cog.out(genFuncArray("_timer_event"))
cog.out(genFuncArray("_surface_event", params = "u8 p, u8 v, u8 x, u8 y"))
cog.out(genFuncArray("_midi_event", params = "u8 port, u8 t, u8 ch, u8 p, u8 v"))
cog.out(genFuncArray("_aftertouch_event", params = "u8 v"))
cog.out(genFuncArray("_poly_event", params = "u8 p, u8 v"))

]]]*/

void (*const mode_init[15])() = {
	performance_init, ableton_init, note_init, drum_init, fader_init, programmer_init, piano_init, text_init, snake_init, scale_setup_init, editor_init, setup_init, boot_init, puyo_init, idle_init
};

void (*const mode_timer_event[15])() = {
	performance_timer_event, ableton_timer_event, note_timer_event, drum_timer_event, fader_timer_event, programmer_timer_event, piano_timer_event, text_timer_event, snake_timer_event, scale_setup_timer_event, editor_timer_event, setup_timer_event, boot_timer_event, puyo_timer_event, idle_timer_event
};

void (*const mode_surface_event[15])(u8 p, u8 v, u8 x, u8 y) = {
	performance_surface_event, ableton_surface_event, note_surface_event, drum_surface_event, fader_surface_event, programmer_surface_event, piano_surface_event, text_surface_event, snake_surface_event, scale_setup_surface_event, editor_surface_event, setup_surface_event, boot_surface_event, puyo_surface_event, idle_surface_event
};

void (*const mode_midi_event[15])(u8 port, u8 t, u8 ch, u8 p, u8 v) = {
	performance_midi_event, ableton_midi_event, note_midi_event, drum_midi_event, fader_midi_event, programmer_midi_event, piano_midi_event, text_midi_event, snake_midi_event, scale_setup_midi_event, editor_midi_event, setup_midi_event, boot_midi_event, puyo_midi_event, idle_midi_event
};

void (*const mode_aftertouch_event[15])(u8 v) = {
	performance_aftertouch_event, ableton_aftertouch_event, note_aftertouch_event, drum_aftertouch_event, fader_aftertouch_event, programmer_aftertouch_event, piano_aftertouch_event, text_aftertouch_event, snake_aftertouch_event, scale_setup_aftertouch_event, editor_aftertouch_event, setup_aftertouch_event, boot_aftertouch_event, puyo_aftertouch_event, idle_aftertouch_event
};

void (*const mode_poly_event[15])(u8 p, u8 v) = {
	performance_poly_event, ableton_poly_event, note_poly_event, drum_poly_event, fader_poly_event, programmer_poly_event, piano_poly_event, text_poly_event, snake_poly_event, scale_setup_poly_event, editor_poly_event, setup_poly_event, boot_poly_event, puyo_poly_event, idle_poly_event
};
//[[[end]]]

u8 mode = 0;
u8 mode_default = 0;

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
