#include <stdlib.h>

#include "simulated_register_area.h"

uint8_t *simulated_register_map = NULL;

int8_t init_simulated_register_area()
{
    simulated_register_map = (uint8_t *)malloc(128);

    if (!simulated_register_map)
        return -1;
    
    return 0;
}