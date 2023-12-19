// 四路寻迹模块驱动
#include "global.h"

void Tracking_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_InitStructure.GPIO_Pin  = S1_Pin | S2_Pin | S3_Pin | S4_Pin;
    GPIO_Init(GPIO_P2, &GPIO_InitStructure);
}
uint8_t Tracking_Sensor(void)
{
    // 1为检测到黑线，0为未检测到黑线
    // 读取传感器数据
    uint8_t sensor_data = 0;
    if (S1_Pin == 0) {
        sensor_data |= 0x01;
    }
    if (S2_Pin == 0) {
        sensor_data |= 0x02;
    }
    if (S3_Pin == 0) {
        sensor_data |= 0x04;
    }
    if (S4_Pin == 0) {
        sensor_data |= 0x08;
    }
    return ((~sensor_data) << 4)>>4;
}