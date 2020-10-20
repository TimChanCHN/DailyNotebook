# Readme   
1. APP1--基于正点原子的RTC实验，LED1\LED2同时闪，实时接收串口1发送过来的bin文件
2. APP2--LED1闪，实时接收串口1发送过来的bin文件
3. IAP Bootloader V1.1--bootloader，先检查更新位，若无需更新，则直接跳去APP1，否则把APP2拷贝到APP1，之后再跳去APP1，执行新程序
4. addcrc.cpp--在linux中运行，目的是在其bin文件尾部增加CRC校验码，以实现固件升级的CRC校验，保证传输过程的正确性

