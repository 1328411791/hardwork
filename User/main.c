#include "global.h" // Device heade

uint8_t opt;

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

    opt = 4;

    switch (opt) {
        case 1:
            OLED_ShowString(4, 1, "1.Tracking");
            Tracking();
            break;
        default:
            OLED_ShowString(4, 1, "Default");
            break;
    }
}