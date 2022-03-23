#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "simulated_register_area.h"
#include "registers.h"
#include "fan_driver.h"
#include "fan_control_protocol.h"
#include "wireless_receiver.h"

void printByte(uint8_t byte)
{
    printf("0b");
    for (int i = 0; i < 8; i++)
        printf("%d", (byte & (1 << (7-i))) >> (7-i));
    
    printf("\n");
}

int main()
{
    pthread_t wireless_receiver_thread_id;

    if (init_simulated_register_area())
    {
        perror("Simulated registers failed to init");
        exit(EXIT_FAILURE);
    }

    wireless_receiver_start_receive(&wireless_receiver_thread_id);

    while(1) {}

    return 0;
}