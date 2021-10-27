LED--PA8

红外传感器Infrared
右：INFRARED_PIN_R          PA14
左：INFRARED_PIN_L          PA15


电机Motor（TIM5）
PWM输出
    右电机：PA2
    左电机：PA3
方向控制
    IN1：PB0    IN2：PB1    IN3：PB12   IN4：PB13


舵机Rudder（TIM4） ch1
复用功能
PWM输出 PD12
脉冲宽度与舵机角度对应关系
0.5ms————-0度；
1.0ms————45度；
1.5ms————90度；
2.0ms———–135度；
2.5ms———–180度；



左编码器（TIME3）
引脚PA6，PA7

右编码器（TIME2）
引脚PA0，PA1

*****屏幕LCD PB4、PB5、PB6、PB7、PB8、PB9（没记错是这样的）****

LCD主要使用函数：

// 清空屏幕函数，参数是背景色
// LCD_Clear(BLACK);  

// 显示字符函数，参数分别是：x坐标、y坐标、前景色、背景色、字符串(字是8*16像素大小的)
// LCD_DrawFont_GBK16(2, 10, GREEN, BLACK, "这里只能是英文字符串");
// (0,0)              128
// ——————————————————>x
// |
// |
// |
// |
// | y(128)

// 显示数字函数,参数分别是：x坐标、y坐标、前景色、背景色、数字变量(整形或浮点型)
// SWK_LCD_DrawNum(60, 65, GREEN, BLACK, Number);
// 这个函数编译的时候可能会有个类型不匹配的警告，先不用管它，我还没想好咋解决，不影响


vofa+上位机使用了串口1

