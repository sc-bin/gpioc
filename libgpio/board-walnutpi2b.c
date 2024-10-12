#include "board-pin.h"
#include "pin-num.h"

struct BOARD_PIN walnutpi2b_pins[] = {
    DEF_A_BOARD_PIN(0, 0, "", 0),
    DEF_A_BOARD_PIN(1, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    DEF_A_BOARD_PIN(2, PH_5V, "5v", PH_COLOR_RED),
    DEF_A_BOARD_PIN(3, PB4, "PB4", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(4, PH_5V, "5v", PH_COLOR_RED),
    DEF_A_BOARD_PIN(5, PB5, "PB5", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(6, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(7, PB6, "PB6", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(8, PB0, "PB0", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(9, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(10, PB1, "PB1", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(11, PB13, "PB13", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(12, PB14, "PB14", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(13, PI12, "PI12", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(14, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(15, PI11, "PI11", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(16, PI10, "PI10", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(17, PH_3V3, "3.3v", PH_COLOR_YELLOW),
    DEF_A_BOARD_PIN(18, PI9, "PI9", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(19, PI4, "PI4", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(20, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(21, PI5, "PI5", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(22, PI7, "PI7", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(23, PI3, "PI3", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(24, PI2, "PI2", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(25, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(26, PI6, "PI6", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(27, PI16, "PI16", PH_COLOR_BLUE),
    DEF_A_BOARD_PIN(28, PI15, "PI15", PH_COLOR_BLUE),
    DEF_A_BOARD_PIN(29, PL6, "PL6", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(30, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(31, PL5, "PL5", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(32, PI14, "PI14", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(33, PL4, "PL4", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(34, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(35, PL2, "PL2", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(36, PI13, "PI13", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(37, PL3, "PL3", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(38, PI0, "PI0", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(39, PH_GND, "GND", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(40, PI1, "PI1", PH_COLOR_GREEEN),
    DEF_A_BOARD_PIN(41, PB7, "KEY", PH_COLOR_BLACK),
    DEF_A_BOARD_PIN(42, PB8, "LED", PH_COLOR_BLACK),
};
static int walnutpi2b_pwms_pins[] = {0};
static int walnutpi2b_pwms_modes[] = {0};
static struct BOARD_PIN_PER walnutpi2b_pwms =
    {
        .count = 0,
        .pins = walnutpi2b_pwms_pins,
        .modes = walnutpi2b_pwms_modes,
};

static int walnutpi2b_uarts_pins[] = {0};
static int walnutpi2b_uarts_modes[] = {0};
static struct BOARD_PIN_PER walnutpi2b_uarts =
    {
        .count = 0,
        .pins = walnutpi2b_uarts_pins,
        .modes = walnutpi2b_uarts_modes,
};
static int walnutpi2b_spis_pins[] = {0};
static int walnutpi2b_spis_modes[] = {0};
static struct BOARD_PIN_PER walnutpi2b_spis =
    {
        .count = 0,
        .pins = walnutpi2b_spis_pins,
        .modes = walnutpi2b_spis_modes,
};
static int walnutpi2b_i2cs_pins[] = {0};
static int walnutpi2b_i2cs_modes[] = {0};
static struct BOARD_PIN_PER walnutpi2b_i2cs =
    {
        .count = 0,
        .pins = walnutpi2b_i2cs_pins,
        .modes = walnutpi2b_i2cs_modes,
};
struct BOARD_DESC walnutpi_2b = {
    .model = "walnutpi-2b",
    .pin_num = 42,
    .pins = walnutpi2b_pins,
    .pwms = &walnutpi2b_pwms,
    .uarts = &walnutpi2b_uarts,
    .spis = &walnutpi2b_spis,
    .i2cs = &walnutpi2b_i2cs,
};