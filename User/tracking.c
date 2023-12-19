#include "global.h"

void Tracking()
{
    while (TRUE) {
        // 寻迹小车
        // 1. 读取传感器数据
        uint8_t sensor = Tracking_Sensor();

        char str[10];
        sprintf(str, "0x%X", sensor);
        OLED_ShowString(1, 1, str);
        // 2. 根据传感器数据控制电机
        if (sensor == 0x0) {
            // S1-S4未检测到黑线
            // 前进
            Motor_Run(FORWARD, PWM_DUTY / 100 * 70);
        } else if (sensor == 0x01) {
            Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 50);
        } else if (sensor == 0x02) {
            Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 70);
        } else if (sensor == 0x03) {
            Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 70);
        } else if (sensor == 0x04) {
            Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 70);
        } else if (sensor == 0x05) {
            Motor_Run(FORWARD, PWM_DUTY / 100 * 50);
        } else if (sensor == 0x06) {
            Motor_Run(FORWARD, PWM_DUTY / 100 * 50);
        } else if (sensor == 0x07) {
            Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 70);
        } else if (sensor == 0x08) {
            Motor_Run(FORWARD, PWM_DUTY / 100 * 50);
        } else if (sensor == 0x09) {
            Motor_Run(FORWARD, PWM_DUTY / 100 * 50);
        } else if (sensor == 0x0A) {
            Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 70);
        } else if (sensor == 0x0B) {
            Motor_Run(TURNRIGHT, PWM_DUTY / 100 * 50);
        } else if (sensor == 0x0C) {
            Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 70);
        } else if (sensor == 0x0D) {
            Motor_Run(TURNLEFT, PWM_DUTY / 100 * 50);
        } else if (sensor == 0x0E) {
            Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 70);
            DelayUs(100);
        } else if (sensor == 0x0F) {
            Motor_Run(FORWARD, PWM_DUTY / 100 * 50);
        } else {
            OLED_ShowString(2, 1, "sensor error");
        }
    }
}