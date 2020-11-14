# LwIP系统框架
## 1. LwIP系统框架内容
1. 底层与内核间的数据交互
2. 应用程序到内核间的数据交互

## 2. 网卡接收数据流程
1. eth接收数据并产生中断，中断释放信号量通知网卡接收线程处理接收数据；
2. 接收线程对数据进行封装，投递到tcpip_mbox邮箱
3. LwIP内核线程获得消息，并对消息进行解析，根据消息中数据包类型进行处理
   1. 实际上是调用`ethernet_input()`函数决定将数据递交给IP层还是ARP缓存表
![网卡数据传入LwIP内核流程](https://gitee.com/timchanchn/pictures/raw/master/daily/LwIP/%E7%BD%91%E5%8D%A1%E4%B8%8E%E5%86%85%E6%A0%B8%E6%95%B0%E6%8D%AE%E4%BA%A4%E4%BA%92%E6%B5%81%E7%A8%8B.png)

## 3. 内核超时处理
1. 类似于RT-Thread的超时处理，LwIP的内核也有类似的超时处理机制：
   1. 使用结构体`sys_timeo`描述超时事件，同时还使用链表管理`next_timeout`当前所有的超时事件
   2. 当需要对超时事件进行管理时，先使用API函数`sys_timeout`把该事件按照时间升序的顺序进行管理
   3. 对于循环超时事件，使用结构体`lwip_cyclic_timer`进行描述，但这些事件也是放到超时事件管理链表中进行管理，对于循环超时事件，每次处理完回调函数后，会通过函数`lwip_cyclic_timer`将其重新注册到超时链表中
   4. 检查超时事件:定时调用API`tcpip_timeouts_mbox_fetch`,在该函数中对超时事件进行判断，若发生超时事件，则调用`sys_check_timeouts`去检查超时事件

## 4. tcpip_thread线程
1. 调用`tcpip_timeouts_mbox_fetch`等待消息，此处是非阻塞等待邮箱中的消息
2. 当有消息时，调用`tcpip_thread_handle_msg`对消息进行处理

## 5. LwIP消息
1. LwIP中消息有多种结构，不同的消息其封装也是不一样的，`tcpip_thread`线程通过`tcpip_msg`描述消息，而`tcpip_thread`接收到消息后，根据消息类型进行不同处理
2. LwIP利用`tcpip_msg_type`枚举类型定义了系统中可能出现的类型，而消息结构`tcpi_msg`中msg字段是一个共用体，意味着`tcpip_msg`字段中指定地址都是用于存储消息类型
3. 数据包消息
   1. 对于每种类型的消息，LwIP内核都必须有一个产生与之对应的消息函数，在产生该类型的消息后就将其投递到系统邮箱`tcpip_mbox`中，从而`tcpip_thread`就可以从邮箱中得到消息并处理  
   2. 通过API`tcpip_input`对消息进行构造并投递
   3. `tcpip_input`会调用`tcpip_inpkt`完成实际的消息构造
   ![数据包消息运作流程](https://gitee.com/timchanchn/pictures/raw/master/daily/LwIP/%E6%95%B0%E6%8D%AE%E5%8C%85%E6%B6%88%E6%81%AF%E4%BC%A0%E9%80%92%E6%B5%81%E7%A8%8B.png)
4. API消息
   1. 使用`api_msg`描述API消息内容，包括链接信息conn、内核返回结果err、消息msg
   2. API消息由用户线程发出，再与内核进行交互，因为用户的应用程序并不是与内核在统一线程中(其实就是用户使用NETCONN API接口时)，LwIP会将对应API函数与参数搞糟成消息传递到`tcpip_thread`线程中，然后根据相应的API函数进行对应操作。
   3. 投递API消息投递函数`netconn_apimsg`,在NETCONN API中构造完成数据包，便调用该函数进行投递消息，完成用户线程与`tcpip_thread`的信息交互
   ![API消息运作流程](https://gitee.com/timchanchn/pictures/raw/master/daily/LwIP/API%E6%B6%88%E6%81%AF%E4%BC%A0%E9%80%92%E6%B5%81%E7%A8%8B.png)



