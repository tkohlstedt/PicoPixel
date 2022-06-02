/**
 * Copyright (c) 2021 WIZnet Co.,Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
  * ----------------------------------------------------------------------------------------------------
  * Includes
  * ----------------------------------------------------------------------------------------------------
  */
#include <stdio.h>
#include <string.h>

#include "port_common.h"

#include "wizchip_conf.h"
#include "w5x00_spi.h"
#include "dhcp.h"

#include "httpServer.h"
#include "userHandler.h"
#include "web_page.h"
#include "jscolor_js.h"
#include "PicoPixel.h"
#include "networkManager.h"
#include "zcpp_implementation.h"
#include "acn.h"
#include "outputManager.h"
#include "eepromManager.h"
#include "effects.h"

#include <pico/multicore.h>
#include <pico/unique_id.h>
#include <stdlib.h>

/**
  * ----------------------------------------------------------------------------------------------------
  * Variables
  * ----------------------------------------------------------------------------------------------------
  */
/* Network */
static wiz_NetInfo g_net_info =
    {
        .mac = {0x00, 0x08, 0xDC, 0x00, 0x00, 0x00}, // MAC address  00:08:DC is Wiznet OUI
        .ip = {192, 168, 8, 30},                     // IP address
        .sn = {255, 255, 255, 0},                    // Subnet Mask
        .gw = {192, 168, 8, 254},                     // Gateway
        .dns = {192, 168, 8, 2},                         // DNS server
//        .dhcp = NETINFO_STATIC                       // DHCP enable/disable
        .dhcp = NETINFO_DHCP
};

#define DHCP_SOCKET 2
#define DATA_SOCKET 3

////////////////
// DHCP client//
////////////////
#define MY_MAX_DHCP_RETRY			2
uint8_t my_dhcp_retry = 0;
bool run_user_applications;
char hostname[32];
repeating_timer_t dhcp_timer;


/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void Net_Conf();
static void Display_Net_Conf();
static void PHYStatus_Check(void);
// Callback function : User defined DHCP functions
void my_ip_assign(void);
void my_ip_conflict(void);


/* HTTP */
static uint8_t g_http_send_buf[ETHERNET_BUF_MAX_SIZE] = {
    0,
};
static uint8_t g_http_recv_buf[ETHERNET_BUF_MAX_SIZE] = {
    0,
};
static uint8_t g_http_socket_num_list[HTTP_SOCKET_MAX_NUM] = {0, 1};

/* Network buffers */
static uint8_t data_socket_num = DATA_SOCKET;
//static uint8_t data_recv_buffer[ETHERNET_BUF_MAX_SIZE] = {0};
//static uint8_t data_send_buffer[ETHERNET_BUF_MAX_SIZE] = {0};

static uint8_t network_buffer[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE];
static uint16_t network_buffer_ptr[ETHERNET_BUF_MAX_SLOTS];
static char dhcp_buf[1024];

/* ZCPP */
zcppParam zcpp_listen_param;
acnParam acn_listen_param;
static thread_ctrl hwconfig;
int universe_start,universe_count,universe_size;
int pixel_port_count;
char *pixelBuffer;

static uint32_t timer_triggered;

pico_unique_board_id_t  board_id;

/**
  * ----------------------------------------------------------------------------------------------------
  * Main
  * ----------------------------------------------------------------------------------------------------
  */
int main()
{
    /* Initialize */
    uint8_t i = 0;
    uint32_t ret = 0;

    stdio_init_all();

    /* wait a few seconds for serial connection */
    sleep_ms(5000);

    // set the mac address by using the last 3 bytes of the pico board id
    pico_get_unique_board_id (&board_id);
    g_net_info.mac[3] = board_id.id[5];
    g_net_info.mac[4] = board_id.id[6];
    g_net_info.mac[5] = board_id.id[7];

    CFG_Packet * dev_config = get_CFG_Packet_pointer();

    // set network configuration from stored config
    get_CFG_Packet_value(&g_net_info.ip,dev_config->network_info_common.local_ip,4);
    get_CFG_Packet_value(&g_net_info.sn,dev_config->network_info_common.subnet,4);
    get_CFG_Packet_value(&g_net_info.gw,dev_config->network_info_common.gateway,4);
    get_CFG_Packet_value(&g_net_info.dns,dev_config->options.dns_server_ip,4);
    get_CFG_Packet_value(&g_net_info.dhcp,&dev_config->options.dhcp_use,1);
    g_net_info.dhcp++; // dhcp usage is stored as 0=static,1=dhcp
                       // Wiznet macros use 1=static, 2=dhcp
    memset(hostname,'\0',sizeof(hostname));
    get_CFG_Packet_value(hostname,dev_config->module_name,25);

//    g_net_info.dhcp = NETINFO_DHCP;

    // initialize network hardware
    wizchip_spi_initialize();
    wizchip_cris_initialize();

    wizchip_reset();
    wizchip_initialize();
    wizchip_check();

    // set network speed to 10mbs  
    // 100mbs will overrun the buffers if there is more than about 5K channels/frame
    wiz_PhyConf phyconfig;
    phyconfig.by = PHY_CONFBY_SW;
    phyconfig.duplex = PHY_DUPLEX_FULL;
    phyconfig.mode = PHY_MODE_MANUAL;
    phyconfig.speed = PHY_SPEED_10;

    if (ctlwizchip(CW_SET_PHYCONF, (void *)&phyconfig) == -1)
    {
      printf(" W5x00 PHY config failed\n");
    }

    // bring up the network
    network_initialize(g_net_info);

    // set the receive buffer sizes by socket
    // allocate as much as possible to the data socket
#if _WIZCHIP_ == W5100S
    uint8_t memsize[2][4] = {{2, 2, 2, 2}, {2, 1, 1, 4}};
#elif _WIZCHIP_ == W5500
    uint8_t memsize[2][8] = {{2, 2, 2, 2, 2, 2, 2, 2}, {2, 1, 1, 8, 1, 1, 1, 1}};
#endif
    if (ctlwizchip(CW_INIT_WIZCHIP, (void *)memsize) == -1)
    {
        printf(" W5x00 buffer initialized fail\n");
    }

	/* DHCP client Initialization */
	if(g_net_info.dhcp == NETINFO_DHCP)
	{
		DHCP_init(DHCP_SOCKET, dhcp_buf,hostname);
		// if you want different action instead default ip assign, update, conflict.
		// if cbfunc == 0, act as default.
		reg_dhcp_cbfunc(my_ip_assign, my_ip_assign, my_ip_conflict);
    // need a 1 second timer callback
		add_repeating_timer_ms(1000,(repeating_timer_callback_t)DHCP_time_handler,NULL,&dhcp_timer);
    // don't start processing until an IP address is assigned
		run_user_applications = false; 	
	} else
  {
    run_user_applications = true;
  }

    // start the webserver
    httpServer_init(g_http_send_buf, g_http_recv_buf, HTTP_SOCKET_MAX_NUM, g_http_socket_num_list);

    /* Register web page */
	  reg_httpServer_webContent((uint8_t *)"index.html", (uint8_t *)index_page);				// index.html 		: Main page example
    reg_httpServer_webContent((uint8_t *)"jscolor.js", (uint8_t *)jscolor_script);


    /* wait a few seconds for serial connection */
    sleep_ms(5000);

#ifdef _MAIN_DEBUG_
		display_reg_webContent_list();
#endif

    /* Get network information */
    print_network_information(g_net_info);

    /* Set config */
    
    universe_start = dev_config->proto.universe;
    universe_count = MAX_UNIVERSES;
    universe_size = dev_config->proto.usize;
    pixel_port_count = PIXEL_PORTS;

    hwconfig.run_mode = MODE_RUN;

    // allocate and clear the pixelbuffer
    pixelBuffer = malloc(PIXEL_BUFFER_SIZE);
    memset(pixelBuffer,0,PIXEL_BUFFER_SIZE);

    // clear the hw config
    memset((void *)&hwconfig,0,sizeof(thread_ctrl));
    hwconfig.buffer = pixelBuffer;
    hwconfig.pixel_ports = PIXEL_PORTS;
    // set the channel config from saved config
    for(int a = 0;a<PIXEL_PORTS;a++)
    {
      hwconfig.led_string[a].channel_count[0] = dev_config->io.channel_count[a];
      hwconfig.led_string[a].brightness[0] = 100;
      hwconfig.led_string[a].start_channel[0] = dev_config->io.start_channel[a];
    }

    if(dev_config->proto.protocol == 0)  // ZCPP protocol
    {
      // setup the universes to listen for
      zcpp_listen_param.universeStart = universe_start;
      zcpp_listen_param.universeEnd = universe_start + universe_count - 1;
      zcpp_listen_param.buffer = pixelBuffer;
      zcpp_listen_param.hwconfig = &hwconfig;
      strcpy(zcpp_listen_param.controller_name, dev_config->module_name);


      listenerInit(data_socket_num,ZCPP_PORT,(uint8_t (*)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE])&network_buffer,(uint16_t (*)[ETHERNET_BUF_MAX_SLOTS])&network_buffer_ptr); // assign socket 3
      zcppInit((uint8_t (*)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE])&network_buffer,(uint16_t (*)[ETHERNET_BUF_MAX_SLOTS])&network_buffer_ptr); 
    }
    else  // ACN E1.31
    {
      acn_listen_param.universeStart = universe_start;
      acn_listen_param.universeEnd = universe_start + universe_count -1;
      acn_listen_param.universeSize = universe_size;
      acn_listen_param.buffer = pixelBuffer;
      acn_listen_param.hwconfig = &hwconfig;
      strcpy(acn_listen_param.controller_name, dev_config->module_name);

      listenerInit(data_socket_num,ACN_PORT,(uint8_t (*)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE])&network_buffer,(uint16_t (*)[ETHERNET_BUF_MAX_SLOTS])&network_buffer_ptr); // assign socket 3
      acnInit((uint8_t (*)[ETHERNET_BUF_MAX_SLOTS][ETHERNET_BUF_MAX_SIZE])&network_buffer,(uint16_t (*)[ETHERNET_BUF_MAX_SLOTS])&network_buffer_ptr); 
    }

    // Start the network listener thread on core 1
    multicore_launch_core1(networkWorker);

    // Initialize the output drivers
    outputInit(&hwconfig);
    
    // schedule the output driver
    // refresh every 50 ms
    struct repeating_timer timer;
    add_repeating_timer_ms(50,(repeating_timer_callback_t)outputWork,NULL,&timer);

    //Initialize the test mode
    test_init(&hwconfig);


    /* Infinite loop */
    while (1)
    {
   	if(g_net_info.dhcp == NETINFO_DHCP)
    	{
        switch(DHCP_run())
        {
          case DHCP_IP_ASSIGN:
          case DHCP_IP_CHANGED:
            print_network_information(g_net_info);
            break;
          case DHCP_IP_LEASED:
            run_user_applications = true;
            break;
          case DHCP_FAILED:
            break;
          default:
            break;
        }
    	}
    if(run_user_applications)
      {
        /* Run HTTP server */
        for (i = 0; i < HTTP_SOCKET_MAX_NUM; i++)
        {
            httpServer_run(i);
        }
        if(dev_config->proto.protocol == 0)  // ZCPP protocol
        {
            zcpp_listen(&zcpp_listen_param);
        } else
        {
            acn_listen(&acn_listen_param);
        }
        if(hwconfig.run_mode == MODE_TEST)
        {
          test_run();
        }
      }
    }
}

//
// Return a pointer to the running config
//
thread_ctrl *get_running_config()
{
  return &hwconfig;
}
//
// Set the global run/test mode
//
void set_run_mode(uint8_t mode)
{
  hwconfig.run_mode = mode;
}
//
// Return the global run/test mode
// 0=Run,1=Test
//
uint8_t get_run_mode()
{
  return hwconfig.run_mode;
}

static void Net_Conf()
{
	/* wizchip netconf */
	ctlnetwork(CN_SET_NETINFO, (void*) &g_net_info);
}

void my_ip_assign(void)
{
   getIPfromDHCP(g_net_info.ip);
   getGWfromDHCP(g_net_info.gw);
   getSNfromDHCP(g_net_info.sn);
   getDNSfromDHCP(g_net_info.dns);
   g_net_info.dhcp = NETINFO_DHCP;
   /* Network initialization */
   Net_Conf();      // apply from DHCP
#ifdef _MAIN_DEBUG_
   print_network_information(g_net_info);
   printf("DHCP LEASED TIME : %ld Sec.\r\n", getDHCPLeasetime());
   printf("\r\n");
#endif
}
/************************************
 * @ brief Call back for ip Conflict
 ************************************/
void my_ip_conflict(void)
{
#ifdef _MAIN_DEBUG_
	printf("CONFLICT IP from DHCP\r\n");
#endif
   //halt or reset or any...
   while(1); // this example is halt.
}