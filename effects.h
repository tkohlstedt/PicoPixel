#ifndef __EFFECTS_H__
#define __EFFECTS_H__

void test_init(thread_ctrl * hwconfig);
void test_run();

void off(int led_str);
void solid(int led_str); 
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
void rainbowCycle(int led_str);
uint8_t * Wheel(uint8_t WheelPos);
void RunningLights(int led_str);
void FadeInOut(int led_str);


#endif