#include "stm32f10x.h"
#include "Delay.h"

// 按键初始化
void Key_Init(void) {
    // 启用 GPIOB 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 配置按键引脚为上拉输入模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        // 上拉输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_1;  // 配置 PB1 和 PB11
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    // 引脚速度
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// 获取按键编号
uint8_t Key_GetNum(void) {
    uint8_t KeyNum = 0;

    // 检测按键是否按下 (低电平有效)
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {  // 检测 PB1
        Delay_ms(20);                                     // 消抖
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {  // 再次确认按键状态
            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);  // 等待按键松开
            Delay_ms(20);                                 // 再次消抖
            KeyNum = 1;                                   // 按键1被按下
        }
    } else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0) {  // 检测 PB11
        Delay_ms(20);                                             // 消抖
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0) {     // 再次确认按键状态
            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);  // 等待按键松开
            Delay_ms(20);                                         // 再次消抖
            KeyNum = 2;                                           // 按键2被按下
        }
    }

    return KeyNum;
}
