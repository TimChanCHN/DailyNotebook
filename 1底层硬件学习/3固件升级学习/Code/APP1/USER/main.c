#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "usmart.h"
#include "rtc.h"
#include "stmflash.h"

/***********************************************************
 *  bootloader：起始地址0x08000000,大小0x10000(64K)
 *  APP1:				起始地址0x08010000,大小0x70000(448K)
 *	APP2:				起始地址0x08080000,大小0x60000(384K)
 ***********************************************************/
#define BOOTADDR	0x08000000
#define BOOTSIZE	0x10000
#define APP1ADDR	0x08010000
#define	APP1SIZE	0x70000
#define	APP2ADDR	0x08080000
#define	APP2SIZE	0x60000					

#define UPDATEREG	0x080FFFFC
#define BINLENREG 0x080FFFF8


int main(void)
{ 

	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;

	u8 tbuf[40];
	u8 t=0;
	u32 applenth[2] = {0, 0xAAAAAAAA};
	
	SCB->VTOR = FLASH_BASE | 0x10000;//设置偏移量
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	usmart_dev.init(84); 	//初始化USMART	
	LED_Init();					  //初始化LED
	My_RTC_Init();		 		//初始化RTC
 
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//配置WAKE UP中断,1秒钟中断一次
	
	while(1) 
	{		
		t++;
		if((t%100)==0)	//每1s更新一次显示数据
		{
			RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
			
			sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
			//printf("%s ", tbuf);
			
			RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
			
			sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 
			//printf("%s ", tbuf);
			
			sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.RTC_WeekDay); 
			// printf("%s\r\n\r\n", tbuf);
			
			// 检查是否有数据接收并且接收完成
			if (check_receive_finish(&applenth[0]))
			{
				// app最后两位是CRC16校验码
				uint32_t applen = applenth[0]-2;
				uint16_t crcGet = 0;
				uint16_t crcRes = (USART_RX_BUF[applenth[0]-2] << 8) | USART_RX_BUF[applenth[0]-1];
				
				crcGet = crc16(USART_RX_BUF, applen);

				// 对APP进行CRC16检验
				if (crcGet == crcRes)
				{
					// 检验通过，把接收的内容存放到APP2中
					printf("用户程序校验成功!\r\n");
					STM32FLASH_write_appbin(APP2ADDR, USART_RX_BUF, applenth[0]);
					printf("代码长度:%dBytes\r\n",applenth[0]);
					
					STMFLASH_Write(BINLENREG, applenth, 2);
					printf("升级成功!准备复位...\r\n");
					delay_ms(2000);
					
					// 重启系统
					NVIC_SystemReset();
				}
				else
				{
					printf("用户程序校验失败!\r\n");
					printf("继续执行旧程序!\r\n");
				}
			}
		} 
		
		if((t%20)==0)
			LED0=!LED0;	//每200ms,翻转一次LED0 
		
		delay_ms(10);
	}	
}
