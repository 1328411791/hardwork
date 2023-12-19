// 按键驱动
#include "global.h"

void Button_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_InitStructure.GPIO_Pin  = Button_Pin;
    GPIO_Init(GPIO_P3, &GPIO_InitStructure);
}

uint8_t Button_Scan(void)
{
    // 1为按下，0为未按下
    // 读取按键数据
    if (Button_Pin == 0) {
        return 1;
    } else {
        return 0;
    }
}