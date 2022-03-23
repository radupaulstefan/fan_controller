#ifndef SIMULATED_REGISTER_AREA_H
#define SIMULATED_REGISTER_AREA_H

/**
 * File to simulate registers memory. To be closer to a real life scenario we will simulate registers addresses
 * as a memory area in heap memory.
 * simulated_register_map will be the beginning of this area. Further, the fact that this is never null
 * will be considered as true. So make sure we are always calling init_simulated_registers_area as a first thing at startup.
 */


#include "stdint.h"

extern uint8_t *simulated_register_map; //!< never access this before calling init_simulated_registers_area

/**
 * Always call this at startup.
 */
int8_t init_simulated_register_area();


#endif // SIMULATED_REGISTER_AREA_H