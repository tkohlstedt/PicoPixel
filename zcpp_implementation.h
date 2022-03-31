#ifndef __ZCPP_IMPLEMENTATION_H__
#define __ZCPP_IMPLEMENTATION_H__
#include "PicoPixel.h"

typedef struct _zcppParam
{
    int universeStart;
    int universeEnd;
    char controller_name[32];
    char *buffer;
    thread_ctrl *hwconfig;
} zcppParam;

void zcppInit(uint8_t (*nb)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE], uint16_t (*nbp)[ETHERNET_BUF_MAX_SLOTS]);
void *zcpp_multicast_listen(void *listen_parameters);
void *zcpp_listen(void *listen_parameters);

#endif