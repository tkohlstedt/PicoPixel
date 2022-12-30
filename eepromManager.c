#include <hardware/flash.h>
#include <hardware/sync.h>
#include "eepromManager.h"
#include <pico/multicore.h>
#include <string.h>
#include <stdio.h>

#define __EEPROM_DEBUG_

static CFG_Packet cfg_packet;

CFG_Packet* get_CFG_Packet_pointer()
{
    if(strncmp((const char *)&cfg_packet.magic,"PiPx",4))
    {
        load_CFG_Packet_from_storage();
    }
	return &cfg_packet;
}

#define MAJOR_VER 1
#define MINOR_VER 0
#define MAINTENANCE_VER 0

void set_CFG_Packet_to_factory_value()
{
	memcpy(cfg_packet.magic, "PiPx",4);  // set the magic string
	cfg_packet.packet_size = sizeof(CFG_Packet);	// 133
	cfg_packet.module_type[0] = 0x01;
	cfg_packet.module_type[1] = 0x02;
	cfg_packet.module_type[2] = 0x00;
	memcpy(cfg_packet.module_name, "PicoPixel\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 25);
	cfg_packet.fw_ver[0] = MAJOR_VER;
	cfg_packet.fw_ver[1] = MINOR_VER;
	cfg_packet.fw_ver[2] = MAINTENANCE_VER;

	cfg_packet.network_info_common.local_ip[0] = 192;
	cfg_packet.network_info_common.local_ip[1] = 168;
	cfg_packet.network_info_common.local_ip[2] = 11;
	cfg_packet.network_info_common.local_ip[3] = 100;
	cfg_packet.network_info_common.gateway[0] = 192;
	cfg_packet.network_info_common.gateway[1] = 168;
	cfg_packet.network_info_common.gateway[2] = 11;
	cfg_packet.network_info_common.gateway[3] = 1;
	cfg_packet.network_info_common.subnet[0] = 255;
	cfg_packet.network_info_common.subnet[1] = 255;
	cfg_packet.network_info_common.subnet[2] = 255;
	cfg_packet.network_info_common.subnet[3] = 0;

	cfg_packet.io.protocol[0] = 0; // set all ports to unused
	cfg_packet.io.protocol[1] = 0;
	cfg_packet.io.protocol[2] = 0;
	cfg_packet.io.protocol[3] = 0;
	cfg_packet.io.protocol[4] = 0;
	cfg_packet.io.protocol[5] = 0;
	cfg_packet.io.protocol[6] = 0;
	cfg_packet.io.protocol[7] = 0;

	cfg_packet.proto.protocol = 0; //default to zcpp

	memcpy(cfg_packet.options.pw_setting, "PicoPixel\0", 10);
	cfg_packet.options.dhcp_use = 1;
	cfg_packet.options.dns_use = 1;
	cfg_packet.options.dns_server_ip[0] = 8;
	cfg_packet.options.dns_server_ip[1] = 8;
	cfg_packet.options.dns_server_ip[2] = 8;
	cfg_packet.options.dns_server_ip[3] = 8;
	memset(cfg_packet.options.dns_domain_name, '\0', 50);
}

void load_CFG_Packet_from_storage()
{
	read_flash(CONFIG_PAGE_ADDR, (uint8_t *)&cfg_packet, sizeof(CFG_Packet));

	if(strncmp((const char *)&cfg_packet.magic,"PiPx",4)){
		set_CFG_Packet_to_factory_value();
		write_flash(CONFIG_PAGE_ADDR, (uint8_t *)&cfg_packet, sizeof(CFG_Packet));
	}
}

void save_CFG_Packet_to_storage()
{
	write_flash(CONFIG_PAGE_ADDR, (uint8_t *)&cfg_packet, sizeof(CFG_Packet));
}

void get_CFG_Packet_value(void *dest, const void *src, uint16_t size)
{
	memcpy(dest, src, size);
}

void set_CFG_Packet_value(void *dest, const void *value, const uint16_t size)
{
	memcpy(dest, value, size);
}

void set_CFG_Packet(wiz_NetInfo *net)
{
	set_CFG_Packet_value(cfg_packet.network_info_common.mac, net->mac, sizeof(cfg_packet.network_info_common.mac));
	set_CFG_Packet_value(cfg_packet.network_info_common.local_ip, net->ip, sizeof(cfg_packet.network_info_common.local_ip));
	set_CFG_Packet_value(cfg_packet.network_info_common.gateway, net->gw, sizeof(cfg_packet.network_info_common.gateway));
	set_CFG_Packet_value(cfg_packet.network_info_common.subnet, net->sn, sizeof(cfg_packet.network_info_common.subnet));
	set_CFG_Packet_value(cfg_packet.options.dns_server_ip, net->dns, sizeof(cfg_packet.options.dns_server_ip));
	if(net->dhcp == NETINFO_STATIC)
		cfg_packet.options.dhcp_use = 0;
	else
		cfg_packet.options.dhcp_use = 1;
}

void get_CFG_Packet(wiz_NetInfo *net)
{
	get_CFG_Packet_value(net->mac, cfg_packet.network_info_common.mac, sizeof(net->mac));
	get_CFG_Packet_value(net->ip, cfg_packet.network_info_common.local_ip, sizeof(net->ip));
	get_CFG_Packet_value(net->gw, cfg_packet.network_info_common.gateway, sizeof(net->gw));
	get_CFG_Packet_value(net->sn, cfg_packet.network_info_common.subnet, sizeof(net->sn));
	get_CFG_Packet_value(net->dns, cfg_packet.options.dns_server_ip, sizeof(net->dns));
	if(cfg_packet.options.dhcp_use)
		net->dhcp = NETINFO_DHCP;
	else
		net->dhcp = NETINFO_STATIC;
}


int read_flash(uint32_t address, uint8_t *data, uint32_t size)
// address is the position in flash, not a memory address.
// to read it, add the XIP_BASE to find the actual memory address
{
    char *p = (char *)XIP_BASE + address;
    memcpy(data,p,size);
}

int write_flash(uint32_t address, uint8_t *data, uint32_t size)
{
    // size must be a multiple of FLASH_PAGE_SIZE (256 bytes)
    // address must be aligned on 4K boundary
    // right now only 1st 256 bytes can be programmed.  Fix this code to handle larger
    // chunks and potentially save sections not to be updated before erasing

    // pause the second core while doing this
#ifdef __EEPROM_DEBUG_
printf("Lockout Core 1\n\r");
#endif
    bool lo = multicore_lockout_start_timeout_us(1000);  // wait up to 1 second for lockout
#ifdef __EEPROM_DEBUG_
printf("Lockout %s \n\r",lo?"succeeded":"failed");
printf("Disabling interrupts\n\r");
#endif
    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(address,FLASH_SECTOR_SIZE);
    flash_range_program (address, data, size);
    restore_interrupts (ints);
#ifdef __EEPROM_DEBUG_
printf("Interrupts restored\n\r");
#endif
    multicore_lockout_end_timeout_us(1000);
#ifdef __EEPROM_DEBUG_
printf("Lockout ended\n\r");
#endif
}

