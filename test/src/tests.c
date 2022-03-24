#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>
#include "fan_control_protocol.h"

static void test(void **state)
{
    uint8_t buffer[3] = {3, 2, 0};
    int ret = FAN_API_BAD_FRAME;
    
    assert_int_equal(fan_control_process_message(1, buffer), FAN_API_NOT_READY);

    fan_control_init();

    assert_int_equal(fan_control_process_message(1, NULL), FAN_API_BAD_PARAM);
    assert_int_equal(fan_control_process_message(4, buffer), FAN_API_BAD_FRAME);
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_DIRECTION_OUT_OF_RANGE);

    buffer[0] = 0x03;
    buffer[1] = 0x01;
    buffer[2] = 0x00;
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_SPEED_OUT_OF_RANGE);
    
    buffer[0] = 0x03;
    buffer[1] = 0x01;
    buffer[2] = 0xF2;
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_SPEED_OUT_OF_RANGE);

    buffer[0] = 0x03;
    buffer[1] = 0x01;
    buffer[2] = 0xF2;
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_SPEED_OUT_OF_RANGE);

    buffer[0] = 0x03;
    buffer[1] = 0x00;
    buffer[2] = 0x01;
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_SUCCESS);
    assert_int_equal(fan_control_get_register(), 0b00000000);

    buffer[0] = 0x01;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    assert_int_equal(fan_control_process_message(1, buffer), FAN_API_SUCCESS);
    assert_int_equal(fan_control_get_register(), 0b00000001);

    buffer[0] = 0x02;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    assert_int_equal(fan_control_process_message(1, buffer), FAN_API_SUCCESS);
    assert_int_equal(fan_control_get_register(), 0b00000000);

    buffer[0] = 0x01;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    assert_int_equal(fan_control_process_message(1, buffer), FAN_API_SUCCESS);
    assert_int_equal(fan_control_get_register(), 0b00000001);

    buffer[0] = 0x03;
    buffer[1] = 0x01;
    buffer[2] = 0x01;
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_SUCCESS);
    assert_int_equal(fan_control_get_register(), 0b00000011);

    buffer[0] = 0x03;
    buffer[1] = 0x00;
    buffer[2] = 0x01;
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_SUCCESS);
    assert_int_equal(fan_control_get_register(), 0b00000001);

    buffer[0] = 0x03;
    buffer[1] = 0x00;
    buffer[2] = 0x02;
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_SUCCESS);
    assert_int_equal(fan_control_get_register(), 0b00010001);

    buffer[0] = 0x03;
    buffer[1] = 0x01;
    buffer[2] = 0x05;
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_SUCCESS);
    assert_int_equal(fan_control_get_register(), 0b01000011);

    buffer[0] = 0x03;
    buffer[1] = 0x01;
    buffer[2] = 0xFA;
    assert_int_equal(fan_control_process_message(3, buffer), FAN_API_SPEED_OUT_OF_RANGE);
    assert_int_equal(fan_control_get_register(), 0b01000011);
}


int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}