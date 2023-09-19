from gpioc._pin import Pin
from gpioc._pwm import PWMOut_father as _PWM

import gpioc._gpioc as _common

class Pwm(_PWM):
    _chip = _common.CHIP_H616

# class Pin(_PIN):

    # def _setup(self, gpio_num, dir, pull_up_down=None ):
    #     if dir == _gpio.f_INPUT :
    #         _gpio.set_mode(gpio_num, _gpio.f_INPUT)
    #         if pull_up_down == self.PULL_UP:
    #             _gpio.set_pullUpDn(gpio_num, _gpio.f_pullUp)
    #         elif pull_up_down == self.PULL_DOWN:
    #             _gpio.set_pullUpDn(gpio_num, _gpio.f_pullDown)
    #         else:
    #             _gpio.set_pullUpDn(gpio_num, _gpio.f_pull_OFF)
    #     if dir == _gpio.f_OUTPUT :
    #         _gpio.set_mode(gpio_num, _gpio.f_OUTPUT)
                
    # # self.output(self.id, val)
    # def _output(self, gpio_num, val):
    #     _gpio.write(gpio_num, val)

    # # return _gpio.input(self.id)
    # def _input(self, gpio_num):
    #     return _gpio.read(gpio_num)
    

PC0 = Pin(64)
PC1 = Pin(65)
PC2 = Pin(66)
PC3 = Pin(67)
PC4 = Pin(68)
PC5 = Pin(69)
PC6 = Pin(70)
PC7 = Pin(71)
PC8 = Pin(72)
PC9 = Pin(73)
PC10 = Pin(74)
PC11 = Pin(75)
PC12 = Pin(76)
PC13 = Pin(77)
PC14 = Pin(78)
PC15 = Pin(79)

PF0 = Pin(160)
PF1 = Pin(161)
PF2 = Pin(162)
PF3 = Pin(163)
PF4 = Pin(164)
PF5 = Pin(165)
PF6 = Pin(166)

PG0 = Pin(192)
PG1 = Pin(193)
PG2 = Pin(194)
PG3 = Pin(195)
PG4 = Pin(196)
PG5 = Pin(197)
PG6 = Pin(198)
PG7 = Pin(199)
PG8 = Pin(200)
PG9 = Pin(201)
PG10 = Pin(202)
PG11 = Pin(203)
PG12 = Pin(204)
PG13 = Pin(205)
PG14 = Pin(206)
PG15 = Pin(207)
PG16 = Pin(208)
PG17 = Pin(209)
PG18 = Pin(210)
PG19 = Pin(211)

PH0 = Pin(224)
PH1 = Pin(225)
PH2 = Pin(226)
PH3 = Pin(227)
PH4 = Pin(228)
PH5 = Pin(229)
PH6 = Pin(230)
PH7 = Pin(231)
PH8 = Pin(232)
PH9 = Pin(233)
PH10 = Pin(234)

PI0 = Pin(256)
PI1 = Pin(257)
PI2 = Pin(258)
PI3 = Pin(259)
PI4 = Pin(260)
PI5 = Pin(261)
PI6 = Pin(262)
PI7 = Pin(263)
PI8 = Pin(264)
PI9 = Pin(265)
PI10 = Pin(266)
PI11 = Pin(267)
PI12 = Pin(268)
PI13 = Pin(269)
PI14 = Pin(270)
PI15 = Pin(271)
PI16 = Pin(272)