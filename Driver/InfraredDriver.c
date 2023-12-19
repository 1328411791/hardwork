#include "global.h"
// 红外接收模块

char str[16];
unsigned char i, j;
uint8_t IR_Data[4]    = {0}; // 存储红外数据
unsigned int IR_Count = 0, IR_HighTime = 0;
uint16_t IR_Flag = 0;

void Infrared_Init(uint16_t *flag)
{
    // 设置为INT0 中断
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
    GPIO_InitStructure.GPIO_Pin  = Infrared_Pin;
    GPIO_Init(GPIO_P3, &GPIO_InitStructure);

    // 设置INT1中断
    IT1 = 1; // INT1下降沿触发
    EX1 = 1; // INT1中断允许
    EA  = 1; // 总中断允许
}

void Infrared_Scan() interrupt INT1_VECTOR
{
    EA = 0;
    DelayMs(9); // 延时9ms
    if (Infrared_Pin == 0) {
        IR_Count = 1000;
        while (!Infrared_Pin && IR_Count) // 等待引导信号9ms低电平结束，若超过10ms强制退出
        {
            DelayUs(10); // 1000*10us
            IR_Count--;
            if (IR_Count == 0)
                return;
        }
        if (Infrared_Pin) // 引导信号9ms低电平已过，进入4.5ms高电平
        {
            IR_Count = 500;
            while (Infrared_Pin && IR_Count) // 等待引导信号4.5ms高电平结束，若超过5ms强制退出
            {
                DelayUs(10);
                IR_Count--;
                if (IR_Count == 0) return;
            }
            for (i = 0; i < 4; i++) // 循环4次，读取4个字节数据
            {
                for (j = 0; j < 8; j++) // 循环8次读取每位数据即一个字节
                {
                    IR_Count = 600;
                    while (!Infrared_Pin && IR_Count) // 等待数据1或0前面的0.56ms结束，若超过6ms强制退出
                    {
                        DelayUs(10);
                        IR_Count--;
                        if (IR_Count == 0) return;
                    }
                    IR_Count = 20;
                    while (Infrared_Pin) // 等待数据1或0后面的高电平结束，若超过2ms强制退出
                    {
                        DelayUs(100);
                        IR_HighTime++;
                        if (IR_HighTime > 20) return; // 20*100us
                    }
                    IR_Data[i] >>= 1;    // 先读取的为低位，然后是高位
                    if (IR_HighTime > 8) // 如果高电平时间大于0.8ms，数据则为1，否则为0
                        IR_Data[i] |= 0x80;
                    IR_HighTime = 0; // 重新清零，等待下一次计算时间
                }
            }
        }
    }
    if (IR_Data[2] != ~IR_Data[3]) // 校验控制码与反码，错误则返回
    {
        for (i = 0; i < 4; i++)
            IR_Data[i] = 0;
        return;
    }
    //OLED_Clear();
    //sprintf(str, "%X %X", IR_Data[0], IR_Data[1], IR_Data[2], IR_Data[3]);
    //OLED_ShowString(1, 1, str);
    sscanf(str, "%X %X", &IR_Data[0], &IR_Flag);
    IR_Flag = IR_Flag >> 8;
    sprintf(str, "%X", IR_Flag);
    OLED_ShowString(4, 1, str);
    //DelayUs(500);
    EA = 1;
}

uint16_t get_Flag()
{
    return IR_Flag;
}
