#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "key.h"   
#include "stmflash.h" 
#include "iap.h"   

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
	u32 updateSta = 0;	// 更新状态位
  u32 binLength = 0;	// 新APP长度

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	// 判断更新位状态
	// 扇区11最后的字是更新位状态--0xAAAAAAAA(地址是0x080FFFFC)
	// 扇区11倒数第二个字节是APP2长度	--(地址是0x080FFFF8)
	STMFLASH_Read(UPDATEREG, &updateSta, 1);
	printf("[bootloader]update status : 0x%x\r\n", updateSta);
	STMFLASH_Read(BINLENREG, &binLength, 1);
	if (binLength == 0xFFFFFFFF)
		binLength = 0;
	printf("bin length : %d\r\n", binLength);
	
	// 可以更新程序
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
//		// 打印APP1的数据
//		for (i = 0; i < binLength; i++)
//		{
//			tmp = STMFLASH_ReadByte(app1++);
//			printf ("0x%x*", tmp);
//		}
//		printf("\r\n");
//		
//		printf("-----------APP2---------------\r\n");		
//		// 打印APP2的数据
//		for (i = 0; i < binLength; i++)
//		{
//			tmp = STMFLASH_ReadByte(app2++);
//			printf ("0x%x*", tmp);
//		}
//		printf("\r\n");
		
		// 复位状态位
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

