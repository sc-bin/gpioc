# gpioc
本项目是一个在linux下控制gpio的库，提供`Python` 、`C` 、 `shell` 3种调用方式

通过直接控制底层寄存器的方式，能强制使用那些被分配给其他驱动使用的引脚

## c
`example-c`文件夹下有例程
1. 编写代码的时候调用头文件`#include "gpio.h"`
2. 编译代码的时候使用`-lgpio`,如`gcc main.c -lgpio -o exe`

操作寄存器需要以管理员权限运行，当代码以普通用户运行时底层会通过与一个后台服务通信来间接操作寄存器，速度会慢一点点
```
    while (1)
    {
        pin_write(LED, 1);
        pin_write(LED, 0);
    }
```
以管理员权限运行时，高电平与低电平的时长都接近1us，示波器测算频率为530k
以普通用户运行时，高电平与低电平的时长都接近250us，示波器测算频率为2.3k


## shell命令
所有命令都支持自动补全，按两下TAB键就能查看有哪些可选参数

查看所有引脚的状态
------
```
gpio pins
```
命令行输入上面的命令，就会输出一张大表格，其中每一列的含义如下
- `Physical` : 板上排针的编号，后续命令操作时都使用此编号，C语言编程时也使用此编号
- `Name` : 引脚名称，在python编程时可使用此名称
- `mode`: 引脚当前所处工作模式：
    - `OFF`: 初始状态未设置
    - `IN`: 输入模式
    - `OUT`: 输出模式
    - `其他`: 引脚复用功能
- `V` : 当引脚为 IN/OUT 模式时，引脚的电平状态，1为高电平，0为低电平


查看pwm/uart等引脚的位置
------
```
gpio pin [function]
```
会输出一张表格显示具备该功能的引脚的位置
- `[function]`:功能类型，可选择以下几个选项
    - `pwm`
    - `uart`
    - `spi`
    - `i2c`

例如我想知道板子旁边那堆引脚里，有哪些是硬件pwm引脚，则可以输入以下命令，会输出一个表格
```
gpio pin pwm
```

设置引脚功能
------
```
gpio mode [PIN] [mode]
```
- `[PIN]`:目标引脚的排针编号，
- `[mode]`: 在下面几种中间选择:
    - `IN` : 输入模式,浮空
    - `IN_PULLUP` : 输入模式,开启内部上拉
    - `IN_PULLDOWN` : 输入模式,开启内部下拉
    - `OUT` : 输出模式
    - `OFF` : 回归初始未使用状态

例如我想把核桃派1b上编号为41的板载按键设置为上拉输入，则在命令行输入如下
```
gpio mode 41 IN_PULLUP
```


读取引脚输入电平
------
```
gpio read [PIN]
```
- `[PIN]` 目标引脚的排针编号

例如我想读取核桃派1b上编号41的板载按键的输入状态，就在命令行输入如下
```
gpio read 41
```


控制引脚输出
------
```
gpio write [PIN] [VALUE]
```
- `[PIN]` 目标引脚的排针编号
- `[VALUE]` 为1或0。

例如我想让核桃派1b上编号42的板载led输出高电平
```
gpio write 42 1
```


翻转引脚输出电平
------
```
gpio toggle [PIN]
```
- `[PIN]` 目标引脚的排针编号

让一个处于输出模式的引脚，输出的电平翻转，即42号脚本来输出1，执行完这个命令就会变成0，本来是0，执行完就会变成1。
```
gpio toggle 42
```