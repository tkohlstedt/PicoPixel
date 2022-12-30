/**
 * @file	userHandler.h
 * @brief	Header File for User Control Example
 * @version 1.0
 * @date	2014/07/15
 * @par Revision
 *			2014/07/15 - 1.0 Release
 * @author	
 * \n\n @par Copyright (C) 1998 - 2014 WIZnet. All rights reserved.
 */

#ifndef __USERHANDLER_H
#define __USERHANDLER_H

#include <stdint.h>
//#include "types.h"
#include "wizchip_conf.h"

//#define RESET_W5500		GPIO_Pin_0	//out
#define INT_W5500		GPIO_Pin_1	//in


// Digital I/O
#define DATA_0			GPIO_Pin_0	// inout
#define DATA_1			GPIO_Pin_1	// inout
#define DATA_2			GPIO_Pin_2	// inout
#define DATA_3			GPIO_Pin_3	// inout
#define DATA_4			GPIO_Pin_4	// inout
#define DATA_5			GPIO_Pin_15	// inout
#define DATA_6			GPIO_Pin_10	// inout
#define DATA_7			GPIO_Pin_11	// inout
#define DATA_8			GPIO_Pin_5	// inout
#define DATA_9			GPIO_Pin_2	// inout
#define DATA_10			GPIO_Pin_3	// inout
#define DATA_11			GPIO_Pin_4	// inout
#define DATA_12			GPIO_Pin_5	// inout
#define DATA_13			GPIO_Pin_6	// inout
#define DATA_14			GPIO_Pin_7	// inout
#define DATA_15			GPIO_Pin_8	// inout


//Data IO
typedef enum
{
  D0 = 0,
  D1 = 1,
  D2 = 2,
  D3 = 3,
  D4 = 4,
  D5 = 5,
  D6 = 6,
  D7 = 7,
  D8 = 8,
  D9 = 9,
  D10 = 10,
  D11 = 11,
  D12 = 12,
  D13 = 13,
  D14 = 14,
  D15 = 15
} IO_Type;

enum net_state {
	net_disconnect = 0,
	net_connect = 1,
	net_udp = 2
};

// End of Extra defines

//#define _WEB_DEBUG_

#define MAX_ALIAS_SIZE			25


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pre-defined CGI Interface Functions Handler
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t predefined_get_cgi_processor(uint8_t * uri_name, uint8_t * buf, uint16_t * len);
uint8_t predefined_set_cgi_processor(uint8_t * uri_name, uint8_t * uri, uint8_t * buf, uint16_t * len);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HTTP GET Method CGI Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void make_basic_config_setting_json_callback(uint8_t * buf, uint16_t * len);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HTTP POST Method CGI Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void make_cgi_basic_config_response_page(uint16_t delay, uint8_t * url, uint8_t * cgi_response_buf, uint16_t * len);
uint8_t * set_basic_config_setting(uint8_t * uri);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Custom Command Handler Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define _CUSTOM_COMMAND_DEBUG_

#define NO_CUSTOM_COMMAND		0
#define COMMAND_SUCCESS			1
#define COMMAND_ERROR			2

uint8_t custom_command_handler(uint8_t * buf);

#endif