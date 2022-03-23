#include "fan_control_protocol.h"
#include "simulated_register_area.h"
#include "fan_driver.h"
#include "stdio.h"

#define TRUE 1
#define FALSE 0

static uint8_t initSuccessfully = FALSE;

static int validate_direction(uint8_t direction);
static int validate_speed(uint8_t speed);
static uint8_t convert_speed(uint8_t speed);

int8_t fan_control_init()
{
    int8_t ret;

    ret = init_simulated_register_area();
    if (ret == 0)
    {
        initSuccessfully = TRUE;
    }

    return ret;
}

int fan_control_process_message(uint8_t bufferLength, uint8_t* buffer)
{
    int ret_code = FAN_API_SUCCESS;

    if (initSuccessfully != TRUE)
    {
        printf("Library was not initialized!");
        return FAN_API_NOT_READY;
    }

    if (!buffer)
        return FAN_API_BAD_PARAM;

    if (bufferLength < 1 || bufferLength > 3) // length should be [1:3]
        return FAN_API_BAD_FRAME;
    
    switch (buffer[0])
    {
        case 0x01:
        {
            if (FAN_SUCCESS != fan_start_stop(FAN_START))
                ret_code = FAN_API_COMMAND_FAILED;
            break;
        }

        case 0x02:
        {
            if (FAN_SUCCESS != fan_start_stop(FAN_STOP))
                ret_code = FAN_API_COMMAND_FAILED;
            break;
        }

        case 0x03:
        {
            if (bufferLength != 3)
                ret_code = FAN_API_BAD_FRAME;
            else if (validate_direction(buffer[1]) != 0)
                ret_code = FAN_API_DIRECTION_OUT_OF_RANGE;
            else if (validate_speed(buffer[2] != 0))
                ret_code = FAN_API_SPEED_OUT_OF_RANGE;
            else
            {
                fan_direction_type direction = buffer[1] == 0 ? FAN_DIRECTION_CLOCKWISE : FAN_DIRECTION_COUNTERCLOCKWISE;
                uint8_t speed = convert_speed(buffer[2]);

                if (FAN_SUCCESS != fan_set_direction(direction))
                    ret_code = FAN_API_COMMAND_FAILED;
                else if (FAN_SUCCESS != fan_set_speed(speed))
                    ret_code = FAN_API_COMMAND_FAILED;
            }
            break;
        }

        // do nothing for reserved values
        default:
            break;
    }

    return ret_code;
}

uint8_t fan_control_get_register()
{
    if (initSuccessfully != TRUE)
    {
        printf("Library was not initialized!");
        return FAN_API_NOT_READY;
    }

    return FAN;
}

static int validate_direction(uint8_t direction)
{
    return direction == 0 || direction == 1 ? 0 : -1;
}

static int validate_speed(uint8_t speed)
{
    return speed >= 1 && speed <=16 ? 0 : -1;
}

static uint8_t convert_speed(uint8_t speed)
{
    return speed -1;
}