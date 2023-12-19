#include "global.h"

char str2[16];
uint16_t C_FLAG = 0;

void Controller()
{
    C_FLAG = get_Flag();
    while (TRUE) {
        C_FLAG = get_Flag();
        sprintf(str2, "%X", C_FLAG);
        OLED_ShowString(3, 1, str2);

        switch (C_FLAG) {
            case K_UP:
                Motor_Run(FORWARD, PWM_DUTY / 100 * 30);
                C_FLAG = 0;
                break;
            case K_DOWN:
                Motor_Run(BACKWARDS, PWM_DUTY / 100 * 30);
                C_FLAG = 0;
            case K_LEFT:
                Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 30);
                C_FLAG = 0;
                break;
            case K_RIGHT:
                Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 370);
                C_FLAG = 0;
                break;
            case K_STOP:
                Motor_Run(STOP, 0);
                C_FLAG = 0;
                break;
            default:
                Motor_Run(STOP, 0);
                break;
        }
        DelayUs(100);
    }
}