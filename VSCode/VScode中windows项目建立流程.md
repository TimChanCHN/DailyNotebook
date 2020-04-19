# VScode中建立项目流程
> [参考例程](https://blog.csdn.net/zhangxiaoshuoyu/article/details/82745950)

1. 环境配置
    1. 本地编译器：MingW, 安装后，并把安装路径添加到可执行程序中即可

2. 文件配置
    1. 基本配置
        1. 打开命令窗口，输入C/Cpp:Edit Configurations，创建出文件c_cpp_properties.json；
        2. 文件作用：配置编译器，头文件路径；
        3. 重要参数：includePath、compilerPath
    
    2. 生成.exe控制台程序
        1. 命令行输入Tasks: Configure Tasks 生成 task.json
        2. 文件作用：生成exe可执行程序
        3. 重要参数：
        > label:标签，在launch.json中会用到  
        > command:  
        > args:编译命令参数：第一个参数为源文件，最后一个参数是目标文件，中间的选项是可选选项，"-o"必须要有
    
    3. 添加group信息
        1. 命令行输入Tasks:Run Build Task， task.json即可以自动生成

    4. 编写代码文件

    5. 配置launch.json
        1. Debug，start debug ,选择C++ (GDB/LLDB)
        2. 作用：引导编译
        3. 重要参数：
        > program: ${workspaceFolder}/${filename}.exe  
        > externalConsole: true  
        > miDebuggerPath: 编译器路径  
        > preLaunchTask: 同上，label
    
    6. 多文件编译
        1. 把第2点的args中的源文件设多几个即可，而生成文件是"main.exe"

3. 备注
    第（2）点的1，2，3，5均是配置步骤，4是代码实现过程.
