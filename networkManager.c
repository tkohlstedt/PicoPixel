
#include "networkManager.h"
#include "PicoPixel.h"
#include <stdio.h>
#include <string.h>
#include "wizchip_conf.h"
#include "socket.h"
#include "port_common.h"
#include "ZCPP.h"
#include "acn.h"
#include "netutil.h"
#include <pico/multicore.h>

static uint16_t listenPort;
static uint8_t sh_sn;
static uint8_t   (*net_buffer)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE];
static uint16_t (*net_buffer_ptr)[ETHERNET_BUF_MAX_SLOTS];
static int buffer_slot_ptr;

void listenerInit(uint8_t sn,uint16_t listen_port,uint8_t (*nb)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE], uint16_t (*nbp)[ETHERNET_BUF_MAX_SLOTS])
{
   listenPort = listen_port;
   sh_sn = sn;
   net_buffer = nb;
   net_buffer_ptr = nbp;
   buffer_slot_ptr = 0;
}

void networkWorker(void)
{
   // call this function to allow the other thread to pause this thread while writing to ROM
#ifdef _NETWORK_DEBUG_
               printf("Starting multicore_lockout_victim_init\r\n");
#endif   
   multicore_lockout_victim_init();
   while (1)
   {
      listenerWork(sh_sn);
//      sleep_ms(5);
   }
}

int32_t listenerWork(uint8_t sn)
{
   int32_t  ret;
   uint16_t size, sentsize, remainingsize;
   uint8_t  destip[4];
   uint16_t destport;
   ZCPP_packet_t *zcpp_packet;
   ACNPacket *acn_packet;

   switch(getSn_SR(sn))
   {
      case SOCK_UDP :
         while( (size = getSn_RX_RSR(sn)) > 0)
         {
            if(size > ETHERNET_BUF_MAX_SIZE) size = ETHERNET_BUF_MAX_SIZE;
            ret = recvfrom(sn, (*net_buffer)[buffer_slot_ptr], size, destip, (uint16_t*)&listenPort);
            if(ret <= 0)
            {
#ifdef _NETWORK_DEBUG_
               printf("%d: recvfrom error. %ld\r\n",sn,ret);
#endif
               return ret;
            }
            zcpp_packet = (ZCPP_packet_t *)(*net_buffer)[buffer_slot_ptr];
            acn_packet = (ACNPacket *)(*net_buffer)[buffer_slot_ptr];
#ifdef _NETWORK_DEBUG_
            if(!strncmp(zcpp_packet->Data.Header.token,ZCPP_token,4))
               printf("Received %ld bytes frame %i offset %i data len %i slot %d\n\r",ret,zcpp_packet->Data.sequenceNumber ,
                  ntohl(zcpp_packet->Data.frameAddress),ntohs(zcpp_packet->Data.packetDataLength),buffer_slot_ptr);
            if(!strcmp(acn_packet->RL.ACNPacketIdentifier,ACN_TOKEN))
               printf("Received %ld bytes universe %i sequence %i slot %d\n\r",ret,
                  getUniverse(acn_packet),getSequence(acn_packet),buffer_slot_ptr);
#endif      
            (*net_buffer_ptr)[buffer_slot_ptr++] = size;
            if (buffer_slot_ptr == ETHERNET_BUF_MAX_SLOTS)
               buffer_slot_ptr = 0;
         }
         break;
      case SOCK_CLOSED:
#ifdef _NETWORK_DEBUG_
         //printf("%d:UDP loopback start\r\n",sn);
#endif
         if((ret = socket(sn, Sn_MR_UDP, listenPort, 0x00)) != sn)
            return ret;
#ifdef _NETWORK_DEBUG_
         printf("%d:Opened, UDP loopback, port [%d]\r\n", sn, listenPort);
#endif
         break;
      default :
         break;
   }
   return 1;
   
}