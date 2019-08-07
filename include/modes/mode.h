#ifndef MODE_H
#define MODE_H

#include "app_defs.h"

#include "led/led.h"
#include "flash/flash.h"

/*[[[cog

import json

with open("./include/modes/mode.json", "r") as fp:
	mode_list = json.load(fp)

mode_count = 0
for block in mode_list:
	mode_count += len(block["list"])

]]]*/
//[[[end]]]

/*[[[cog

# Mode defines
i = 0
for block in mode_list:
	group = block["group"]
	for mode in block["list"]:
		cog.out("""
#define mode_{mode} {i}
#include "modes/{group}/{mode}.h"
""".format(i = i, group = group, mode = mode))
		i += 1
	cog.out("""
#define mode_{group} {i}
""".format(i = i, group= group))

]]]*/

#define mode_performance 0
#include "modes/normal/performance.h"

#define mode_ableton 1
#include "modes/normal/ableton.h"

#define mode_note 2
#include "modes/normal/note.h"

#define mode_drum 3
#include "modes/normal/drum.h"

#define mode_fader 4
#include "modes/normal/fader.h"

#define mode_programmer 5
#include "modes/normal/programmer.h"

#define mode_piano 6
#include "modes/normal/piano.h"

#define mode_text 7
#include "modes/normal/text.h"

#define mode_normal 8

#define mode_snake 8
#include "modes/custom/snake.h"

#define mode_custom 9

#define mode_scale_setup 9
#include "modes/special/scale_setup.h"

#define mode_editor 10
#include "modes/special/editor.h"

#define mode_setup 11
#include "modes/special/setup.h"

#define mode_boot 12
#include "modes/special/boot.h"

#define mode_puyo 13
#include "modes/special/puyo.h"

#define mode_idle 14
#include "modes/special/idle.h"

#define mode_special 15
//[[[end]]]

/*[[[cog

# Array definitions
cog.out("""
extern void (*const mode_init[{mode_count}])();
extern void (*const mode_timer_event[{mode_count}])();
extern void (*const mode_surface_event[{mode_count}])(u8 p, u8 v, u8 x, u8 y);
extern void (*const mode_midi_event[{mode_count}])(u8 port, u8 t, u8 ch, u8 p, u8 v);
extern void (*const mode_aftertouch_event[{mode_count}])(u8 v);
extern void (*const mode_poly_event[{mode_count}])(u8 p, u8 v);
""".format(mode_count = mode_count))

]]]*/

extern void (*const mode_init[15])();
extern void (*const mode_timer_event[15])();
extern void (*const mode_surface_event[15])(u8 p, u8 v, u8 x, u8 y);
extern void (*const mode_midi_event[15])(u8 port, u8 t, u8 ch, u8 p, u8 v);
extern void (*const mode_aftertouch_event[15])(u8 v);
extern void (*const mode_poly_event[15])(u8 p, u8 v);
//[[[end]]]

extern u8 mode, mode_default;

void mode_refresh();
void mode_update(u8 x);
void mode_default_update(u8 x);

#endif