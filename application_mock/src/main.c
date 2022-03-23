#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "stdint.h"

#include "wireless_receiver.h"

int main()
{
    wireless_receiver_start_receive();

    while(1) {}

    return 0;
}