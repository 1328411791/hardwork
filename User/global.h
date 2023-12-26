#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include "USART.h"

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long uint32_t;

/*A14_motor.c*/
#define PWM_DUTY          (Main_Fosc_KHZ / 10) // ����PWM�����ڣ�10KHz
#define PWM_HIGH_MIN      500                  // ����PWM�������Сռ�ձȡ�
#define PWM_HIGH_MAX      (PWM_DUTY - 1)       // ����PWM��������ռ�ձȡ�
#define Motor_Port        GPIO_P0
#define Right_MotoA_Pin   GPIO_Pin_0
#define Right_MotoB_Pin   GPIO_Pin_1
#define Left_MotoA_Pin    GPIO_Pin_2
#define Left_MotoB_Pin    GPIO_Pin_3
#define Right_MotoPWM_Pin GPIO_Pin_4
#define Left_MotoPWM_Pin  GPIO_Pin_5
#define LeftMotor_Go()                              \
    {                                               \
        GPIO_SetBits(Motor_Port, Left_MotoB_Pin);   \
        GPIO_ResetBits(Motor_Port, Left_MotoA_Pin); \
    }
#define LeftMotor_Back()                            \
    {                                               \
        GPIO_ResetBits(Motor_Port, Left_MotoB_Pin); \
        GPIO_SetBits(Motor_Port, Left_MotoA_Pin);   \
    }
#define LeftMotor_Stop()                            \
    {                                               \
        GPIO_ResetBits(Motor_Port, Left_MotoB_Pin); \
        GPIO_ResetBits(Motor_Port, Left_MotoA_Pin); \
    }
#define RightMotor_Go()                              \
    {                                                \
        GPIO_SetBits(Motor_Port, Right_MotoA_Pin);   \
        GPIO_ResetBits(Motor_Port, Right_MotoB_Pin); \
    }
#define RightMotor_Back()                            \
    {                                                \
        GPIO_ResetBits(Motor_Port, Right_MotoA_Pin); \
        GPIO_SetBits(Motor_Port, Right_MotoB_Pin);   \
    }
#define RightMotor_Stop()                            \
    {                                                \
        GPIO_ResetBits(Motor_Port, Right_MotoA_Pin); \
        GPIO_ResetBits(Motor_Port, Right_MotoB_Pin); \
    }
#define LeftMotorPWM(Speed)  TIM_SetCompare4(TIM1, Speed);
#define RightMotorPWM(Speed) TIM_SetCompare1(TIM1, Speed);
enum _motor_direction_ {
    FORWARD,
    BACKWARDS,
    TURNLEFT,
    TURNRIGHT,
    SPINTURNLEFT,
    SPINTURNRIGHT,
    STOP
};
extern void Motor_PWM_Init(void);
extern void Motor_Run(uint8_t dir, uint16_t speed);

/*TrackingDriver.c*/

#define S1_Pin P20
#define S2_Pin P21
#define S3_Pin P22
#define S4_Pin P23

void Tracking_Init(void);
uint8_t Tracking_Sensor(void);

/*OLED.c*/
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);

/*button.c*/
#define Button_Pin P30

void Button_Init(void);
uint8_t Button_Scan(void);

/*InfraredDriver.c*/
#define IR_PIN P33

void Infrared_Init();
void Infrared_Scan(void);
void Controller();

#define K_UP        0x46
#define K_DOWN      0x15
#define K_LEFT      0x44
#define K_RIGHT     0x43
#define K_STOP      0x45
#define K_SOUND     0x40
#define K_SPINLEFT  0x07
#define K_SPINRIGHT 0x09
#define K_0         0x19
#define K_1         0x0C
#define K_2         0x18
#define K_3         0x5E

/*RTCHBOT_timer.c*/
#define Timer0                    0
#define Timer1                    1
#define Timer2                    2
#define Timer3                    3
#define Timer4                    4

#define TIM_16BitAutoReload       0
#define TIM_16Bit                 1
#define TIM_8BitAutoReload        2
#define TIM_16BitAutoReloadNoMask 3

#define TIM_CLOCK_1T              0
#define TIM_CLOCK_12T             1
#define TIM_CLOCK_Ext             2

typedef struct
{
    uint8_t TIM_Mode;      // ����ģʽ,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
    uint8_t TIM_Polity;    // ���ȼ�����	PolityHigh,PolityLow
    uint8_t TIM_Interrupt; // �ж�����		ENABLE,DISABLE
    uint8_t TIM_ClkSource; // ʱ��Դ		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
    uint8_t TIM_ClkOut;    // �ɱ��ʱ�����,	ENABLE,DISABLE
    uint16_t TIM_Value;    // װ�س�ֵ
    uint8_t TIM_Run;       // �Ƿ�����		ENABLE,DISABLE
} TIM_InitTypeDef;

extern int Timer_Inilize(uint8_t TIM, TIM_InitTypeDef *TIMx);
extern void SysTick_Init(void);
extern uint32_t time_GetTicks(void);
extern void DelayMs(uint16_t ms);

/*delay.c*/
extern void DelayMs(uint16_t ms);
extern void DelayUs(uint16_t us);

/*uart.c*/
extern void Usart1_Init(uint16_t t_baud);
extern uint8_t uart1_Read(void *vbuf, uint8_t len);
extern void uart1_Write(const void *vbuf, uint8_t len);

/*tracking.c*/
void Tracking(void);

/*Controller.c*/
void Controller(int *flag);

#endif