#ifndef REGISTERS_H
#define REGISTERS_H

#include "simulated_register_area.h"

#define FAN (*(volatile uint8_t *)(simulated_register_map + 0x0F)) // let's suppose FAN is the 16th register in this map
/**
 * It's volatile because we want to prevent any compiler optimisations here so variabile will be read
 * every time we acces it during the executing
 */ 

#endif // REGISTERS_H