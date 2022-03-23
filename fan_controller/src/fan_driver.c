#include "fan_driver.h"

#define FAN_BITS_START_STOP_OFFSET 0
#define FAN_BITS_DIRECTION_OFFSET 1
#define FAN_BITS_NOT_DEFINED_OFFSET 2
#define FAN_BITS_SPEED_OFFSET 4

#define FAN_SET_BIT(bit_pos) (FAN |= (1 << bit_pos))
#define FAN_RESET_BIT(bit_pos) (FAN &= ~(1 << bit_pos))

#define FAN_READ_BIT(bit_pos) ((FAN & (1 << bit_pos)) >> bit_pos)

#define FAN_WRITE_SPEED(speed) (FAN |= (0x0F & FAN) + (speed << FAN_BITS_SPEED_OFFSET))
#define FAN_READ_SPEED ((FAN & 0xF0) >> 4)

fan_action_response_type fan_start_stop(fan_state_type new_state)
{
    FAN = new_state == FAN_START ? FAN_SET_BIT(FAN_BITS_START_STOP_OFFSET) : FAN_RESET_BIT(FAN_BITS_START_STOP_OFFSET);

    if (FAN_START == new_state && !FAN_READ_BIT(FAN_BITS_START_STOP_OFFSET))
        return FAN_FAILED;
    
    if (FAN_STOP == new_state && FAN_READ_BIT(FAN_BITS_START_STOP_OFFSET))
        return FAN_FAILED;
    
    return FAN_SUCCESS;
}

fan_action_response_type fan_set_direction(fan_direction_type new_direction)
{
    FAN = new_direction == FAN_DIRECTION_CLOCKWISE ? FAN_RESET_BIT(FAN_BITS_DIRECTION_OFFSET) : FAN_SET_BIT(FAN_BITS_DIRECTION_OFFSET);

    if (FAN_DIRECTION_CLOCKWISE == new_direction && FAN_READ_BIT(FAN_BITS_DIRECTION_OFFSET))
        return FAN_FAILED;
    else if (FAN_DIRECTION_COUNTERCLOCKWISE == new_direction && !FAN_READ_BIT(FAN_BITS_DIRECTION_OFFSET))
        return FAN_FAILED;
    
    return FAN_SUCCESS;
}

fan_action_response_type fan_set_speed(uint8_t new_speed)
{
    if (new_speed > 0x0F)
        return FAN_FAILED;
    
    FAN_WRITE_SPEED(new_speed);

    if (FAN_READ_SPEED != new_speed)
        return FAN_FAILED;
    
    return FAN_SUCCESS;
}

fan_state_type fan_get_state()
{
    return FAN_READ_BIT(FAN_BITS_START_STOP_OFFSET) ? FAN_START : FAN_STOP;
}

fan_direction_type fan_get_direction()
{
    return FAN_READ_BIT(FAN_BITS_DIRECTION_OFFSET) ? FAN_DIRECTION_COUNTERCLOCKWISE : FAN_DIRECTION_CLOCKWISE;
}

uint8_t fan_get_speed()
{
    return FAN_READ_SPEED;
}