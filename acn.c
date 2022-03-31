#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
//#include <sys/socket.h> 
//#include <arpa/inet.h> 
//#include <netinet/in.h> 
#include "acn.h"
#include "PicoPixel.h"

#define ETH_BUFFER_SIZE 1500
#define ACNSDT 5568

static uint8_t   (*net_buffer)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE];
static uint16_t (*net_buffer_ptr)[ETHERNET_BUF_MAX_SLOTS];
static int buffer_slot_ptr;

void acnInit(uint8_t (*nb)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE], uint16_t (*nbp)[ETHERNET_BUF_MAX_SLOTS])
{
   net_buffer = nb;
   net_buffer_ptr = nbp;
   buffer_slot_ptr = 0;
}

// listen for unicast packets
void *acn_listen(void *listen_parameters)
{
    ACNPacket * acn_packet;
    int universe;
    uint8_t sequence;
//    int buffer_offset;
    acnParam *params = listen_parameters;
    char *pixelbuffer = params->buffer;
    uint32_t buffer_offset;
    uint16_t len;

    while((*net_buffer_ptr)[buffer_slot_ptr])
    {
#ifdef _ACN_DEBUG_
        printf("ACN processing slot %d\n\r",buffer_slot_ptr);
#endif        
        acn_packet = (ACNPacket *)(*net_buffer)[buffer_slot_ptr];
        if(!strncmp(acn_packet->RL.ACNPacketIdentifier,ACN_TOKEN,9))
        {
            len = getPropertyCount(acn_packet);
            universe = getUniverse(acn_packet);
            if ((universe >= params->universeStart) && (universe <= params->universeEnd))
            {
                buffer_offset = (universe - params->universeStart) * params->universeSize;
                if (len > params->universeSize)
                {
                    len = params->universeSize;
                }
            memcpy(pixelbuffer + buffer_offset,acn_packet->DMP.Properties.Data,len);   
#ifdef _ACN_DEBUG_
    printf("Universe %d sequence %i Length %d\n\r",universe,getSequence(data),len);
#endif
            }
        }
        (*net_buffer_ptr)[buffer_slot_ptr++] = 0;  // Mark slot as processed
        if (buffer_slot_ptr == ETHERNET_BUF_MAX_SLOTS)
        {
            buffer_slot_ptr = 0;
        }
    }
}

// Get the universe number and convert to host integer
inline int getUniverse(ACNPacket *Packet)
{
	return (Packet->FL.UniverseH<<8)+Packet->FL.UniverseL;
}

// Get the number of data bytes and convert to host integer
inline int getPropertyCount(ACNPacket *Packet)
{
	return(Packet->DMP.Properties.PropertyCountH<<8)+Packet->DMP.Properties.PropertyCountL -1;
}

inline uint8_t getSequence(ACNPacket *Packet)
{
    return(Packet->FL.Sequence);
}
