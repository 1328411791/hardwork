#include "global.h" // Device heade

uint8_t opt;
int Flag = 0;
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
    Infrared_Init(&Flag);
}

void main(void)
{
    // 初始化
    System_Init();

    opt = 4;

    while (TRUE) {
        OLED_Clear();
        switch (opt) {
            case 1:
                OLED_ShowString(4, 1, "1.Tracking");
                Tracking();
                break;
            case 2:
                OLED_ShowString(4, 1, "2.Controller");
                Controller(&Flag);
                break;
            default:
                sprintf(str1, "%X", Flag);
                OLED_ShowString(3, 1, str1);
                OLED_ShowString(4, 1, "Default");
                break;
        }
        DelayMs(100);
    }
}