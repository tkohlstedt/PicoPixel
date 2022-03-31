#ifndef __PIXELCONTROLLER_H__
#define __PIXELCONTROLLER_H__

#define  _PICOPIXEL_DEBUG_
#undef   _OUTPUT_DEBUG_
#undef   _NETWORK_DEBUG_
#undef   _ZCPP_DEBUG_
#define  _MAIN_DEBUG_

#define MAX_PIXELS 5000
#define MAX_UNIVERSES 30
#define UNIVERSE_SIZE 512
#define START_UNIVERSE 200
#define PIXEL_BUFFER_SIZE MAX_UNIVERSES * UNIVERSE_SIZE
#define CONTROLLER_NAME "PicoPixelController\0"
#define PIXEL_PORTS 8
#define IO_PINS 16

/* Buffer */
#define ETHERNET_BUF_MAX_SIZE (1024 * 2)
#define ETHERNET_BUF_MAX_SLOTS 40

/* Socket */
#define HTTP_SOCKET_MAX_NUM 2

typedef struct __string_ctrl
{
   uint32_t channel_count[8];
   uint32_t start_channel[8];
   int brightness[8];
   int gamma[8];
   int direction[8];
   int color_order[8];
   int null_pixels[8];
   int * spi_dev;
//   spi_device * spi_dev;
} string_ctrl;

typedef struct __thread_ctrl
{
   int pixel_ports;
   char *buffer;
   string_ctrl led_string[PIXEL_PORTS];
} thread_ctrl;

#endif
