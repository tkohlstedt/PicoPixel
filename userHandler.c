/**
 * @file	userHandler.c
 * @brief	User Control Example
 * @version 1.0
 * @date	2014/07/15
 * @par Revision
 *			2014/07/15 - 1.0 Release
 * @author	
 * \n\n @par Copyright (C) 1998 - 2014 WIZnet. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pico/multicore.h>
#include "userHandler.h"

#include "httpParser.h"
#include "eepromManager.h"
#include "httpserver.h"
#include "PicoPixel.h"

#define __userHandler_debug_

// Pre-defined Get CGI functions
void make_json_devinfo(uint8_t * buf, uint16_t * len);
void make_json_netinfo(uint8_t * buf, uint16_t * len);
void make_basic_config_setting_json_callback(uint8_t * buf, uint16_t * len);

// Pre-defined Set CGI functions
uint8_t set_devinfo(uint8_t * uri);
uint8_t set_netinfo(uint8_t * uri);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HTTP GET Method CGI Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void make_basic_config_setting_json_callback(uint8_t * buf, uint16_t * len)
{
	
	wiz_NetInfo gWIZNETINFO;

	ctlnetwork(CN_GET_NETINFO, (void*) &gWIZNETINFO);
//	set_CFG_Packet(&gWIZNETINFO);

	load_CFG_Packet_from_storage();
	CFG_Packet *value = get_CFG_Packet_pointer();

	*len = sprintf((char *)buf, "BasicSettingCallback({\"ver\":\"%d.%d.%d\",\
                                        \"dname\":\"%s\",\
                                        \"pcode\":\"%d-%d-%d\",\
                                        \"mac\":\"%02X:%02X:%02X:%02X:%02X:%02X\",\
                                        \"dhcp\":\"%d\",\
                                        \"lip\":\"%d.%d.%d.%d\",\
                                        \"gw\":\"%d.%d.%d.%d\",\
                                        \"sub\":\"%d.%d.%d.%d\",\
                                        \"dns\":\"%d.%d.%d.%d\",\
                                        \"smode\":\"%d\",\
                                        \"universe\":\"%d\",\
                                        \"usize\":\"%d\"\
                                        });",
										value->fw_ver[0], value->fw_ver[1], value->fw_ver[2],
                                        value->module_name,
                                        value->module_type[0],value->module_type[1],value->module_type[2],
//                                        value->network_info_common.mac[0],value->network_info_common.mac[1],value->network_info_common.mac[2],value->network_info_common.mac[3],value->network_info_common.mac[4],value->network_info_common.mac[5],
										gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5],
                                        value->options.dhcp_use,
                                        value->network_info_common.local_ip[0],value->network_info_common.local_ip[1],value->network_info_common.local_ip[2],value->network_info_common.local_ip[3],
                                        value->network_info_common.gateway[0],value->network_info_common.gateway[1],value->network_info_common.gateway[2],value->network_info_common.gateway[3],
                                        value->network_info_common.subnet[0],value->network_info_common.subnet[1],value->network_info_common.subnet[2],value->network_info_common.subnet[3],
                                        value->options.dns_server_ip[0],value->options.dns_server_ip[1],value->options.dns_server_ip[2],value->options.dns_server_ip[3],
                                        value->proto.protocol,
										value->proto.universe,
										value->proto.usize
                                        );
}

void make_json_port_config(uint8_t * buf, uint16_t * len)
{
	CFG_Packet * cfg = get_CFG_Packet_pointer();
	*len = sprintf((char *)buf, "PortConfigCallback({\"dir\":[{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"}],\
												 \"start\":[{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"}],\
											  \"channels\":[{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"}]});",
															cfg->io.pin[0], cfg->io.pin[1], cfg->io.pin[2], cfg->io.pin[3],
															cfg->io.pin[4], cfg->io.pin[5], cfg->io.pin[6], cfg->io.pin[7],
															cfg->io.pin[8], cfg->io.pin[9], cfg->io.pin[10],cfg->io.pin[11],
															cfg->io.pin[12],cfg->io.pin[13],cfg->io.pin[14],cfg->io.pin[15],
															cfg->io.start_channel[0], cfg->io.start_channel[1], cfg->io.start_channel[2], cfg->io.start_channel[3],
															cfg->io.start_channel[4], cfg->io.start_channel[5], cfg->io.start_channel[6], cfg->io.start_channel[7],
															cfg->io.start_channel[8], cfg->io.start_channel[9], cfg->io.start_channel[10],cfg->io.start_channel[11],
															cfg->io.start_channel[12],cfg->io.start_channel[13],cfg->io.start_channel[14],cfg->io.start_channel[15],
															cfg->io.channel_count[0], cfg->io.channel_count[1], cfg->io.channel_count[2], cfg->io.channel_count[3],
															cfg->io.channel_count[4], cfg->io.channel_count[5], cfg->io.channel_count[6], cfg->io.channel_count[7],
															cfg->io.channel_count[8], cfg->io.channel_count[9], cfg->io.channel_count[10],cfg->io.channel_count[11],
															cfg->io.channel_count[12],cfg->io.channel_count[13],cfg->io.channel_count[14],cfg->io.channel_count[15]
															);
}

void make_json_output_config(uint8_t * buf, uint16_t * len)
{
	CFG_Packet * cfg = get_CFG_Packet_pointer();
	*len = sprintf((char *)buf, "OutputConfigCallback({\"proto\":[{\"p\":\"%d\"},\
															{\"p\":\"%d\"},\
															{\"p\":\"%d\"},\
															{\"p\":\"%d\"},\
															{\"p\":\"%d\"},\
															{\"p\":\"%d\"},\
															{\"p\":\"%d\"},\
															{\"p\":\"%d\"}],\
												   \"pin\":[{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"},\
															{\"v\":\"%d\"}],\
												 \"start\":[{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"},\
															{\"s\":\"%d\"}],\
											  \"channels\":[{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"},\
															{\"a\":\"%d\"}]});",
															cfg->io.protocol[0], cfg->io.protocol[1], cfg->io.protocol[2], cfg->io.protocol[3],
															cfg->io.protocol[4], cfg->io.protocol[5], cfg->io.protocol[6], cfg->io.protocol[7],
															cfg->io.pin[0], cfg->io.pin[1], cfg->io.pin[2], cfg->io.pin[3],
															cfg->io.pin[4], cfg->io.pin[5], cfg->io.pin[6], cfg->io.pin[7],
															cfg->io.start_channel[0], cfg->io.start_channel[1], cfg->io.start_channel[2], cfg->io.start_channel[3],
															cfg->io.start_channel[4], cfg->io.start_channel[5], cfg->io.start_channel[6], cfg->io.start_channel[7],
															cfg->io.channel_count[0], cfg->io.channel_count[1], cfg->io.channel_count[2], cfg->io.channel_count[3],
															cfg->io.channel_count[4], cfg->io.channel_count[5], cfg->io.channel_count[6], cfg->io.channel_count[7]
															);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HTTP POST Method CGI Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t * set_basic_config_setting(uint8_t * uri)
{
	uint8_t * param;
	uint8_t str_size, baudrate_idx;
	CFG_Packet *value = get_CFG_Packet_pointer();

	// Redirection IP address init
	uint8_t return_ip[4] = {value->network_info_common.local_ip[0],
							value->network_info_common.local_ip[1],
							value->network_info_common.local_ip[2],
							value->network_info_common.local_ip[3]};

	uint8_t * ip = return_ip;

	if((param = get_http_param_value((char *)uri, "devicename")))
	{
		memset(value->module_name, 0x00, 25);
		if((str_size = strlen((char*)param)) > 24) str_size = 24; // exception handling
		memcpy(value->module_name, param, str_size);
	}

	if((param = get_http_param_value((char *)uri, "dhcp")))
	{
		if(strstr((char const*)param, "1") != NULL) value->options.dhcp_use = 1; // DHCP mode
		else value->options.dhcp_use = 0; // Static mode
	}

	if(value->options.dhcp_use == 0) // Static mode
	{
		if((param = get_http_param_value((char *)uri, "lip")))
		{
			inet_addr_((u_char*)param, value->network_info_common.local_ip);

			return_ip[0] = value->network_info_common.local_ip[0];
			return_ip[1] = value->network_info_common.local_ip[1];
			return_ip[2] = value->network_info_common.local_ip[2];
			return_ip[3] = value->network_info_common.local_ip[3];
		}
		if((param = get_http_param_value((char *)uri, "gw")))
		{
			inet_addr_((u_char*)param, value->network_info_common.gateway);
		}
		if((param = get_http_param_value((char *)uri, "sub")))
		{
			inet_addr_((u_char*)param, value->network_info_common.subnet);
		}
		if((param = get_http_param_value((char *)uri, "dns")))
		{
			inet_addr_((u_char*)param, value->options.dns_server_ip);
		}
	}

		if((param = get_http_param_value((char *)uri, "smode")))
	{
		if(strstr((char const*)param, "1") != NULL) value->proto.protocol = 1; // DHCP mode
		else value->proto.protocol = 0; // Static mode
	}
	if((param = get_http_param_value((char *)uri, "Universe")))
	{
		value->proto.universe = ATOI(param, 10);
	}

	if((param = get_http_param_value((char *)uri, "USize")))
	{
		value->proto.usize = ATOI(param, 10);
	}

#ifdef __userHandler_debug_
printf("set_basic_config_setting calling save_CFG_Packet_to_storage \n\r");
#endif
	save_CFG_Packet_to_storage();
#ifdef __userHandler_debug_
printf("set_basic_config_setting returning \n\r");
#endif

	return ip;
}

uint8_t * set_port_config_setting(uint8_t * uri)
{
	uint8_t * param;
	uint8_t str_size;
	char param_name[25];
	int a;

	CFG_Packet *value = get_CFG_Packet_pointer();

	// Redirection IP address init
	uint8_t return_ip[4] = {value->network_info_common.local_ip[0],
							value->network_info_common.local_ip[1],
							value->network_info_common.local_ip[2],
							value->network_info_common.local_ip[3]};

	uint8_t * ip = return_ip;

	for(a=0;a<PIXEL_PORTS;a++)
	{
		sprintf(param_name,"Proto_p%i",a);
		if((param = get_http_param_value((char *)uri, param_name)))
		{
#ifdef __userHandler_debug_
printf("Parameter %s returned %s\n\r",param_name,param);
#endif

			value->io.protocol[a] = ATOI(param, 10);
		}
		sprintf(param_name,"IO_p%i",a);
		if((param = get_http_param_value((char *)uri, param_name)))
		{
			value->io.pin[a] = ATOI(param, 10);
		}
		sprintf(param_name,"start_p%i",a);
		if((param = get_http_param_value((char *)uri, param_name)))
		{
			value->io.start_channel[a] = ATOI(param, 10);
		}
		sprintf(param_name,"channels_p%i",a);
		if((param = get_http_param_value((char *)uri, param_name)))
		{
			value->io.channel_count[a] = ATOI(param, 10);
		}
	}

	save_CFG_Packet_to_storage();

	return ip;
}



void make_cgi_basic_config_response_page(uint16_t delay, uint8_t * url, uint8_t * cgi_response_buf, uint16_t * len)
{
	CFG_Packet *value = get_CFG_Packet_pointer();

	if(value->options.dhcp_use == 1) // Static -> DHCP, DHCP -> DHCP
	{
		*len = sprintf((char *)cgi_response_buf,"<html><head><title>PicoPixel - Configuration</title><body>Reboot Complete. Please try to connect to the IP address assigned by the <span style='color:red;'>DHCP server</span></body></html>");
	}
	else // Static -> Static, DHCP -> Static
	{
		*len = sprintf((char *)cgi_response_buf,"<html><head><title>PicoPixel - Configuration</title><script language=javascript>j=%d;function func(){document.getElementById('delay').innerText=' '+j+' ';if(j>0)j--;setTimeout('func()',1000);if(j<=0)location.href='http://%d.%d.%d.%d';}</script></head><body onload='func()'>Please wait for a while, the module will boot in<span style='color:red;' id='delay'></span> seconds.</body></html>", delay, value->network_info_common.local_ip[0] ,value->network_info_common.local_ip[1],value->network_info_common.local_ip[2],value->network_info_common.local_ip[3]);
	}
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pre-defined Get CGI functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void make_json_devinfo(uint8_t * buf, uint16_t * len)
{
	CFG_Packet *value = get_CFG_Packet_pointer();

	*len = sprintf((char *)buf, "DevinfoCallback({\"fwver\":\"%d.%d.%d\",\
											\"devname\":\"%s\",\
											\"pcode\":\"%d-%d-%d\",\
											\"mac\":\"%02X:%02X:%02X:%02X:%02X:%02X\"\
											});",
											value->fw_ver[0], value->fw_ver[1], value->fw_ver[2],
											value->module_name,
											value->module_type[0],value->module_type[1],value->module_type[2],
											value->network_info_common.mac[0],value->network_info_common.mac[1],value->network_info_common.mac[2],value->network_info_common.mac[3],value->network_info_common.mac[4],value->network_info_common.mac[5]
											);
}

void make_json_netinfo(uint8_t * buf, uint16_t * len)
{
	CFG_Packet *value = get_CFG_Packet_pointer();

	*len = sprintf((char *)buf, "NetinfoCallback({\"ip\":\"%d.%d.%d.%d\",\
											\"gw\":\"%d.%d.%d.%d\",\
											\"sub\":\"%d.%d.%d.%d\",\
											\"dns\":\"%d.%d.%d.%d\",\
											\"dhcp\":\"%d\"\
											});",
											value->network_info_common.local_ip[0],value->network_info_common.local_ip[1],value->network_info_common.local_ip[2],value->network_info_common.local_ip[3],
											value->network_info_common.gateway[0],value->network_info_common.gateway[1],value->network_info_common.gateway[2],value->network_info_common.gateway[3],
											value->network_info_common.subnet[0],value->network_info_common.subnet[1],value->network_info_common.subnet[2],value->network_info_common.subnet[3],
											value->options.dns_server_ip[0],value->options.dns_server_ip[1],value->options.dns_server_ip[2],value->options.dns_server_ip[3],
											value->options.dhcp_use
											);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Predefined Set CGI functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t set_devinfo(uint8_t * uri)
{
	uint8_t ret = 0;
	uint8_t * param;
	uint8_t str_size;
	CFG_Packet *value = get_CFG_Packet_pointer();

	if((param = get_http_param_value((char *)uri, "devname")))
	{
		memset(value->module_name, 0x00, 25);
		if((str_size = strlen((char*)param)) > 24) str_size = 24; // exception handling
		memcpy(value->module_name, param, str_size);

		ret = 1;
	}

	if(ret == 1) save_CFG_Packet_to_storage();
	return ret;
}

uint8_t set_netinfo(uint8_t * uri)
{
	uint8_t ret = 0;
	uint8_t * param;

	CFG_Packet *value = get_CFG_Packet_pointer();


	if((param = get_http_param_value((char *)uri, "dhcp")))
	{
		if(strstr((char const*)param, "1") != NULL) value->options.dhcp_use = 1; // DHCP mode
		else value->options.dhcp_use = 0; // Static mode
		ret = 1;
	}

	if(value->options.dhcp_use == 0) // Static mode
	{
		if((param = get_http_param_value((char *)uri, "ip")))
		{
			inet_addr_((u_char*)param, value->network_info_common.local_ip);
			ret = 1;
		}
		if((param = get_http_param_value((char *)uri, "gw")))
		{
			inet_addr_((u_char*)param, value->network_info_common.gateway);
			ret = 1;
		}
		if((param = get_http_param_value((char *)uri, "sub")))
		{
			inet_addr_((u_char*)param, value->network_info_common.subnet);
			ret = 1;
		}
		if((param = get_http_param_value((char *)uri, "dns")))
		{
			inet_addr_((u_char*)param, value->options.dns_server_ip);
			ret = 1;
		}
	}

	if(ret == 1) save_CFG_Packet_to_storage();
	return ret;
}

int8_t set_test_mode(uint8_t * uri)
{
	uint8_t * param;
	uint8_t tmode = 0;
	thread_ctrl *hwconfig = get_running_config();

	if((param = get_http_param_value((char *)uri, "testmode"))) 
	{
		tmode = (uint8_t)ATOI(param, 10);
	}

	hwconfig->run_mode = tmode;
	printf("Run mode: %i\n",hwconfig->run_mode);
	return tmode;

}

int8_t set_test_pattern(uint8_t * uri)
{
	uint8_t * param;
	uint8_t str_size = 0;
	uint8_t port;
	uint8_t testtype;
	uint32_t color;

	//CFG_Packet * config = get_CFG_Packet_pointer();
	thread_ctrl *running_config = get_running_config();

/*	    uint8_t port[16];
    uint32_t start_channel[16];
    uint32_t channel_count[16];
*/
	if((param = get_http_param_value((char *)uri, "port"))) 
	{
		port = (uint8_t)ATOI(param, 10);
		if(port > 15) return -1;

		if((param = get_http_param_value((char *)uri, "testtype")))  
		{
			testtype = (uint8_t)ATOI(param,10);
			if((param = get_http_param_value((char *)uri,"color")))
			{
				color = (uint32_t)ATOL(&param[1],16);
			}
			running_config->led_string[port].test_mode[0] = testtype;
			running_config->led_string[port].test_color[0] = color;
printf("Port:%i TestType:%i Color:%#010x\n\r",port,testtype,color);
		}
	}

	return port;
}

int8_t set_channel(uint8_t * uri)
{
	uint8_t * param;
	uint8_t pin = 0;
	uint8_t str_size = 0;
	uint8_t port;
	uint32_t start_channel;
	uint32_t channel_count;

	CFG_Packet * config = get_CFG_Packet_pointer();
/*	    uint8_t port[16];
    uint32_t start_channel[16];
    uint32_t channel_count[16];
*/
	if((param = get_http_param_value((char *)uri, "pin"))) // GPIO (D0 ~ D15)
	{
		pin = (uint8_t)ATOI(param, 10);
		if(pin > 15) return -1;

		if((param = get_http_param_value((char *)uri, "Port")))  // Port (0 ~ 7)
		{
			port = (uint8_t)ATOI(param,10);
			if((param = get_http_param_value((char *)uri,"Start")))
			{
				start_channel = (uint32_t)ATOI(param,10);
				if((param = get_http_param_value((char *)uri,"Channels")))
				{
					channel_count = (uint32_t)ATOI(param,10);
				}
			}
			config->io.pin[pin] = port;
			config->io.start_channel[pin] = start_channel;
			config->io.channel_count[pin] = channel_count;
printf("D%i Port:%i Start Channel:%i Channels:%i\n\r",pin,port,start_channel,channel_count);
			save_CFG_Packet_to_storage();
		}
	}

	return pin;
}

// Parameters: URI, Buffer, Length
uint8_t predefined_get_cgi_processor(uint8_t * uri_name, uint8_t * buf, uint16_t * len)
{
	uint8_t ret = 1;	// ret = 1 means 'uri_name' matched
	uint8_t cgibuf[14] = {0, };
	int8_t cgi_dio = -1;
	int8_t cgi_ain = -1;

	uint8_t i;

	if(strcmp((const char *)uri_name, "get_devinfo.cgi") == 0)
	{
		make_json_devinfo(buf, len);
	}
	else if(strcmp((const char *)uri_name, "get_netinfo.cgi") == 0)
	{
		make_json_netinfo(buf, len);
	}
	else if(strcmp((const char *)uri_name,"widget.cgi") == 0)
	{
		make_basic_config_setting_json_callback(buf, len);
	}
	else if(strcmp((const char *)uri_name, "portconfig.cgi") == 0)
	{
		make_json_port_config(buf, len);
	}
	else if(strcmp((const char *)uri_name, "outputconfig.cgi") == 0)
	{
		make_json_output_config(buf, len);
	}
	else
	{
		ret=0;
	}
	return ret;
}


// Parameters: URI, Parameters, Buffer, Length
uint8_t predefined_set_cgi_processor(uint8_t * uri_name, uint8_t * uri, uint8_t * buf, uint16_t * len)
{
	uint8_t ret = 1;	// ret = 1 means 'uri_name' matched
	uint8_t val = 0;
	uint8_t * device_ip;
	if(strcmp((const char *)uri_name, "config.cgi") == 0)
	{
		device_ip = set_basic_config_setting(uri);
		make_cgi_basic_config_response_page(10, device_ip, buf, len);
		ret = HTTP_RESET;
	}
	// Pixel port configuration
	else if(strcmp((const char *)uri_name, "set_portconfig.cgi") == 0)
	{
		device_ip = set_port_config_setting(uri);
		make_cgi_basic_config_response_page(10, device_ip, buf, len);
		ret = HTTP_RESET;
	}
	// Test Mode Control
	else if(strcmp((const char *)uri_name, "set_testmode.cgi") == 0)
	{
		val = set_test_mode(uri);
		*len = sprintf((char *)buf, "%d", val);
	}
	// Test pattern Control
	else if(strcmp((const char *)uri_name, "set_testpattern.cgi") == 0)
	{
		val=set_test_pattern(uri);
		*len = sprintf((char *)buf, "%d",val);
	}
	// Devinfo; devname
	else if(strcmp((const char *)uri_name, "set_devinfo.cgi") == 0)
	{
		val = set_devinfo(uri);
		*len = sprintf((char *)buf, "%d", val);
	}
	// Netinfo; ip, gw, sub, dns, dhcp
	else if(strcmp((const char *)uri_name, "set_netinfo.cgi") == 0)
	{
		val = set_netinfo(uri);
		*len = sprintf((char *)buf, "%d", val);
	}
	// Channel port mappings
	else if(strcmp((const char *)uri_name, "save_channel.cgi") == 0)
	{
		val = set_channel(uri);
		*len = sprintf((char *)buf, "%d", val);
	}
	else
	{
		ret = 0;
	}

	return ret;
}

// return value - 	0: Failed (no custom command)
//					1: Success
//					2: Failed (custom command ok, but process error - e.g., I/O control failed)
uint8_t custom_command_handler(
	uint8_t * buf				/**< custom command: pointer to be parsed */
	)
{
	uint8_t ret = NO_CUSTOM_COMMAND;

#ifdef _CUSTOM_COMMAND_DEBUG_
			//printf("[CWD] ");
#endif

	// if the command process succeed, ret = COMMAND_SUCCESS;
	// if the command received but process failed, ret = COMMAND_ERROR;
	// if the http request is not custom command, ret = NO_CUSTOM_COMMAND;

	return ret;
}

//*********************************************************************************************************
// Extra functions to make userHandler.c compile
//*********************************************************************************************************


void Mac_Conf()
{
	CFG_Packet *value = get_CFG_Packet_pointer();
	setSHAR(value->network_info_common.mac);
}

void set_dhcp_mode()
{
	CFG_Packet *value = get_CFG_Packet_pointer();

	value->options.dhcp_use = 1;
}

void set_static_mode()
{
	CFG_Packet *value = get_CFG_Packet_pointer();

	value->options.dhcp_use = 0;
}

void set_mac(uint8_t *mac)
{
	CFG_Packet *value = get_CFG_Packet_pointer();

	memcpy(value->network_info_common.mac, mac, sizeof(value->network_info_common.mac));
}