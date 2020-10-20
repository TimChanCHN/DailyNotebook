#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "key.h"   
#include "stmflash.h" 
#include "iap.h"   

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
	u32 updateSta = 0;	// ����״̬λ
  u32 binLength = 0;	// ��APP����

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	// �жϸ���λ״̬
	// ����11�������Ǹ���λ״̬--0xAAAAAAAA(��ַ��0x080FFFFC)
	// ����11�����ڶ����ֽ���APP2����	--(��ַ��0x080FFFF8)
	STMFLASH_Read(UPDATEREG, &updateSta, 1);
	printf("[bootloader]update status : 0x%x\r\n", updateSta);
	STMFLASH_Read(BINLENREG, &binLength, 1);
	if (binLength == 0xFFFFFFFF)
		binLength = 0;
	printf("bin length : %d\r\n", binLength);
	
	// ���Ը��³���
	if (updateSta == 0xAAAAAAAA)
	{
		u32 reset = 0xFFFFFFFF;
//		u8 tmp = 0;
//		int i = 0;
//		u32 app1 = APP1ADDR;
//		u32 app2 = APP2ADDR;
		
		printf("updating...\r\n");
		iap_copy_app1_from_app2(APP1ADDR, APP2ADDR, binLength);
		
//		printf("-----------APP1---------------\r\n");
//		// ��ӡAPP1������
//		for (i = 0; i < binLength; i++)
//		{
//			tmp = STMFLASH_ReadByte(app1++);
//			printf ("0x%x*", tmp);
//		}
//		printf("\r\n");
//		
//		printf("-----------APP2---------------\r\n");		
//		// ��ӡAPP2������
//		for (i = 0; i < binLength; i++)
//		{
//			tmp = STMFLASH_ReadByte(app2++);
//			printf ("0x%x*", tmp);
//		}
//		printf("\r\n");
		
		// ��λ״̬λ
		STMFLASH_Write(UPDATEREG, &reset, 1);
	}
	else
	{
		printf("there is no APP to be updated!\r\n");
	}
	
	delay_ms(1000);
	printf("APP start to work... \r\n\r\n");
	iap_load_app(APP1ADDR);
}

