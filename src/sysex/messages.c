#include "sysex/messages.h"

const u8 syx_device_inquiry[syx_device_inquiry_length] = {0xF0, 0x7E, 0x7F, 0x06, 0x01, 0xF7};
const u8 syx_device_inquiry_response[syx_device_inquiry_response_length] = {0xF0, 0x7E,
                                                                            0x00,                                                  // Device number
                                                                            0x06, 0x02, 0x00, 0x20, 0x29, 0x51, 0x00, 0x00, 0x00,  // Novation LP Pro Device ID (Constant)
                                                                            0x00, 0x00, 0x00, 0x00,                                // Firmware rev. (4 bytes) - change this!
                                                                            0xF7};