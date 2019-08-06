#ifndef MESSAGES_H
#define MESSAGES_H

#include "app_defs.h"

#define syx_device_inquiry_length 6
#define syx_device_inquiry_response_length 17

#define syx_challenge_length 7
#define syx_challenge_response_length 10

#define syx_mode_selection_length 7
#define syx_mode_selection_response_length 9

#define syx_live_layout_selection_length 7
#define syx_live_layout_selection_response_length 9

#define syx_standalone_layout_selection_length 7
#define syx_standalone_layout_selection_response_length 9

#define syx_led_single_length 7
#define syx_led_column_length 7
#define syx_led_row_length 7
#define syx_led_all_length 7

#define syx_led_flash_length 7
#define syx_led_pulse_length 7

#define syx_led_rgb_length 7
#define syx_led_rgb_fast_length 2
#define syx_led_grid_length 7

#define syx_text_length 7
#define syx_text_response_length 8

#define syx_palette_start_length 9
#define syx_palette_write_length 8
#define syx_palette_export_length 13
#define syx_palette_end_length 9

#define syx_palette_text_length 33

#define syx_fader_length 7

extern const u8 syx_device_inquiry[syx_device_inquiry_length];
extern const u8 syx_device_inquiry_response[syx_device_inquiry_response_length];

extern const u8 syx_challenge[syx_challenge_length];
extern u8 syx_challenge_response[syx_challenge_response_length];

extern const u8 syx_mode_selection[syx_mode_selection_length];
extern u8 syx_mode_selection_response[syx_mode_selection_response_length];

extern const u8 syx_live_layout_selection[syx_live_layout_selection_length];
extern u8 syx_live_layout_selection_response[syx_live_layout_selection_response_length];

extern const u8 syx_standalone_layout_selection[syx_standalone_layout_selection_length];
extern u8 syx_standalone_layout_selection_response[syx_standalone_layout_selection_response_length];

extern const u8 syx_led_single[syx_led_single_length];
extern const u8 syx_led_column[syx_led_column_length];
extern const u8 syx_led_row[syx_led_row_length];
extern const u8 syx_led_all[syx_led_all_length];

extern const u8 syx_led_flash[syx_led_flash_length];
extern const u8 syx_led_pulse[syx_led_pulse_length];

extern const u8 syx_led_rgb[syx_led_rgb_length];
extern const u8 syx_led_rgb_fast[syx_led_rgb_fast_length];
extern const u8 syx_led_grid[syx_led_grid_length];

extern const u8 syx_text[syx_text_length];
extern const u8 syx_text_response[syx_text_response_length];

extern const u8 syx_palette_start[syx_palette_start_length];
extern const u8 syx_palette_write[syx_palette_write_length];
extern u8 syx_palette_export[syx_palette_export_length];
extern const u8 syx_palette_end[syx_palette_end_length];

extern u8 syx_palette_text[syx_palette_text_length];

extern const u8 syx_fader[syx_fader_length];

#endif