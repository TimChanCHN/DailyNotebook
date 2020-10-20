#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "usmart.h"
#include "rtc.h"
#include "stmflash.h"

/***********************************************************
 *  bootloader����ʼ��ַ0x08000000,��С0x10000(64K)
 *  APP1:				��ʼ��ַ0x08010000,��С0x70000(448K)
 *	APP2:				��ʼ��ַ0x08080000,��С0x60000(384K)
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
	
	SCB->VTOR = FLASH_BASE | 0x10000;//����ƫ����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	usmart_dev.init(84); 	//��ʼ��USMART	
	LED_Init();					  //��ʼ��LED
	My_RTC_Init();		 		//��ʼ��RTC
 
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//����WAKE UP�ж�,1�����ж�һ��
	
	while(1) 
	{		
		t++;
		if((t%100)==0)	//ÿ1s����һ����ʾ����
		{
			RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
			
			sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
			//printf("%s ", tbuf);
			
			RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
			
			sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 
			//printf("%s ", tbuf);
			
			sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.RTC_WeekDay); 
			// printf("%s\r\n\r\n", tbuf);
			
			// ����Ƿ������ݽ��ղ��ҽ������
			if (check_receive_finish(&applenth[0]))
			{
				// app�����λ��CRC16У����
				uint32_t applen = applenth[0]-2;
				uint16_t crcGet = 0;
				uint16_t crcRes = (USART_RX_BUF[applenth[0]-2] << 8) | USART_RX_BUF[applenth[0]-1];
				
				crcGet = crc16(USART_RX_BUF, applen);

				// ��APP����CRC16����
				if (crcGet == crcRes)
				{
					// ����ͨ�����ѽ��յ����ݴ�ŵ�APP2��
					printf("�û�����У��ɹ�!\r\n");
					STM32FLASH_write_appbin(APP2ADDR, USART_RX_BUF, applenth[0]);
					printf("���볤��:%dBytes\r\n",applenth[0]);
					
					STMFLASH_Write(BINLENREG, applenth, 2);
					printf("�����ɹ�!׼����λ...\r\n");
					delay_ms(2000);
					
					// ����ϵͳ
					NVIC_SystemReset();
				}
				else
				{
					printf("�û�����У��ʧ��!\r\n");
					printf("����ִ�оɳ���!\r\n");
				}
			}
		} 
		
		if((t%20)==0)
			LED0=!LED0;	//ÿ200ms,��תһ��LED0 
		
		delay_ms(10);
	}	
}
