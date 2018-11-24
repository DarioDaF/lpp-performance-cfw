#include "flash/flash.h"

#define flash_indicator_r 3
#define flash_indicator_g 0
#define flash_indicator_b 0

u8 flash[USER_AREA_SIZE] = {0};
u8 dirty = 0;

void flash_read() {
	hal_read_flash(0, &flash[0], USER_AREA_SIZE);
	u16 fp = 0;	
	
	vel_sensitive = flash[fp++];
	if (vel_sensitive >> 1) vel_sensitive = 0;
}

void flash_write() {
	if (dirty) {
		rgb_led(99, flash_indicator_r, flash_indicator_g, flash_indicator_b);
		u16 fp = 0;

		flash[fp++] = vel_sensitive;
		
		hal_write_flash(0, &flash[0], USER_AREA_SIZE);
		
		rgb_led(99, 0, 0, 0);
		dirty = 0;
	}
}