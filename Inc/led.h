#ifndef __LED_H__
#define __LED_H__

enum
{
	LED_0 = 0,
	LED_1,
	LED_2,
	LED_3,
	LED_4,
	LED_5,
	LED_6,
	LED_7,
};

void led_on(int n);
void led_off(int n);
void led_toggle(int n);
void led_on_all(void);
void led_off_all(void);

#endif
