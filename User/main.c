#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Ds18b20.h"
#include "LED.h"

int main(void)
{
    // 初始化OLED
    OLED_Init();
    OLED_ShowString(1, 1, "Temperature:");
    LED_Init();

    ds18b20_init();
    unsigned short value;

    while(1)
    {
        // 启动温度转换
        DS18B20StartConvert();

        // 等待温度转换完成（750ms）
        Delay_ms(750);

        // 读取温度值
        value = ds18b20_read();

        // 处理温度数据，value为16位，其中高8位为整数部分，低8位为小数部分
        unsigned char temp_integer = value / 10;   // 整数部分
        unsigned char temp_decimal = value % 10;   // 小数部分

        // 显示整数部分
        OLED_ShowNum(2, 2, temp_integer, 2);  // 显示整数部分

        // 显示小数点
        OLED_ShowString(2, 4, ".");

        // 显示小数部分
        OLED_ShowNum(2, 5, temp_decimal, 1);  // 显示小数部分

        OLED_ShowChinese(5,3,1);
    
        // 显示单位℃
        Delay_ms(250);

        // 如果温度大于等于30，打开LED2，否则关闭LED2
        if (temp_integer >= 30)
        {
            LED2_ON();
        }
        else
        {
            LED2_OFF();
        }
    }
}
