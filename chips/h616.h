#ifndef _H616_H
#define _H616_H

#define SUNXI_PUD_OFF   0
#define SUNXI_PUD_UP    1
#define SUNXI_PUD_DOWN  2

//sunxi_pwm
#define SUNXI_PWM_BASE (0x01c21400)
#define SUNXI_PWM_CTRL_REG  (SUNXI_PWM_BASE)
#define SUNXI_PWM_CH0_PERIOD  (SUNXI_PWM_BASE + 0x4)
#define SUNXI_PWM_CH1_PERIOD  (SUNXI_PWM_BASE + 0x8)

#define SUNXI_PWM_CH0_EN   (1 << 4)
#define SUNXI_PWM_CH0_ACT_STA  (1 << 5)
#define SUNXI_PWM_SCLK_CH0_GATING (1 << 6)
#define SUNXI_PWM_CH0_MS_MODE  (1 << 7) //pulse mode
#define SUNXI_PWM_CH0_PUL_START  (1 << 8)


#define GPIO_BIT(x)                        (1UL << (x))

#define NS_1s 1000000000
#define FREQ_CLOCK 24000000

extern void H616_pin_set_mode (int gpio_num, int mode);
extern void H616_pin_set_alt (int gpio_num, int mode);
extern int H616_pin_get_alt (int gpio_num);

extern int H616_gpio_read(int gpio_num);
extern void H616_gpio_write(int gpio_num, int value);
extern void H616_gpio_set_PullUpDn (int gpio_num, int pud);


extern void H616_pwmWrite(int gpio_num, int value, int freq);
extern void H616_pwmwrite_time(int gpio_num, int high_time, int period_time);
#endif