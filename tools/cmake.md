# CMAKE整理
[CMAKE使用教程](https://blog.csdn.net/zhuiyunzhugang/article/details/88142908)
## 1. 安装CMAKE(linux环境)
sudo apt install cmake

## 2. 使用
1. 所需文件：
   1. 源文件：.c/.cpp/.h
   2. CMakeList.txt
2. CMakeList.txt文件编写
   1. cmake_minimum_required (VERSION 2.8)--指定cmake最低版本
   2. project--项目名称
   3. AUX_SOURCE_DIRECTORY(. SRC_LIST)--查找当前目录下的所有源文件，并把名称保存到SRC_LIST变量中
		- 也可以利用set(SRC_LIST ${real_src_files})，设置SRC_LIST变量代表所有的.c/.cpp文件
   4. add_subdirectory(math)--添加子目录<math>
   5. add_executable(hello ${SRC_LIST})--根据源文件生成指定可执行文件
		> 子目录math中也会有一个CMakeList.txt文件，生成的可执行文件是hello
   6. target_link_libraries(hello MathFunctions)--添加链接库
		> 链接库的设置如同设置源文件一样，若是固定路径的.a/.so，则需要全部路径
		> 若是系统默认的库，则直接加库名即可，各个库之间使用空格/enter隔开
	7. set_target_properties(target PROPERTIES SPECIFIC_PRO PARAM):设置目标特性
		> target:目标，如输出的可执行文件
		> PROPERTIES：属性关键字
		> SPECIFIC_PRO：具体的属性，如RUNTIME_OUTPUT_DIRECTORY,指定的属性可执行程序的输出路径
		> PARAM:参数，对应${SPECIFIC_PRO}的值
	8. message("string"):字符串输出，如echo，但string中包含${}字样，则输出里面宏所替代的内容
	9. option(USE_COMPILE "Use Compile" ON):如同设置宏开关
	10. set(NAME "this is test")：令NAME="this is test"；
		string(APPEND NAME "this is another line"):令NAME的后面为"this is another line"
	11. add_custom_target(target
			COMMAND ${real command}
			DEPENDS dependences)
		> target:在生成的makefile中的一个依赖
		> COMMAND:完成改目标所要执行的操作，生成make target即会执行这些命令
		> dependences:执行该命令所需要的依赖

## 3. 其他设置
1. 添加编译器选项
   1. `add_compile_options`:针对所有编译器
   2. set命令设置`CMAKE_C_FLAGS`或`CMAKE_CXX_FLAGS`:只针对C/C++编译器

## ERROR
1. 安装cmake报错：Cannot find appropriate Makefile processor on this system.
   1. 解决：apt-get install build-essential
   2. 