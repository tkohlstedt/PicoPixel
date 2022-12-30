#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "picopixel.h"
#include "effects.h"

static thread_ctrl *config;

//local prototypes
void rainbowCycleCount();
void FadeInOutCount();
void RunningLightsCount();

void test_init(thread_ctrl * hwconfig)
{
    config = hwconfig;
}

void test_run()
{
  // do these only once each regardless of how many strings are in test mode
  rainbowCycleCount();
  FadeInOutCount();
  RunningLightsCount();
    for(int a = 0;a < PIXEL_PORTS;a++)
    {
        if(config->led_string[a].active[0])
        {
            switch (config->led_string[a].test_mode[0])
            {
                case TEST_OFF:
                    off(a);
                    break;
                case TEST_SOLID:
                    solid(a);
                    break;
                case TEST_CHASE:
                    RunningLights(a);
                    break;
                case TEST_COLORWASH:
                    rainbowCycle(a);
                    break;
                case TEST_FADE:
                    FadeInOut(a);
                    break;
                case TEST_RUNNING_LIGHTS:
                    RunningLights(a);
                    break;
            }
        }
    }
}

void off(int led_str)
{
  uint8_t *buffer_ptr;
  uint16_t leds;

  leds = config->led_string[led_str].channel_count[0] / 3;
  buffer_ptr = config->buffer + config->led_string[led_str].start_channel[0];

  for(int a=0;a<leds;a++)
  {
      *buffer_ptr++ = 0;
      *buffer_ptr++ = 0;
      *buffer_ptr++ = 0;
  }
}

void solid(int led_str) 
{
  uint8_t *buffer_ptr;
  uint8_t red,green,blue;
  uint16_t leds;

  leds = config->led_string[led_str].channel_count[0] / 3;
  buffer_ptr = config->buffer + config->led_string[led_str].start_channel[0];
  red = (config->led_string[led_str].test_color[0] & 0x00FF0000)>>16;
  green = (config->led_string[led_str].test_color[0] & 0x0000FF00)>>8;
  blue = (config->led_string[led_str].test_color[0] & 0x000000FF);
  for(int a=0;a<leds;a++)
  {
      *buffer_ptr++ = red;
      *buffer_ptr++ = green;
      *buffer_ptr++ = blue;
  }
}

// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
#define RAINBOWCYCLEDELAY 10
uint16_t rainbowCycleCounter;

void rainbowCycleCount()
{
  static int delaycounter = RAINBOWCYCLEDELAY;
  delaycounter--;
  if(!delaycounter)
  {
    rainbowCycleCounter++;
    if(rainbowCycleCounter>256*5)
    {
      rainbowCycleCounter=0;
    }
      delaycounter = RAINBOWCYCLEDELAY;
  }
}

void rainbowCycle(int led_str) {
  uint8_t *c;
  static uint16_t i;
  uint16_t leds;
  uint8_t *buffer_ptr;

  leds = config->led_string[led_str].channel_count[0] / 3;
  buffer_ptr = config->buffer + config->led_string[led_str].start_channel[0];
//  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
  for(i=0 ; i< leds; i++) 
  {
      c=Wheel(((i * 256 / leds) + rainbowCycleCounter) & 255);
      *buffer_ptr++ = *c++;
      *buffer_ptr++ = *c++;
      *buffer_ptr++ = *c++;
  }
}

uint8_t * Wheel(uint8_t WheelPos) {
  static uint8_t c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

#define RUNNINGLIGHTSDELAY 10
uint8_t RunningLightsPosition;

void RunningLightsCount()
{
  static int delaycounter = RUNNINGLIGHTSDELAY;
  if(!delaycounter)
  {
    RunningLightsPosition++;
    delaycounter = RUNNINGLIGHTSDELAY;
  }
  delaycounter--;
}

void RunningLights(int led_str) {
  uint16_t leds;
  uint8_t * buffer_ptr;
  uint8_t red,green,blue;
  int shifted;


  leds = config->led_string[led_str].channel_count[0] / 3;
  buffer_ptr = config->buffer + config->led_string[led_str].start_channel[0];
  red = (config->led_string[led_str].test_color[0] & 0x00FF0000)>>16;
  green = (config->led_string[led_str].test_color[0] & 0x0000FF00)>>8;
  blue = (config->led_string[led_str].test_color[0] & 0x000000FF);

//  for(int j=0; j<leds*2; j++)
//  {
//      Position++; // = 0; //Position + Rate;
      for(int i=0; i<leds; i++) {
        shifted = i >>2;
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        *buffer_ptr++ = ((sin(shifted+RunningLightsPosition) * 127 + 128)/255) * red;
        *buffer_ptr++ = ((sin(shifted+RunningLightsPosition) * 127 + 128)/255) * green;
        *buffer_ptr++ = ((sin(shifted+RunningLightsPosition) * 127 + 128)/255) * blue;
      }
//  }
}

void FadeInOutCount()
{


}
void FadeInOut(int led_str){
  uint16_t leds;
  uint8_t * buffer_ptr;
  uint8_t red,green,blue;

  leds = config->led_string[led_str].channel_count[0] / 3;
  buffer_ptr = config->buffer + config->led_string[led_str].start_channel[0];
  red = (config->led_string[led_str].test_color[0] & 0xFF000000)>>24;
  green = (config->led_string[led_str].test_color[0] & 0x00FF0000)>>16;
  blue = (config->led_string[led_str].test_color[0] & 0x0000FF00) >>8;

  float r, g, b;
  static int k = 0;
  static int dir = 1;

  if(dir)
  {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    for(int a=0;a<leds;a++)
    {
        *buffer_ptr++ = red;
        *buffer_ptr++ = green;
        *buffer_ptr++ = blue;
    }
    if(++k > 255)
    {
        dir = 0;
    }

  }else
  {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    for(int a=0;a<leds;a++)
    {
        *buffer_ptr++ = red;
        *buffer_ptr++ = green;
        *buffer_ptr++ = blue;
    }
    if(--k==0)
    {
        dir = 1;
    }      
  }
}