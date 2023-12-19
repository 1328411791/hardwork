#include "global.h"

uint16_t *C_FLAG;
char str2[16];

void Controller(uint16_t *flag)
{
    C_FLAG = flag;
    while (TRUE) {
        sprintf(str2, "%X", *C_FLAG);
        OLED_ShowString(3, 1, str2);

        switch (*C_FLAG) {
            case K_UP:
                Motor_Run(FORWARD, PWM_DUTY / 100 * 70);
                *C_FLAG = 0;
                break;
            case K_DOWN:
                Motor_Run(BACKWARDS, PWM_DUTY / 100 * 70);
                *C_FLAG = 0;
            case K_LEFT:
                Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 70);
                *C_FLAG = 0;
                break;
            case K_RIGHT:
                Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 70);
                *C_FLAG = 0;
                break;
            case K_STOP:
                Motor_Run(STOP, 0);
                *C_FLAG = 0;
                break;
            default:
                Motor_Run(STOP, 0);
                break;
        }
        DelayUs(100);
    }
}