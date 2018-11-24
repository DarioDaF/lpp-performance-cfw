#ifndef PALETTES_H
#define PALETTES_H

#include "app_defs.h"

#define palette_count 1

const u8 palette[palette_count][3][128];

u8 palette_value(u8 i, u8 v, u8 c);

#endif