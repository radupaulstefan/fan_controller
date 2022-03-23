#ifndef FAN_CONTROL_MODULE_H
#define FAN_CONTROL_MODULE_H

#include "stdint.h"

#define FAN_API_SUCCESS                 0x00000000
#define FAN_API_BAD_PARAM               0x00000001
#define FAN_API_COMMAND_FAILED          0x00000002
#define FAN_API_DIRECTION_OUT_OF_RANGE  0x00000003
#define FAN_API_SPEED_OUT_OF_RANGE      0x00000004
#define FAN_API_BAD_FRAME               0x00000005

int process_message(uint8_t bufferLength, uint8_t* buffer);

#endif // FAN_CONTROL_MODULE_H