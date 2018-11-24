#include "sysex/sysex.h"

void handle_sysex(u8 port, u8 * d, u16 l) {
    // Device Inquiry - Read information about the connected device
	if (!memcmp(d, &syx_device_inquiry[0], syx_device_inquiry_length)) {
		hal_send_sysex(port, &syx_device_inquiry_response[0], syx_device_inquiry_response_length);
		return;
	}

	// Handle other custom SysEx messages
}