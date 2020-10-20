#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "stmflash.h"

/***********************************************************
 *  bootloader����ʼ��ַ0x08000000,��С0x10000(64K)
 *  APP1:				��ʼ��ַ0x08010000,��С0x78000(480K)
 *	APP2:				��ʼ��ַ0x08088000,��С0x78000(480K)
 ***********************************************************/
#define BOOTADDR	0x08000000
#define BOOTSIZE	0x10000
#define APP1ADDR	0x08010000
#define	APP1SIZE	0x78000
#define	APP2ADDR	0x08088000
#define	APP2SIZE	0x77FF8					// ���Ը���λ����Сλ

#define UPDATEREG	0x080FFFFC
#define BINLENREG 0x080FFFF8


int main(void)
{ 
	u8 t=0;
	u32 applenth[2] = {0, 0xAAAAAAAA};
	
	SCB->VTOR = FLASH_BASE | 0x10000;//����ƫ����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					  //��ʼ��LED

	while(1) 
	{		
		t++;
		if((t%100)==0)	//ÿ1s����һ����ʾ����
		{
			printf("[APP2]This is APP2\r\n");
			
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
