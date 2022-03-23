#ifndef FAN_DRIVER_H
#define FAN_DRIVER_H

/**
 * File that implements fan driver.
 * IMPORTANT!! This is not thread safe.
 */

#include "registers.h"

typedef enum
{
    FAN_SUCCESS,
    FAN_FAILED
} fan_action_response_type;

typedef enum
{
    FAN_DIRECTION_CLOCKWISE, 
    FAN_DIRECTION_COUNTERCLOCKWISE
} fan_direction_type;

typedef enum
{
    FAN_START, 
    FAN_STOP
} fan_state_type;

fan_action_response_type fan_start_stop(fan_state_type new_state);
fan_action_response_type fan_set_direction(fan_direction_type new_direction);
fan_action_response_type fan_set_speed(uint8_t new_speed);

fan_state_type fan_get_state();
fan_direction_type fan_get_direction();
uint8_t fan_get_speed();




#endif // FAN_DRIVER_H