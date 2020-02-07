# Github相关使用
## 1.相关连接

1. [GitHub简单操作](https://www.bootcss.com/p/git-guide/)
1. [删除github文件操作](https://blog.csdn.net/weixin_43976903/article/details/86630862)
> 也可以直接进入相关文件中，直接删除对应文件，但是该操作只能一个一个地删除文件，不能批量删除文件
3. [本地添加文件至云端--操作1](https://jingyan.baidu.com/article/9989c746e35eedf648ecfe8c.html)
4. [本地添加文件至云端--操作2](https://blog.csdn.net/tangxiujiang/article/details/80463325)
5. [VS Code编辑markdown](https://www.cnblogs.com/shawWey/p/8931697.html)  
6. [Git和本地连接，需要把本地仓库(电脑)和对应的云端链接起来](https://blog.csdn.net/haochaoguo1988/article/details/82662475)

## 2.Git本地仓库和远程仓库删除文件操作简述：
- 在本地仓库打开git bash
- git pull (origin master)  :  把远程仓库拉下
- dir                     ：  查看仓库文件内容；
- git rm -r --cached <file>:  删除目标文件（可以是多个文件）
- git commit -m "text"    :   提交操作
- git push -u origin master  ：  进入远程仓库  

## 3.Git把本地仓库文件更新到远程仓库：  
备注：  该操作即可以把文件更新送到云端，也可以把新创立文件推到云端
- 在本地仓库打开git bash
- git pull:  把远程仓库拉下
- git status: 查看本地仓库的更新
- git add <file> : 增加file
- git commit -m "text"  :  提交
- git push origin master: 推上远程仓库

## 4.分支操作
1. git branch -av	           ：	查看分支情况
2. git checkout -b <本地分支robot_bim_verify> origin/<远程分支robot_bim_verify>		：		创建并切换到本地分支
3. git status 		           :	查看文件状态
4. git remote update	       :	根据远程仓库更新到本地
5. git checkout <本地分支>	    ：	 切换到本地分支
6. git push origin <远程分支>	：	 推送代码到远程分支
7. git branch -d <本地分支>	    ：	 删除本次分支

## 5.查看文件修改内容
1. 可视化方式
   1. gitk

2. 命令行方式
   1. git log filename可以查看到对应哪个操作的commit_id
   2. git show commit_id即可以看到对应的修改内容


## ERROR处理
1. ! [rejected] master -> master (non-fast-forward)
   1. git pull origin master --allow-unrelated-histories
   2. 重新add/commit
   3. git push origin master