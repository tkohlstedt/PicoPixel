#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
//#include <sys/socket.h> 
//#include <arpa/inet.h> 
#include "netutil.h" 
#include "PicoPixel.h"
#include "ZCPP.h"
#include "zcpp_implementation.h"

int last_config_sequence = 0;

static uint8_t   (*net_buffer)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE];
static uint16_t (*net_buffer_ptr)[ETHERNET_BUF_MAX_SLOTS];
static int buffer_slot_ptr;


void zcpp_send_discovery_response(ZCPP_packet_t *data, char *controller_name)
{
    int sockfd, n;
      
    // connect to server
    // find our local ip
    
    ZCPP_DiscoveryResponse *response_packet;
    response_packet = malloc(sizeof(ZCPP_DiscoveryResponse));
    memset(response_packet,0,sizeof(ZCPP_DiscoveryResponse));
    memcpy(response_packet->Header.token,ZCPP_token,sizeof(ZCPP_token));
    response_packet->Header.type = ZCPP_TYPE_DISCOVERY_RESPONSE;
    response_packet->Header.protocolVersion = ZCPP_CURRENT_PROTOCOL_VERSION;
    response_packet->minProtocolVersion = ZCPP_CURRENT_PROTOCOL_VERSION;
    response_packet->maxProtocolVersion = ZCPP_CURRENT_PROTOCOL_VERSION;
    response_packet->vendor = htons(ZCPP_VENDOR_FALCON);
    response_packet->model = htons(0x0001);
    response_packet->macAddress[0] = 0xA0;
    response_packet->macAddress[1] = 0xFF;
    response_packet->macAddress[2] = 0xFF;
    response_packet->ipv4Address = htonl(0xC0A8087D); //need to fix this
    response_packet->ipv4Mask = htonl(0xFFFFFF00); //need to fix this
    strcpy(response_packet->userControllerName,controller_name);
    response_packet->maxTotalChannels = htons(4800);
    response_packet->pixelPorts = 4;
    response_packet->rsPorts = 0;
    response_packet->channelsPerPixelPort = htons(3600);
    response_packet->channelsPerRSPort = htons(0);
    response_packet->flags = htons(ZCPP_DISCOVERY_FLAG_SUPPORTS_VIRTUAL_STRINGS);
    response_packet->protocolsSupported = htonl(ZCPP_DISCOVERY_PROTOCOL_WS2811);

printf("My ip %i \n\r",response_packet->ipv4Address);

    // request to send datagram
//    sendto(sockfd, response_packet, sizeof(ZCPP_DiscoveryResponse), 0, (struct sockaddr*)NULL, sizeof(servaddr));
  
    // close the descriptor

}

void zcpp_process_config(ZCPP_packet_t *data,thread_ctrl *hwconfig)
{
    printf("Recieved config packet %i\n\r",ntohs(data->Configuration.sequenceNumber));
    printf("Config count %i\n\r",data->Configuration.ports);
    // Clear out existing channel mappings
    if(last_config_sequence != ntohs(data->Configuration.sequenceNumber))
    {
        last_config_sequence = ntohs(data->Configuration.sequenceNumber);
        for(int p = 0;p<PIXEL_PORTS;p++){
            for(int s = 0;s<8;s++){
                hwconfig->led_string[p].channel_count[s] = 0;
                hwconfig->led_string[p].start_channel[s] = 0;
                hwconfig->led_string[p].brightness[s] = 100;
                hwconfig->led_string[p].gamma[s] = 1;
                hwconfig->led_string[p].null_pixels[s] = 0;
                hwconfig->led_string[p].color_order[s] = 0;
                hwconfig->led_string[p].direction[s] = 0;
            }
        }
    }
    // Set new channel mappings based on config packet
    for(int a =0;a<data->Configuration.ports;a++)
    {
        printf("Port : %i Channels: %lu  Protocol: %i String: %i Start Channel: %lu Brightness: %i Gamma: %i\n\r",data->Configuration.PortConfig[a].port,ntohl(data->Configuration.PortConfig[a].channels),
        data->Configuration.PortConfig[a].protocol,data->Configuration.PortConfig[a].string,
        ntohl(data->Configuration.PortConfig[a].startChannel),data->Configuration.PortConfig[a].brightness,
        data->Configuration.PortConfig[a].gamma);

        hwconfig->led_string[data->Configuration.PortConfig[a].port].channel_count[data->Configuration.PortConfig[a].string] = ntohl(data->Configuration.PortConfig[a].channels);
        hwconfig->led_string[data->Configuration.PortConfig[a].port].start_channel[data->Configuration.PortConfig[a].string] = ntohl(data->Configuration.PortConfig[a].startChannel);
        hwconfig->led_string[data->Configuration.PortConfig[a].port].brightness[data->Configuration.PortConfig[a].string] = data->Configuration.PortConfig[a].brightness;
        hwconfig->led_string[data->Configuration.PortConfig[a].port].gamma[data->Configuration.PortConfig[a].string] = data->Configuration.PortConfig[a].gamma;
        hwconfig->led_string[data->Configuration.PortConfig[a].port].null_pixels[data->Configuration.PortConfig[a].string] = data->Configuration.PortConfig[a].nullPixels;
        hwconfig->led_string[data->Configuration.PortConfig[a].port].color_order[data->Configuration.PortConfig[a].string] = data->Configuration.PortConfig[a].directionColourOrder & 7;
        hwconfig->led_string[data->Configuration.PortConfig[a].port].direction[data->Configuration.PortConfig[a].string] = data->Configuration.PortConfig[a].directionColourOrder & 128;
    }
}

void zcpp_process_extra_data(ZCPP_packet_t *data)
{

}
void zcpp_send_config_response(ZCPP_packet_t *data)
{
    printf("recieved config request\n\r");
}

void zcpp_process_data(ZCPP_packet_t *data, char *pixelbuffer)
{
    uint32_t buffer_offset;
    uint16_t len;

    buffer_offset = ntohl(data->Data.frameAddress);
    len = ntohs(data->Data.packetDataLength);
    memcpy(pixelbuffer + buffer_offset,data->Data.data,len);   
#ifdef _ZCPP_DEBUG_
    printf("Frame %d Offset %i Length %d\n\r",data->Data.sequenceNumber,buffer_offset,len);
#endif
}

void zcpp_process_sync(ZCPP_packet_t *data)
{

}

void zcppInit(uint8_t (*nb)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE], uint16_t (*nbp)[ETHERNET_BUF_MAX_SLOTS])
{
   net_buffer = nb;
   net_buffer_ptr = nbp;
   buffer_slot_ptr = 0;
}

// listen for unicast packets
void *zcpp_listen(void *listen_parameters)
{
    ZCPP_packet_t *zcpp_packet;
    int universe;
    uint8_t sequence;
    int buffer_offset;
    zcppParam *params = listen_parameters;
    char *pixelbuffer = params->buffer;
    uint8_t run_mode;
    
    run_mode = params->hwconfig->run_mode;

    while((*net_buffer_ptr)[buffer_slot_ptr])
    {
#ifdef _ZCPP_DEBUG_
        printf("ZCPP processing slot %d\n\r",buffer_slot_ptr);
#endif        
        zcpp_packet = (ZCPP_packet_t*)(*net_buffer)[buffer_slot_ptr];
        if(!strncmp(zcpp_packet->Data.Header.token,ZCPP_token,4) && (run_mode == MODE_RUN))
        {
            switch (zcpp_packet->Discovery.Header.type)
            {
                case ZCPP_TYPE_DISCOVERY:
                    zcpp_send_discovery_response(zcpp_packet,(char *)((zcppParam*)params->controller_name));
                    break;
                case ZCPP_TYPE_CONFIG:
                    zcpp_process_config(zcpp_packet,(thread_ctrl*)((zcppParam*)params->hwconfig));
                    break;
                case ZCPP_TYPE_EXTRA_DATA:
                    zcpp_process_extra_data(zcpp_packet);
                    break;
                case ZCPP_TYPE_QUERY_CONFIG:
                    zcpp_send_config_response(zcpp_packet);
                    break;
                case ZCPP_TYPE_DATA:
                    zcpp_process_data(zcpp_packet,pixelbuffer);
                    break;
                case ZCPP_TYPE_SYNC:
                    zcpp_process_sync(zcpp_packet);
                    break;
            }
        }
        (*net_buffer_ptr)[buffer_slot_ptr++] = 0;  // Mark slot as processed
        if (buffer_slot_ptr == ETHERNET_BUF_MAX_SLOTS)
        {
            buffer_slot_ptr = 0;
        }
    }
}
