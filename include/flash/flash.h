#ifndef FLASH_H
#define FLASH_H

#include "app.h"

#include "flash/settings.h"
#include "led/led.h"

extern u8 dirty;

void flash_read();
void flash_write();

#endif