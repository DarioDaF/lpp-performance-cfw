#ifndef CHALLENGE_H
#define CHALLENGE_H

#include "app.h"

#include "sysex/messages.h"

extern u8 challenge_do;
extern u16 challenge_counter;

void challenge_timer_event();

#endif