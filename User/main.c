#include "global.h" // Device heade

uint8_t opt;
char str1[16];

void System_Init(void)
{
    SysTick_Init();
    DelayMs(1);
    Motor_PWM_Init();
    OLED_Init();
    Usart1_Init(9600);
    Tracking_Init();
    DelayMs(100);
    Button_Init();
    Infrared_Init();
}

void main(void)
{
    // 初始化
    System_Init();

    opt = 2;
    while (TRUE) {
        switch (opt) {
            case 1:
                OLED_ShowString(4, 1, "1.Tracking");
                Tracking();
                break;
            case 2:
                Controller();
            default:
                sprintf(str1, "%X", get_Flag());
                OLED_ShowString(3, 1, str1);
                OLED_ShowString(4, 1, "Default");
                break;
        }
        DelayMs(1000);
    }
    for (;;) {
    }
}