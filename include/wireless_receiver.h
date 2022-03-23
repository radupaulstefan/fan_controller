#ifndef WIRELESS_RECEIVER_H
#define WIRELESS_RECEIVER_H

#include <pthread.h>

/**
 * Send the thread id as parameter for caller to be aware that
 * the interface will do thread operations, which is starting in this situations.
 */

void wireless_receiver_start_receive(pthread_t* id);

#endif // WIRELESS_RECEIVER_H