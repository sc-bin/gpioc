#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pinctrl.h"
#include "softpwm.h"
#include "board.h"
#include "board-pin.h"

static struct BOARD_DESC
{
    char *model;           // 设备树model字段
    struct BOARD_PIN *pin; // 描述板子所带的所有引脚
};

static struct BOARD_DESC board_list[] = {
    {
        .model = "walnutpi-1b",
        .pin = walnutpi1b_pins,
    },
    {
        .model = "Walnutpi 2b",
        // .model = "walnutpi-1b-emmc",
        .pin = walnutpi1b_emmc_pins,
    },

};

static int walnutpi1b_pin_pwm[][2] = {{15, 5}, {16, 5}, {38, 5}, {40, 5}};
static int walnutpi1b_pin_uart[][2] = {{8, 3}, {10, 3}, {38, 3}, {40, 3}};
static int walnutpi1b_pin_spi[][2] = {{19, 4}, {21, 4}, {23, 4}, {24, 4}, {26, 4}};
static int walnutpi1b_pin_i2c[][2] = {{3, 5}, {5, 5}, {27, 5}, {28, 5}};
static struct BOARD_DESC *now_board_desc = NULL;
struct BOARD_DESC *get_board_desc()
{
    FILE *fp;
    char buffer[1024];
    char *model;
    int i;

    if (now_board_desc != NULL)
        return now_board_desc;
    fp = fopen("/proc/device-tree/model", "r");
    if (fp == NULL)
    {
        printf("Failed to open /proc/device-tree/model \n");
        exit(-1);
    }

    fgets(buffer, 100, fp);
    fclose(fp);

    model = strtok(buffer, "\n");

    for (i = 0; i < sizeof(board_list) / sizeof(struct BOARD_DESC); i++)
    {
        if (strcmp(model, board_list[i].model) == 0)
        {
            now_board_desc = &(board_list[i]);
            return now_board_desc;
        }
    }

    printf("you /proc/device-tree/model string is not in support list");
    exit(-1);
}

static int select_board()
{
    FILE *fp;
    char buffer[1024];
    char *model;
    int i;
    int _board_select = 0;

    fp = fopen("/proc/device-tree/model", "r");
    if (fp == NULL)
    {
        printf("Failed to open /proc/device-tree/model \n");
        exit(-1);
    }

    fgets(buffer, 100, fp);
    fclose(fp);

    model = strtok(buffer, "\n");

    if (strcmp(model, "walnutpi-1b") == 0)
        _board_select = _BOARD_DEF_WANUTPI_1B;
    else if (strcmp(model, "walnutpi-1b-emmc") == 0)
        _board_select = _BOARD_DEF_WANUTPI_1B_EMMC;
    else if (strcmp(model, "Walnutpi 2b") == 0)
        _board_select = _BOARD_DEF_WANUTPI_1B_EMMC;
    else
    {
        printf("you /proc/device-tree/model string is not in support list");
        exit(-1);
    }
    return _board_select;
}
static struct BOARD_PIN *get_BOARD_PIN()
{
    struct BOARD_PIN *PIN;
    return get_board_desc()->pin;
}
int board_ph_to_gpio(int pin_num)
{
    switch (select_board())
    {
    case _BOARD_DEF_WANUTPI_1B:
    case _BOARD_DEF_WANUTPI_1B_EMMC:
        if (pin_num > 42)
        {
            return PH_NUM_ERROR;
        }
        return get_BOARD_PIN()[pin_num].gpio_num;
    default:
        printf("ERROR: no support for your board\n");
    }
    return -99;
}
void exit_if_no_gpio(int pin_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        printf("ERROR: pin %d cannot do this operation \n", pin_num);
        exit(-1);
    }
}
int pin_get_mode(int pin_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        return -1;
    }
    return gpio_get_mode(gpio_num);
}

void pin_set_mode(int pin_num, int mode)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    gpio_set_mode(board_ph_to_gpio(pin_num), mode);
}
void pin_set_mode_by_name(int pin_num, char *mode)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    for (int i = 0; i <= 7; i++)
    {
        const char *str = pin_get_mode_name_by_num(pin_num, i);
        if (str != NULL)
            if (strcasecmp(str, mode) == 0)
            {
                pin_set_mode(pin_num, i);
            }
    }
}
void pin_set_pullUpDn(int pin_num, int pud)
{
    // exit_if_no_gpio(pin_num);
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    gpio_set_pullUpDn(board_ph_to_gpio(pin_num), pud);
}
int pin_read(int pin_num)
{
    // exit_if_no_gpio(pin_num);
    if (board_ph_to_gpio(pin_num) < 0)
        return -1;
    return gpio_read(board_ph_to_gpio(pin_num));
}
void pin_write(int pin_num, int value)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    // exit_if_no_gpio(pin_num);
    gpio_write(board_ph_to_gpio(pin_num), value);
}
const char *pin_get_mode_name_now(int pin_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        return "";
    }
    return gpio_pin_get_mode_name(gpio_num);
}
const char *pin_get_mode_name_by_num(int pin_num, int mode_num)
{
    int gpio_num = board_ph_to_gpio(pin_num);
    if (gpio_num < 0)
    {
        return "";
    }
    return gpio_pin_get_mode_name_by_num(gpio_num, mode_num);
}

void soft_pwm_set_duty_cycle(int pin_num, int dutycycle)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pwm_set_duty_cycle(board_ph_to_gpio(pin_num), dutycycle);
}
void soft_pwm_set_frequency(int pin_num, int freq)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pwm_set_frequency(board_ph_to_gpio(pin_num), freq);
}
int soft_pwm_get_duty_cycle(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return -1;
    return pwm_get_duty_cycle(board_ph_to_gpio(pin_num));
}
int soft_pwm_get_frequency(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return -1;
    return pwm_get_frequency(board_ph_to_gpio(pin_num));
}
void soft_pwm_start(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pwm_start(board_ph_to_gpio(pin_num));
}
void soft_pwm_stop(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return;
    pwm_stop(board_ph_to_gpio(pin_num));
}
int soft_pwm_exists(int pin_num)
{
    if (board_ph_to_gpio(pin_num) < 0)
        return -1;
    return pwm_exists(board_ph_to_gpio(pin_num));
}

void printf_pins_l(int ph)
{
    printf("|");
    if (board_ph_to_gpio(ph) >= 0 && pin_get_mode(ph) < 2)
        printf(" %d ", pin_read(ph));
    else
        printf("   ");

    printf("|");
    if (board_ph_to_gpio(ph) >= 0)
        printf(" %9s ", pin_get_mode_name_now(ph));
    else
        printf(" %9s ", "");

    printf("|");
    printf(" %4s ", get_BOARD_PIN()[ph].name);

    switch (get_BOARD_PIN()[ph].color)
    {
    case PH_COLOR_RED:
        printf("\033[37;41m");
        break;
    case PH_COLOR_BLUE:
        printf("\033[37;44m");
        break;
    case PH_COLOR_YELLOW:
        printf("\033[30;43m");
        break;
    case PH_COLOR_GREEEN:
        printf("\033[30;42m");
        break;
    default:
        printf("\033[37;40m");
    }
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %2d ", ph);
    printf("|");
    printf("\033[0m");
}
void printf_pins_r(int ph)
{
    switch (get_BOARD_PIN()[ph].color)
    {
    case PH_COLOR_RED:
        printf("\033[37;41m");
        break;
    case PH_COLOR_BLUE:
        printf("\033[37;44m");
        break;
    case PH_COLOR_YELLOW:
        printf("\033[30;43m");
        break;
    case PH_COLOR_GREEEN:
        printf("\033[30;42m");
        break;
    default:
        printf("\033[37;40m");
    }
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %-2d ", ph);
    printf("|");
    printf("\033[0m");
    printf(" %4s ", get_BOARD_PIN()[ph].name);

    printf("|");
    if (board_ph_to_gpio(ph) >= 0)
        printf(" %-9s ", pin_get_mode_name_now(ph));
    else
        printf(" %9s ", "");

    printf("|");
    if (board_ph_to_gpio(ph) >= 0 && pin_get_mode(ph) < 2)
        printf(" %d ", pin_read(ph));
    else
        printf("   ");
    printf("|");
}

void print_pins()
{
    printf("+---+-----------+------+----------+------+-----------+---+\n");
    printf("| V |    Mode   | Name | Physical | Name |    Mode   | V |\n");
    printf("+---+-----------+------+----------+------+-----------+---+\n");
    for (int ph = 1; ph < 40; ph++)
    {
        printf_pins_l(ph);
        ph++;
        printf_pins_r(ph);
        printf("\n");
    }
    printf("+---+-----------+------+----------+------+-----------+---+\n");
    printf("\n");
    printf("+---+-----------+------+----------+------+-----------+---+\n");
    printf("| V |    Mode   | Name | Physical | Name |    Mode   | V |\n");
    printf("+---+-----------+------+----------+------+-----------+---+\n");
    printf_pins_l(41);
    printf_pins_r(42);
    printf("\n");
    printf("+---+-----------+------+----------+------+-----------+---+\n");
}

void print_search_none_l(int ph)
{

    printf("|");
    printf(" %9s ", "");
    printf("|");
    printf(" %4s ", get_BOARD_PIN()[ph].name);

    switch (get_BOARD_PIN()[ph].color)
    {
    case PH_COLOR_RED:
        printf("\033[37;41m");
        break;
    case PH_COLOR_BLUE:
        printf("\033[37;44m");
        break;
    case PH_COLOR_YELLOW:
        printf("\033[30;43m");
        break;
    case PH_COLOR_GREEEN:
        printf("\033[30;42m");
        break;
    default:
        printf("\033[37;40m");
    }
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %2d ", ph);
    printf("|");
    printf("\033[0m");
}
void print_search_none_r(int ph)
{
    switch (get_BOARD_PIN()[ph].color)
    {
    case PH_COLOR_RED:
        printf("\033[37;41m");
        break;
    case PH_COLOR_BLUE:
        printf("\033[37;44m");
        break;
    case PH_COLOR_YELLOW:
        printf("\033[30;43m");
        break;
    case PH_COLOR_GREEEN:
        printf("\033[30;42m");
        break;
    default:
        printf("\033[37;40m");
    }
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %-2d ", ph);
    printf("|");
    printf("\033[0m");
    printf(" %-4s ", get_BOARD_PIN()[ph].name);

    printf("|");
    printf(" %9s ", "");

    printf("|");
}

void print_search_hit_l(int ph, int mode_num)
{
    printf("\033[30;42m");
    printf("|");
    printf(" %9s ", pin_get_mode_name_by_num(ph, mode_num));
    printf("|");
    printf(" %4s ", get_BOARD_PIN()[ph].name);
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %2d ", ph);
    printf("|");
    printf("\033[0m");
}
void print_search_hit_r(int ph, int mode_num)
{
    printf("\033[30;42m");
    printf("|");
    if (get_BOARD_PIN()[ph].gpio_num == PH_NC)
        printf(" -- ");
    else
        printf(" %-2d ", ph);
    printf("|");
    printf(" %-4s ", get_BOARD_PIN()[ph].name);
    printf("|");
    printf(" %-9s ", pin_get_mode_name_by_num(ph, mode_num));
    printf("|");
    printf("\033[0m");
}
void print_pin_by_search_all_mode_name(char *str)
{
    printf("serach: %s\n", str);
    printf("+-----------+------+----------+------+-----------+\n");
    printf("|    Mode   | Name | Physical | Name |    Mode   |\n");
    printf("+-----------+------+----------+------+-----------+\n");

    int max_pin = 0;
    switch (select_board())
    {
    case _BOARD_DEF_WANUTPI_1B:
    case _BOARD_DEF_WANUTPI_1B_EMMC:
        max_pin = 43;
        break;
    default:
        printf("ERROR: no support for your board\n");
    }
    for (int ph = 1; ph < max_pin; ph++)
    {
        int j = 7;
        if (board_ph_to_gpio(ph) > 0) // 不是电源引脚
        {
            for (j = 0; j < 7; j++) // 遍历引脚的复用功能0到7
            {
                const char *mode_desc = gpio_pin_get_mode_name_by_num(board_ph_to_gpio(ph), j);
                if (mode_desc != NULL)
                {
                    if (strncasecmp(str, mode_desc, strlen(str)) == 0)
                    {
                        if (ph % 2 == 1)
                            print_search_hit_l(ph, j);
                        else
                        {
                            print_search_hit_r(ph, j);
                            printf("\n");
                        }
                        break;
                    }
                }
            }
        }
        if (j >= 7)
        {
            // 输出代表空的行
            if (ph % 2 == 1)
                print_search_none_l(ph);
            else
            {
                print_search_none_r(ph);
                printf("\n");
            }
        }
    }
    printf("+-----------+------+----------+------+-----------+\n");
}
void print_pin_para()
{
    printf("pwm uart i2c spi");
}
void print_pin_by_mode_name(char *str)
{
    int pins[43] = {-1};
    if (strcasecmp(str, "pwm") == 0)
        for (int i = 0; i < sizeof(walnutpi1b_pin_pwm) / (sizeof(int) * 2); i++)
            pins[walnutpi1b_pin_pwm[i][0]] = walnutpi1b_pin_pwm[i][1];
    else if (strcasecmp(str, "uart") == 0)
        for (int i = 0; i < sizeof(walnutpi1b_pin_uart) / (sizeof(int) * 2); i++)
            pins[walnutpi1b_pin_uart[i][0]] = walnutpi1b_pin_uart[i][1];
    else if (strcasecmp(str, "i2c") == 0)
        for (int i = 0; i < sizeof(walnutpi1b_pin_i2c) / (sizeof(int) * 2); i++)
            pins[walnutpi1b_pin_i2c[i][0]] = walnutpi1b_pin_i2c[i][1];
    else if (strcasecmp(str, "spi") == 0)
        for (int i = 0; i < sizeof(walnutpi1b_pin_spi) / (sizeof(int) * 2); i++)
            pins[walnutpi1b_pin_spi[i][0]] = walnutpi1b_pin_spi[i][1];
    printf("+-----------+------+----------+------+-----------+\n");
    printf("|    Mode   | Name | Physical | Name |    Mode   |\n");
    printf("+-----------+------+----------+------+-----------+\n");
    for (int ph = 1; ph <= 42; ph++)
    {
        if (pins[ph] > 0)
        {
            if (ph % 2 == 1)
                print_search_hit_l(ph, pins[ph]);
            else
            {
                print_search_hit_r(ph, pins[ph]);
                printf("\n");
            }
        }
        else
        {

            if (ph % 2 == 1)
                print_search_none_l(ph);
            else
            {
                print_search_none_r(ph);
                printf("\n");
            }
        }
        if (ph == 40)
            printf("+-----------+------+----------+------+-----------+\n");
    }
    printf("+-----------+------+----------+------+-----------+\n");
}
void print_all_gpio_on_ph()
{
    struct BOARD_PIN *board_pins = get_BOARD_PIN();
    for (int ph = 1; ph <= 42; ph++)
    {
        if (board_pins[ph].gpio_num >= 0)
            printf(" %d ", ph);
    }
}
void print_mode_name_inoutoff(int pin_num)
{
    printf("%s ", pin_get_mode_name_by_num(pin_num, 0));
    printf("%s ", pin_get_mode_name_by_num(pin_num, 1));
    printf("%s ", pin_get_mode_name_by_num(pin_num, 7));
}
