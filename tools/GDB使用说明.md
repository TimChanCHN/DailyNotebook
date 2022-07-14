# GDB使用说明
[参考链接1](https://blog.csdn.net/horotororensu/article/details/82256832)
[参考链接2](https://blog.csdn.net/niyaozuozuihao/article/details/91802994)
[利用GDB解决coredump问题](https://zhuanlan.zhihu.com/p/46605905)
1. 启动
  1. 编译时需要加上`-g`选项；
  2. 若是用Makefile构建程序，则在`CFLAGS`中添加`-g`选项：`CFLAGS := -Wall -O2 -g`
  
2. 使用
  1. 启动：`gdb + 可执行程序`
  2. 设置断点：
    ```bash
      b 函数名:对当前正在执行的文件中的指定函数设置断点  
      b 行号:对当前正在执行的文件中的特定行设置断点 
      b <文件名:行号>:对指定文件的指定行设置断点，最常用的设置断点方式  
      b <文件名:函数名>:对指定文件的指定函数设置断点  
      b <+/-偏移量>：当前指令行+/-偏移量出设置断点  
      b <*地址>:指定地址处设置断点  
      info b:查看断点信息  
    ```
  3. 运行:r
  4. 显示变量:info reg
  5. 单步执行:
    1. next:一行一行地执行源码，遇到函数不进入
    2. setp:一行一行地执行源码，遇到函数进入
  6. 继续执行:continue/c
  7. 显示变量:print var
  8. 显示变量数据类型:whatis var
  9. 清除断点
  ```bash
   delete(d)+<断点编号>：删除指定断点
   clear+<函数名>/<行号>/<文件名:行号>/<文件名:函数名> :删除指定断点
   disable + <断点编号>:禁用指定断点,断点编号为空，指禁止全部断点
   enable + <断点编号>:使能指定断点,断点编号为空，指使能全部断点
  ```
  10. 查看源码:l
3. 工具链使用gdb单步调试
   1. 单片机使用工具链进行开发，而不使用IDE时，如何实现单步调试？
      1. 使用`openocd+arm-none-eabi-gdb+J-Link/StLink`
   2. 过程
      1. 打开一个终端1，输入`openocd -f ../sdk/scripts/openocd/stlink-v2.cfg -f ../sdk/scripts/openocd/hk32f1x.cfg -c init -c 'reset halt'`
      2. 再打开一个终端2，执行gdb命令`arm-none-eabi-gdb`
      3. 在终端2，输入`target remote :3333`，而后在终端1看到`accepting 'gdb' connection on tcp/3333`等信息，说明链接成功，可以利用gdb进行单步调试
    
