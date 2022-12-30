#ifndef __NETWORKMANAGER_H
#define __NETWORKMANAGER_H

#include <stdint.h>
#include "PicoPixel.h"

#define ZCPP_PORT 30005

/* DATA_BUF_SIZE define */
#ifndef DATA_BUF_SIZE
	#define DATA_BUF_SIZE			2048
#endif

void listenerInit(uint8_t sn,uint16_t listen_port,uint8_t (*nb)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE], uint16_t (*nbp)[ETHERNET_BUF_MAX_SLOTS]);
int32_t listenerWork(uint8_t sn);
void networkWorker(void);

#endif